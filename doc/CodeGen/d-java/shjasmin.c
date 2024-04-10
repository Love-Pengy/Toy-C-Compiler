/*
 * shjasmin.c
 * Copyright (c) 1996,1997 Shawn Silverman
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "d-java.h"

static int showAttributeCode_jasmin(ClassFile *, Code_attribute *);
static int showCode_jasmin(ClassFile *, Code_attribute *);
static void showInterfaces_jasmin(ClassFile *);
static void showFields_jasmin(ClassFile *);
static int showMethods_jasmin(ClassFile *);

static void printLineNumberTableEntry(ClassFile *, Code_attribute *, u4);
static void printLocalVariableTableEntry(ClassFile *, Code_attribute *, u4);
static void printExceptionTableEntry(ClassFile *, Code_attribute *, u4);

int showClassFile_jasmin(ClassFile *cf)
{
    u2 i;

    print_info_jasmin(stdout);

    printf("\n;Classfile version:\n;    Major: %d\n;    Minor: %d\n\n",
	cf->major_version, cf->minor_version);

    for (i=0; i<cf->attributes_count; i++) {
        if (!strcmp((char *)cf->constant_pool[cf->attributes[i].ga->attribute_name].item.bytes, "SourceFile")) {
            printf(".source ");
            showAttributeSourceFile(cf, cf->attributes[0].sf);
            break;
        }
    }

    if (cf->access_flags & ACC_INTERFACE) {
        /*printf("\n;note: Jasmin does not yet support interfaces"); */
        printf("\n.interface ");
    }
    else {
        printf("\n.class  ");
    }

    printf("%s%s%s",
           (cf->access_flags & ACC_PUBLIC) ? "public " : "",
           (cf->access_flags & ACC_FINAL) ? "final " : "",
           (cf->access_flags & ACC_ABSTRACT) ? "abstract " : "");

    showConstantUtf8(cf, cf->constant_pool[cf->this_class].index1, FALSE);

    printf("\n%s.super  ",
           (cf->access_flags & ACC_SUPER) ? "; ACC_SUPER bit is set\n"
           : "");

    if (cf->super_class != 0)
	showConstantUtf8(cf, cf->constant_pool[cf->super_class].index1, FALSE);
    else
	printf("java/lang/Object");
    putchar('\n');

    if (cf->interfaces_count > 0) {
	showInterfaces_jasmin(cf);
	/*printf("\n;note: Jasmin does not yet support the implementation of interfaces"); */
    }

    if (cf->fields_count != 0) {
        putchar('\n');
	showFields_jasmin(cf);
	putchar('\n');
    }
	
    if (cf->methods_count != 0) {
        putchar('\n');
	CHECK_STATUS(showMethods_jasmin(cf));
	putchar('\n');
    }
    
    return ERR_OK;
}

static int showAttributeCode_jasmin(ClassFile *cf, Code_attribute *c)
{
    printf("    .limit stack %u\n", c->max_stack);
    printf("    .limit locals %u\n", c->max_locals);
    
    CHECK_STATUS(showCode_jasmin(cf, c));
    
    return ERR_OK;
}

