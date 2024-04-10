/*
 * shclass.c
 * Copyright (c) 1996,1997 Shawn Silverman
 *
*/

#include <stdio.h>
#include <string.h>
#include "d-java.h"

static void showClassFile_attributes(ClassFile *);
static void showClassFile_default(ClassFile *);

static void showOpConstant(ClassFile *, u2);
static void showInterfaces(ClassFile *);
static void showFields(ClassFile *);
static void showMethods(ClassFile *);
static void showFieldType(ClassFile *, u1 *);
static void _showUtf8(u1 *, u2, short);

int showClassFile(ClassFile *cf)
/* This function is the main entry point into the showclass module */
{
    status = ERR_OK;
    if (options.jasmin) status = showClassFile_jasmin(cf);
    else if (options.attributesOnly) showClassFile_attributes(cf);
    else showClassFile_default(cf);
    if (status != ERR_OK) return status;
    
    return ERR_OK;
}

static void showClassFile_attributes(ClassFile *cf)
{
    u2 i, j;
    
    print_info(stdout);
    
    printf("\nClassFile attributes:\n---------------------\n");
    for (i=0; i<cf->attributes_count; i++) {
        printf("%s", (char *)cf->constant_pool[cf->attributes[i].ga->attribute_name].item.bytes);
        printf("    length = %u\n", cf->attributes[i].ga->attribute_length);
    }
    
    printf("\nMethod attributes:\n------------------\n");
    for (i=0; i<cf->methods_count; i++) {
        printf("Method %s:\n", (char *)cf->constant_pool[cf->methods[i].name_index].item.bytes);
        for (j=0; j<cf->methods[i].attributes_count; j++) {
            printf("    %s", (char *)cf->constant_pool[cf->methods[i].attributes[j].ga->attribute_name].item.bytes);
            printf("    length = %u\n", cf->methods[i].attributes[j].ga->attribute_length);
        }
    }
}

static void showClassFile_default(ClassFile *cf)
{
    u2 i;

    print_info(stdout);
    putchar('\n');
    
    for (i=0; i<cf->attributes_count; i++) {
        if (!strcmp((char *)cf->constant_pool[cf->attributes[i].ga->attribute_name].item.bytes, "SourceFile")) {
            printf("Compiled from ");
            showAttributeSourceFile(cf, cf->attributes[0].sf);
            break;
        }
    }

    printf("\n\nMajor version: %d\nMinor version: %d\n\n",
	cf->major_version, cf->minor_version);

    printf("%s%s%s",
           (cf->access_flags & ACC_PUBLIC) ? "public " : "",
           (cf->access_flags & ACC_FINAL) ? "final " : "",
           (cf->access_flags & ACC_ABSTRACT) ? "abstract " : "");

    if (!(cf->access_flags & ACC_INTERFACE)) printf("class ");
    else printf("interface ");
    showConstant(cf, cf->this_class);

    printf(" extends ");
    if (cf->super_class != 0)
	showConstant(cf, cf->super_class);
    else
	printf("java.lang.Object");

    if (cf->interfaces_count != 0) {
	printf("\n    implements ");
	showInterfaces(cf);
    }

    printf("\n%s{",
           (cf->access_flags & ACC_SUPER) ? ">> ACC_SUPER bit set <<\n"
           : "");

    if (cf->fields_count != 0) {
	putchar('\n');
	showFields(cf);
	putchar('\n');
    }
	
    if (options.fieldsOnly == 0) {
        if (cf->methods_count != 0) {
            putchar('\n');
	    showMethods(cf);
	    putchar('\n');
        }
    }

    printf("}\n");
}

short getPadding(u4 pc)
{
    short padding = 0;
    
    switch ((pc+1) & 0x00000003) {
        case 1: padding++;
        case 2: padding++;
        case 3: padding++;
        default: ;
    }
    
    return padding;
}

u4 nextOpcode(u1 *code, u4 pc)
/* Note: this function assumes it was passed a valid opcode */
{
    u4 next = 1;
    s4 npairs, low, high;
    
    if (opcode_length[*code] < 1) return 1;
    
    if (*code == LOOKUPSWITCH || *code == TABLESWITCH)
	next += getPadding(pc);

    code += next;
    
    switch (*(code-next)) {
        case LOOKUPSWITCH:
            next += 4; code += 4;  /* default-offset */
            npairs = u1tos4(code);
            next += 4 + npairs * 8;
            return next;
            break;
        case TABLESWITCH:
            next += 4; code += 4;  /* default_offset */
            low = u1tos4(code);
            next += 4; code += 4;
            high = u1tos4(code);
            next += 4 + (high - low + 1) * 4;
            return next;
            break;
        default: ;
    }
    
    return (opcode_length[*(code-next)]);
}

/*short isTarget(ClassFile *cf, Code_attribute *c, u4 line)
{
    u1 *code = c->code;
    u4 pc, add;
    short padding;
    u4 npairs, low, high, i, j;
    local_variable_table_info lvt_info;
    
     Scan the exception table 
    for (pc=0; pc<c->exception_table_length; pc++) {
        if (line == c->exception_table[pc].start_pc
            || line == c->exception_table[pc].end_pc
            || line == c->exception_table[pc].handler_pc)
            return TRUE;
    }
    
    pc = 0;
    while (pc < c->code_length) {
        switch (*code) {
	    case IFEQ: case IFNE:
	    case IFLT: case IFLE:
	    case IFGT: case IFGE:
	    case IFNULL: case IFNONNULL:
	    case IF_ICMPEQ: case IF_ICMPNE:
	    case IF_ICMPLT: case IF_ICMPGT:
	    case IF_ICMPLE: case IF_ICMPGE:
	    case IF_ACMPEQ: case IF_ACMPNE:
	    case GOTO: case JSR:
	        if (pc + u1tos2(code+1) == line) return TRUE;
	        break;
	    case GOTO_W: case JSR_W:
	        if (pc + u1tos4(code+1) == line) return TRUE;
	        break;
	    case LOOKUPSWITCH:
	        padding = getPadding(pc);
	        if (pc + u1tos4(code+1 + padding) == line) return TRUE;
	        npairs = u1tos4(code+1 + padding + 4);
	        for (i=1; i<=npairs; i++)
	            if (pc + u1tos4(code+1 + padding + 4 + 8*i) == line) return TRUE;
	        break;
	    case TABLESWITCH:
	        padding = getPadding(pc);
	        if (pc + u1tos4(code+1 + padding) == line) return TRUE;
	        low = u1tos4(code+1 + padding + 4);
	        high = u1tos4(code+1 + padding + 8);
	        for (i=1; i<=high-low+1; i++)
	            if (pc + u1tos4(code+1 + padding + 8 + 4*i) == line) return TRUE;
	        break;
	    default:
	        break;
	}
	add = nextOpcode(code, pc);
	pc += add;
	code += add;
    }
    
     Scan the local variable table 
    if (options.showLVT)
        for (i=0; i<c->attributes_count; i++) {
             Find the first attribute that's a local variable table 
            if (!strcmp((char *)cf->constant_pool[c->attributes[i].ga->attribute_name].item.bytes, "LocalVariableTable")) {
                for (j=0; j<c->attributes[i].lvt->local_variable_table_length; j++) {
                    lvt_info = c->attributes[i].lvt->local_variable_table[j];
                    if (lvt_info.start_pc == line
                        || lvt_info.start_pc + lvt_info.length == line)
                        return TRUE;
                }
                break;
            }
        }

    return FALSE;
}*/

/*u4 getLabel(ClassFile *cf, Code_attribute *c, u4 line)
{
    u4 i;
    u4 label_num = 0;

    if (!isTarget(cf, c, line)) return 0;

    for (i=0; i<=line; i++)
        if (isTarget(cf, c, i)) label_num++;

    return label_num;
}*/