static int showCode_jasmin(ClassFile *cf, Code_attribute *c)
{
    u1 *code = c->code;
    u4 i, align, label_num;
    short opcode;
    s4 j, low, high, default_offset, npairs, match, offset;

    if ((num_labels = scanForLabels(cf, c))) {
        if ((labels = (u4 *)calloc(num_labels, sizeof(u4))) == NULL) {
            return ERR_MEM;
        }
        num_labels = insertLabels(cf, c, labels);
    }
     
    for (i=0; i<c->code_length; i++) {
	if (i) putchar('\n');

	opcode = (int) *code++;

	if (opcode == WIDE) {
	    opcode = (int) *code++ + 256;
	    i++;
	}

        if (options.showLNT) printLineNumberTableEntry(cf, c, i);
        if (options.showLVT) printLocalVariableTableEntry(cf, c, i);
        printExceptionTableEntry(cf, c, i);

        /*if (label_num = getLabel(cf, c, i)) */
        if ((label_num = getLabel(labels, num_labels, i)))
            printf("Label%u:\n", label_num);
        printf("    %s", opcode_name[opcode & 0xFF]);

	switch (opcode) {
	    case ILOAD:
	    case LLOAD:
	    case FLOAD:
	    case DLOAD:
	    case ALOAD:
	    case ISTORE:
	    case LSTORE:
	    case FSTORE:
	    case DSTORE:
	    case ASTORE:
	    case RET:
		printf(" %u", *code++); i++;
		break;

	    case ILOAD+256:
	    case LLOAD+256:
	    case FLOAD+256:
	    case DLOAD+256:
	    case ALOAD+256:
	    case ISTORE+256:
	    case LSTORE+256:
	    case FSTORE+256:
	    case DSTORE+256:
	    case ASTORE+256:
	    case RET+256:
		printf(" %u", u1tou2(code)); code+=2; i+=2;
		break;

	    case IINC:
		printf(" %u", *code++); i++;
		printf(" %d", *(s1 *)code++); i++;
		break;

	    case IINC+256:
		printf(" %u", u1tou2(code)); code+=2; i+=2;
		printf(" %d", u1tos2(code)); code+=2; i+=2;
		break;

	    case BIPUSH:
		printf(" %d", *(s1 *)code++); i++;
		break;

	    case SIPUSH:
		printf(" %d", u1tos2(code)); code+=2; i+=2;
		break;

	    case INVOKEVIRTUAL: case INVOKESPECIAL:
	    case INVOKESTATIC:
	    case INVOKEINTERFACE:
	        putchar(' ');
	        showConstantUtf8(cf, cf->constant_pool[cf->constant_pool[u1tou2(code)].index1].index1, FALSE);
	        putchar('/');
	        showConstantUtf8(cf, cf->constant_pool[cf->constant_pool[u1tou2(code)].index2].index1, FALSE);
	        showConstantUtf8(cf, cf->constant_pool[cf->constant_pool[u1tou2(code)].index2].index2, FALSE);
	        code+=2; i+=2;

	        if (opcode != INVOKEINTERFACE) break;
                printf(" %u", *code);  /* nargs */
		code+=2; i+=2;
		break;

	    case LDC:
		putchar(' ');
		showConstant(cf, (u2)*code);
		code++; i++;
		break;

	    case LDC_W: case LDC2_W:
		putchar(' ');
		showConstant(cf, u1tou2(code));
		code+=2; i+=2;
		break;

	    case PUTFIELD: case GETFIELD:
	    case PUTSTATIC: case GETSTATIC:
	        putchar(' ');
	        showConstantUtf8(cf, cf->constant_pool[cf->constant_pool[u1tou2(code)].index1].index1, FALSE);
	        putchar('/');
	        showConstantUtf8(cf, cf->constant_pool[cf->constant_pool[u1tou2(code)].index2].index1, FALSE);
	        putchar(' ');
	        showConstantUtf8(cf, cf->constant_pool[cf->constant_pool[u1tou2(code)].index2].index2, FALSE);
	        code+=2; i+=2;
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
		/*printf(" Label%u", getLabel(cf, c, i + u1tos2(code))); */
		printf(" Label%u", getLabel(labels, num_labels, i + u1tos2(code)));
		code+=2; i+=2;
		break;

	    case GOTO_W: case JSR_W:
		/*printf(" Label%u", getLabel(cf, c, i + u1tos4(code))); */
		printf(" Label%u", getLabel(labels, num_labels, i + u1tos4(code)));
		code+=4; i+=4;
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

	    case NEW:
	    case CHECKCAST:
	    case INSTANCEOF:
	    case ANEWARRAY:
		putchar(' ');
		showConstantUtf8(cf, cf->constant_pool[u1tou2(code)].index1, FALSE);
		code+=2; i+=2;
		break;

	    case MULTIANEWARRAY:
		putchar(' ');
		showConstantUtf8(cf, cf->constant_pool[u1tou2(code)].index1, FALSE);
		printf(" %u", *(code+2));
		code+=3; i+=3;
		break;

	    case TABLESWITCH: case LOOKUPSWITCH:
		align = getPadding(i);
		i += align;
		code += align;
		switch (opcode) {
		    case TABLESWITCH:
		        low = u1tos4(code+4);
		        high = u1tos4(code+8);
		        default_offset = u1tos4(code);
		        code+=12;
			printf(" %d  ;high = %d", low, high);

			for(j=low; j<=high; j++) {
			    /*printf("\n          Label%u", getLabel(cf, c, i-align + u1tos4(code))); */
			    printf("\n          Label%u", getLabel(labels, num_labels, i-align + u1tos4(code)));
			    code+=4;
			}
			/*printf("\n        default : Label%u", getLabel(cf, c, i-align + default_offset)); */
			printf("\n        default : Label%u", getLabel(labels, num_labels, i-align + default_offset));

			i += 12 + 4 * (high - low + 1);
			break;
		    case LOOKUPSWITCH:
			default_offset = u1tos4(code);
			npairs = u1tos4(code+4);
			code+=8;

			offset = 0;
			for (j=0; j<npairs; j++) {
			    match = u1tos4(code);
			    offset = u1tos4(code+4);
			    code+=8;
			    printf("\n        %5d : ", match);
			    /*printf("Label%u", getLabel(cf, c, i-align + offset)); */
			    printf("Label%u", getLabel(labels, num_labels, i-align + offset));
			}
			/*printf("\n        default : Label%u", getLabel(cf, c, i-align + default_offset)); */
			printf("\n        default : Label%u", getLabel(labels, num_labels, i-align + offset));

			i += 8 + npairs * 8;
			break;
		}
		break;
	}
    }

    /*if (label_num = getLabel(cf, c, c->code_length)) */
    if ((label_num = getLabel(labels, num_labels, c->code_length)))
        printf("\nLabel%u:", label_num);

    if (num_labels > 0) free(labels);
    
    return ERR_OK;
}