void showCode(ClassFile *cf, Code_attribute *c)
{
    u1 *code = c->code;
    u4 i, align;
    short opcode;
    s4 j, low, high, npairs;

    for (i=0; i<c->code_length; i++) {
	opcode = (int) *code++;

	printf("%s%5u ", i ? "\n" : "", i);
	printf("%s", opcode_name[opcode & 0xFF]);

	if (opcode == WIDE) {
	    opcode = (int) *code++ + 256; i++;
	    printf("\n%5u %s", i, opcode_name[opcode & 0xFF]);
	}

	switch (opcode) {
	    case ILOAD:
	    case LLOAD:
	    case FLOAD:
	    case DLOAD:
	    case ALOAD:
		printf(" local%u", *code++); i++;
		break;

	    case ISTORE:
	    case LSTORE:
	    case FSTORE:
	    case DSTORE:
	    case ASTORE:
		printf(" local%u", *code++); i++;
		break;

	    case RET:
		printf(" with local%u", *code++); i++;
		break;

	    case ILOAD+256:
	    case LLOAD+256:
	    case FLOAD+256:
	    case DLOAD+256:
	    case ALOAD+256:
		printf(" local%u", u1tou2(code)); code+=2; i+=2;
		break;

	    case ISTORE+256:
	    case LSTORE+256:
	    case FSTORE+256:
	    case DSTORE+256:
	    case ASTORE+256:
		printf(" local%u", u1tou2(code)); code+=2; i+=2;
		break;

	    case RET+256:
		printf(" with local%u", u1tou2(code)); code+=2; i+=2;
		break;

	    case IINC:
		printf(" local%u by ", *code++); i++;
		printf("%d", *(s1 *)code++); i++;
		break;

	    case IINC+256:
		printf(" local%u by ", u1tou2(code)); code+=2; i+=2;
		printf("%d", u1tos2(code)); code+=2; i+=2;
		break;

	    case BIPUSH:
		printf(" %d", *(s1 *)code++); i++;
		break;

	    case SIPUSH:
		printf(" %d", u1tos2(code)); code+=2; i+=2;
		break;

	    case LDC:
		printf(" #%u ", *code); i++;
		showOpConstant(cf, (u2)*code++);
		break;

	    case LDC_W: case LDC2_W:
	    case ANEWARRAY:
	    case PUTFIELD: case GETFIELD:
	    case PUTSTATIC: case GETSTATIC:
	    case INVOKEVIRTUAL: case INVOKESPECIAL:
	    case INVOKESTATIC:
	    case NEW:
	    case CHECKCAST: case INSTANCEOF:
		printf(" #%u ", u1tou2(code));
		showOpConstant(cf, u1tou2(code)); code+=2; i+=2;
		break;

	    case IFEQ: case IFNE:
	    case IFLT: case IFLE:
	    case IFGT: case IFGE:
	    case IFNULL: case IFNONNULL:
	    case IF_ICMPEQ: case IF_ICMPNE:
	    case IF_ICMPLT: case IF_ICMPGT:
	    case IF_ICMPLE: case IF_ICMPGE:
	    case IF_ACMPEQ: case IF_ACMPNE:
	    case GOTO: case JSR:
		printf(" %u", i + u1tos2(code)); code+=2; i+=2;
		break;

	    case GOTO_W: case JSR_W:
		printf(" %u", i + u1tos4(code)); code+=4; i+=4;
		break;

	    case NEWARRAY:
		switch (*code++) {
		    case T_BOOLEAN:	printf(" boolean"); break;
		    case T_CHAR: 	printf(" char"); break;
		    case T_FLOAT: 	printf(" float"); break;
		    case T_DOUBLE: 	printf(" double"); break;
		    case T_BYTE: 	printf(" byte"); break;
		    case T_SHORT:	printf(" short"); break;
		    case T_INT:		printf(" int"); break;
		    case T_LONG: 	printf(" long"); break;
		    default:		printf(" *unknown type*");
		};
		i++;
		break;

	    case MULTIANEWARRAY:
		printf(" #%u dim ", u1tou2(code));
		printf("%u ", *(code+2));
		showOpConstant(cf, u1tou2(code)); code+=3; i+=3;
		break;

	    case TABLESWITCH: case LOOKUPSWITCH:
	        align = getPadding(i);
	        i += align;
	        code += align;
		switch (opcode) {
		    case TABLESWITCH:
		        low = u1tos4(code+4);
		        high = u1tos4(code+8);
			printf(" %d to %d: default=%u", low, high,
			    i-align + u1tos4(code));  /* default-offset */
		        code+=12;

			for(j=low; j<=high; j++) {
			    printf("\n          %5d: %u", j,
			        i-align + u1tos4(code));  /* jump-offset */
			    code+=4;
			}

			i += 12 + 4 * (high - low + 1);
			break;
		    case LOOKUPSWITCH:
			npairs = u1tos4(code+4);
			printf(" %d items: default=%u", npairs,
			    i-align + u1tos4(code));  /* default-offset */
			code+=8;

			for (j=0; j<npairs; j++) {
			    printf("\n          %5d: ", u1tos4(code));  /* match */
			    printf("%u", i-align + u1tos4(code+4));  /* offset */
			    code+=8;
			}

			i += 8 + npairs * 8;
			break;
		}
		break;

	    case INVOKEINTERFACE:
		printf(" (%u ", *(code+2));  /* nargs */
		(*(code+2) == 1) ? printf("arg)") : printf("args)");

		printf(" #%u ", u1tou2(code));
		showOpConstant(cf, u1tou2(code));
		code+=3; i+=3;

		printf(" reserved val: \\x%02X", *code++);  /* reserved */
		i++;
		break;
	}
    }
}

static void showOpConstant(ClassFile *cf, u2 index)
{
    putchar('<');
    switch (cf->constant_pool[index].tag) {
	case CONSTANT_Class: printf("Class "); break;
	case CONSTANT_Fieldref: printf("Field "); break;
	case CONSTANT_Methodref: printf("Method "); break;
	case CONSTANT_InterfaceMethodref: printf("InterfaceMethod "); break;
	case CONSTANT_String: printf("String "); break;
	case CONSTANT_Integer: printf("Int "); break;
	case CONSTANT_Float: printf("Float "); break;
	case CONSTANT_Long: printf("Long "); break;
	case CONSTANT_Double: printf("Double "); break;
	case CONSTANT_NameAndType: printf("NameAndType "); break;
	case CONSTANT_Utf8: printf("\""); break;
	default: printf("Unknown tag: %u", cf->constant_pool[index].tag);
                 break;
    }

    showConstant(cf, index);
    if (cf->constant_pool[index].tag == CONSTANT_Utf8) putchar('\"');
    putchar('>');
}

void showAccessFlags(u2 access_flags)
{
    printf("%s%s%s%s%s%s%s%s%s%s",
	(access_flags & ACC_PUBLIC) ? "public " : "",
	(access_flags & ACC_PRIVATE) ? "private " : "",
	(access_flags & ACC_PROTECTED) ? "protected " : "",
	(access_flags & ACC_STATIC) ? "static " : "",
	(access_flags & ACC_FINAL) ? "final " : "",
	(access_flags & ACC_SYNCHRONIZED) ? "synchronized " : "",
	(access_flags & ACC_VOLATILE) ? "volatile " : "",
	(access_flags & ACC_TRANSIENT) ? "transient " : "",
	(access_flags & ACC_NATIVE) ? "native " : "",
	/*(access_flags & ACC_INTERFACE) ? "interface " : "",*/
	(access_flags & ACC_ABSTRACT) ? "abstract " : "");
}