static void showInterfaces_jasmin(ClassFile *cf)
{
    u2 i;

    printf(".implements ");
    showConstantUtf8(cf, cf->constant_pool[cf->interfaces[0]].index1, FALSE);
    for (i=1; i<cf->interfaces_count; i++) {
	printf("\n.implements ");
	showConstantUtf8(cf, cf->constant_pool[cf->interfaces[i]].index1, FALSE);
    }
}    

static void showFields_jasmin(ClassFile *cf)
{
    u2 i, j;

    for (i=0; i<cf->fields_count; i++) {
	printf("%s.field ", i ? "\n" : "");

	showAccessFlags(cf->fields[i].access_flags);
	showConstantUtf8(cf, cf->fields[i].name_index, FALSE);
	putchar(' ');
	showConstantUtf8(cf, cf->fields[i].descriptor_index, FALSE);

	for (j=0; j<cf->fields[i].attributes_count; j++) {
	    if (!strcmp((char *)cf->constant_pool[cf->fields[i].attributes[j].ga->attribute_name].item.bytes,
	        "ConstantValue"))  {
	        printf(" = ");
	        showConstant(cf, cf->fields[i].attributes[0].cv->constantvalue_index);
	        break;
	    }
	}
    }
}

static int showMethods_jasmin(ClassFile *cf)
{
    u2 i, j, k;

    for (i=0; i<cf->methods_count; i++) {
	if (options.verbose) fputc('.', stderr);

	printf("%s; >> METHOD %u <<\n", i ? "\n\n" : "", i+1);
	
	printf(".method ");

	showAccessFlags(cf->methods[i].access_flags);
	showConstantUtf8(cf, cf->methods[i].name_index, FALSE);
	showConstantUtf8(cf, cf->methods[i].descriptor_index, FALSE);
		
	/* Show the 'throws' stuff */
	for (j=0; j<cf->methods[i].attributes_count; j++) {
	    if (!strcmp((char *)cf->constant_pool[cf->methods[i].attributes[j].ga->attribute_name].item.bytes, "Exceptions")) {
	        for (k=0; k<cf->methods[i].attributes[j].e->number_of_exceptions; k++) {
	            printf("\n    .throws ");
	            showConstantUtf8(cf, cf->constant_pool[cf->methods[i].attributes[j].e->exception_index_table[k]].index1, FALSE);
	        }
	        
	        putchar('\n');
	        break;
	    }
	}
	putchar('\n');
	
	if (!(cf->methods[i].access_flags & ACC_ABSTRACT)) {
	    for (j=0; j<cf->methods[i].attributes_count; j++) {
	        if (!strcmp((char *)cf->constant_pool[cf->methods[i].attributes[j].ga->attribute_name].item.bytes, "Code")) {
	            CHECK_STATUS(showAttributeCode_jasmin(cf, cf->methods[i].attributes[j].c));
	            putchar('\n');
	            break;
	        }
	    }
	}
	
	printf(".end method");
    }
    
    return ERR_OK;
}