static void showInterfaces(ClassFile *cf)
{
    u2 i;

    showConstantClass(cf, cf->interfaces[0]);
    for (i=1; i<cf->interfaces_count; i++) {
	printf(",\n               ");
	showConstant(cf, cf->interfaces[i]);
    }
}

static void showFields(ClassFile *cf)
{
    u2 i, j;

    for (i=0; i<cf->fields_count; i++) {
	printf("%s    ", i ? "\n" : "");
	showAccessFlags(cf->fields[i].access_flags);

	showDescriptorNoArgs(cf, cf->fields[i].descriptor_index);
	putchar(' ');
	showConstantUtf8(cf, cf->fields[i].name_index, FALSE);
	/*for (j=0; j<array_dim; j++) printf("[]"); */

	for (j=0; j<cf->fields[i].attributes_count; j++) {
	    if (!strcmp((char *)cf->constant_pool[cf->fields[i].attributes[j].ga->attribute_name].item.bytes,
	        "ConstantValue"))  {
	        printf(" = ");
	        showConstant(cf,
	        cf->fields[i].attributes[0].cv->constantvalue_index);
	        break;
	    }
	}
	putchar(';');
    }

    putchar ('\n');
    
    for (i=0; i<cf->methods_count; i++) {
	printf("\n    ");
	showAccessFlags(cf->methods[i].access_flags);

	showDescriptorNoArgs(cf, cf->methods[i].descriptor_index);
	putchar(' ');
	showConstantUtf8(cf, cf->methods[i].name_index, FALSE);
	putchar('(');
	showDescriptorArgs(cf, cf->methods[i].descriptor_index);
	putchar(')');

	putchar(';');
    }
}

static void showMethods(ClassFile *cf)
{
    u2 i, j;

    for (i=0; i<cf->methods_count; i++) {
        if (options.verbose) fputc('.', stderr);

	printf("%sMethod ", i ? "\n\n" : "");

	showAccessFlags(cf->methods[i].access_flags);
	showDescriptorNoArgs(cf, cf->methods[i].descriptor_index);
	putchar(' ');
	showConstantUtf8(cf, cf->methods[i].name_index, FALSE);
	putchar('(');
	showDescriptorArgs(cf, cf->methods[i].descriptor_index);
	putchar(')');
	putchar('\n');
		
	/* Show the 'throws' stuff */
	for (j=0; j<cf->methods[i].attributes_count; j++) {
	    if (!strcmp((char *)cf->constant_pool[cf->methods[i].attributes[j].ga->attribute_name].item.bytes, "Exceptions")) {
	        /* If there are no exceptions then leave */
	        if (cf->methods[i].attributes[j].e->number_of_exceptions == 0)
	            break;
	        showAttributeExceptions(cf, cf->methods[i].attributes[j].e);
	        putchar('\n');
	        break;
	    }
	}
	
	for (j=0; j<cf->methods[i].attributes_count; j++) {
	    if (!strcmp((char *)cf->constant_pool[cf->methods[i].attributes[j].ga->attribute_name].item.bytes, "Code")) {
	        showAttributeCode(cf, cf->methods[i].attributes[j].c);
	        break;
	    }
	}
    }
}

void showDescriptorNoArgs(ClassFile *cf, u2 index)
{
    u1 *bytes = cf->constant_pool[index].item.bytes;
    u2 array_dim, i;
    
    /* Skip evrything in between and including '(' & ')' */
    if (*bytes == '(')
        while (*bytes++ != ')') ;

    /* Count '[' so we can put the appropriate number of '[]' after the type */
    array_dim = 0;
    while (*bytes == '[') { array_dim++; bytes++; }

    switch (*bytes) {
	case 'B':
	case 'C':
	case 'D':
	case 'F':
	case 'I':
	case 'J':
	case 'L':
	case 'S':
	case 'Z':
	    showFieldType(cf, bytes);
	    for (i=0; i<array_dim; i++) printf("[]");
	    break;
	case 'V':
	    printf("void");
	    break;
	default:
	    showUtf8(cf->constant_pool[index].item.bytes, FALSE);
    }
}

static void showFieldType(ClassFile *cf, u1 *bytes)
{
    int i = 0;

    switch (*bytes) {
	case 'B': printf("byte"); break;
	case 'C': printf("char"); break;
	case 'D': printf("double"); break;
	case 'F': printf("float"); break;
	case 'I': printf("int"); break;
	case 'J': printf("long"); break;
	case 'L':
	    while (*++bytes != ';')
		i++;
	    _showUtf8(bytes - i, i, TRUE);
	    break;
	case 'S': printf("short"); break;
	case 'Z': printf("boolean"); break;
	default : break; /*printf("*unknown type*"); */
    }
}

void showDescriptorArgs(ClassFile *cf, u2 index)
{
    u2 array_dim, i;
    u1 *bytes = cf->constant_pool[index].item.bytes;
    short more_args = FALSE;
    
    while (*++bytes != ')') {
	if (more_args) putchar(',');
	else more_args = TRUE;
	
        array_dim = 0;
        while (*bytes == '[') { array_dim++; bytes++; }

	showFieldType(cf, bytes);
	for (i=0; i<array_dim; i++) printf("[]");
	
	if (*bytes == 'L')
	    while (*++bytes != ';') ;
    }
}

void showUtf8(u1 *bytes, short fullclassname)
{
    _showUtf8(bytes, strlen((char *)bytes), fullclassname);
}

static void _showUtf8(u1 *bytes, u2 length, short fullclassname)
{
    u2 i;
    u2 u2val;
    /*u1 *pbytes; */
    /*u1 buf[strlen((char *)bytes) + 1]; */
    size_t package_len;

    if (fullclassname) {
        i = 0;
        while (*packages[i]) {
            package_len = strlen(packages[i]);
            if (!strncmp((char *)bytes, packages[i], package_len)) {
                bytes += package_len;
                length -= package_len;
            }
            i++;
        }
    }
    
    for (i=0; i<length; i++, bytes++) {
	if (!(*bytes & 0x80)) {
	    switch (*bytes) {
		case '/':
		    if (fullclassname) putchar('.');
		    else putchar('/'); break;
		case BS: putchar('\\'); putchar('b'); break;
		case TAB: putchar('\\'); putchar('t'); break;
		case LF: putchar('\\'); putchar('n'); break;
		case FF: putchar('\\'); putchar('f'); break;
		case CR: putchar('\\'); putchar('r'); break;
		case BACKSLASH: putchar('\\'); putchar('\\'); break;
		case SINGQUOTE: putchar('\\'); putchar('\''); break;
		case DOUBQUOTE: putchar('\\'); putchar('\"'); break;
		default:
		    putchar((int) *bytes);
	    }
	}

	else if ((*bytes >> 5) == 0x06) {
	    putchar('\\');
	    u2val = ((u2) (*bytes++ & 0x1F)) << 6;
	    u2val |= (*bytes & 0x3F);
	    if (u2val <= 0xFF)
		printf("%03o", u2val);
	    else
		printf("u%04X", u2val);

	    i++;
	}

	else if ((*bytes >> 4) == 0x0E) {
	    u2val = ((u2) (*bytes++ & 0x0F)) << 12;
	    u2val |= ((u2) (*bytes++ & 0x3F)) << 6;
	    u2val |= (u2) (*bytes & 0x3F);

	    printf("\\u%04X", u2val);
	    
	    i+=2;
	}
    }       
}

u2 u1tou2(u1 *bytes)
{
    return ((u2)*bytes << 8 | (u2)*(bytes+1));
}

s2 u1tos2(u1 *bytes)
{
    return ((s2)((u2)*bytes << 8 | (u2)*(bytes+1)));
}

s4 u1tos4(u1 *bytes)
{
    return ((s4)((u4)*bytes << 24
        | (u4)*(bytes+1) << 16
        | (u4)*(bytes+2) << 8
        | (u4)*(bytes+3)));
}