static void printLineNumberTableEntry(ClassFile *cf, Code_attribute *c, u4 line)
{
    u2 i, j;
    
    /* Find the first possible line number table */
    for (i=0; i<c->attributes_count; i++) {
        if (!strcmp((char *)cf->constant_pool[c->attributes[i].ga->attribute_name].item.bytes, "LineNumberTable")) {
            for (j=0; j<c->attributes[i].lnt->line_number_table_length; j++)
                if (c->attributes[i].lnt->line_number_table[j].start_pc == line)
                    printf(".line %u\n", c->attributes[i].lnt->line_number_table[j].line_number);
            return;
        }
    }
}

static void printLocalVariableTableEntry(ClassFile *cf, Code_attribute *c, u4 line)
{
    u2 i, j;
    local_variable_table_info lvt_info;

    for (i=0; i<c->attributes_count; i++) {
        if (!strcmp((char *)cf->constant_pool[c->attributes[i].ga->attribute_name].item.bytes, "LocalVariableTable")) {
            for (j=0; j<c->attributes[i].lvt->local_variable_table_length; j++) {
                lvt_info = c->attributes[i].lvt->local_variable_table[j];
                if (lvt_info.start_pc == line) {
                    printf(".var %u is ", lvt_info.index);
                    showConstantUtf8(cf, lvt_info.name_index, FALSE);
                    putchar(' ');
                    showConstantUtf8(cf, lvt_info.descriptor_index, FALSE);
                    printf(" from Label%u to Label%u\n",
                        /*getLabel(cf, c, lvt_info.start_pc), */
                        /*getLabel(cf, c, lvt_info.start_pc + lvt_info.length)); */
                        getLabel(labels, num_labels, lvt_info.start_pc),
                        getLabel(labels, num_labels, lvt_info.start_pc + lvt_info.length));
                }
            }
	    return;
	}
    }
}

static void printExceptionTableEntry(ClassFile *cf, Code_attribute *c, u4 line)
{
    u2 i;

    for (i=0; i<c->exception_table_length; i++) {
        if (c->exception_table[i].start_pc == (u2)line) {
            printf(".catch ");
            if (c->exception_table[i].catch_type > 0)
                showConstantUtf8(cf, cf->constant_pool[c->exception_table[i].catch_type].index1, FALSE);
            else
                printf("all");

            printf(" from Label%u to Label",
                /*getLabel(cf, c, c->exception_table[i].start_pc), */
                /*getLabel(cf, c, c->exception_table[i].end_pc), */
                /*getLabel(cf, c, c->exception_table[i].handler_pc)); */
                getLabel(labels, num_labels, c->exception_table[i].start_pc));
            printf("%u using Label%u\n",
                getLabel(labels, num_labels, c->exception_table[i].end_pc),
                getLabel(labels, num_labels, c->exception_table[i].handler_pc));
        }
    }
}
