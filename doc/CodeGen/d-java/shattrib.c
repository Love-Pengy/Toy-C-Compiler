/*
 * shattrib.c
 * Copyright (c) 1996,1997 Shawn Silverman
 *
*/

#include <stdio.h>
#include <string.h>
#include "d-java.h"

void showAttributeSourceFile(ClassFile *cf, SourceFile_attribute *sf)
{
    showConstantUtf8(cf, sf->sourcefile_index, FALSE);
}

void showAttributeConstantValue(ClassFile *cf, ConstantValue_attribute *cv)
{
    showConstant(cf, cv->constantvalue_index);
}

void showAttributeExceptions(ClassFile *cf, Exceptions_attribute *e)
{
    u2 i;
    
    printf("    throws ");
    for (i=0; i<e->number_of_exceptions; i++) {
        printf("%s", i ? ",\n           " : "");
        showConstantClass(cf, e->exception_index_table[i]);
    }
}

void showAttributeCode(ClassFile *cf, Code_attribute *c)
{
    u2 i;
    
    printf(">> max_stack=%u, max_locals=%u <<\n", c->max_stack, c->max_locals);

    showCode(cf, c);

    if (c->exception_table_length > 0) {
	printf("\nException table:\n   from   to  target type");
	for (i=0; i<c->exception_table_length; i++) {
	    printf("\n %5u %5u %5u", c->exception_table[i].start_pc,
	        c->exception_table[i].end_pc,
	        c->exception_table[i].handler_pc);
	    if (c->exception_table[i].catch_type != 0) {
		printf("   <Class ");
		showConstant(cf, c->exception_table[i].catch_type);
		putchar('>');
	    }
	    else
		printf("   any");
	}
    }
    
    for (i=0; i<c->attributes_count; i++) {
        if (options.showLVT)
            if (!strcmp((char *)cf->constant_pool[c->attributes[i].ga->attribute_name].item.bytes, "LocalVariableTable")) {
	        putchar('\n');
	        showAttributeLocalVariableTable(cf, c->attributes[i].lvt);
	        continue;
	    }
	if (options.showLNT)
            if (!strcmp((char *)cf->constant_pool[c->attributes[i].ga->attribute_name].item.bytes, "LineNumberTable")) {
                putchar('\n');
	        showAttributeLineNumberTable(cf, c->attributes[i].lnt);
	    }
    }
}

void showAttributeLineNumberTable(ClassFile *cf, LineNumberTable_attribute *lnt)
{
    u2 i;
    
    printf("Line number table:\n    pc   line");
    for (i=0; i<lnt->line_number_table_length; i++) {
        printf("\n %5u  %5u", lnt->line_number_table[i].start_pc,
            lnt->line_number_table[i].line_number);
    }
}

void showAttributeLocalVariableTable(ClassFile *cf, LocalVariableTable_attribute *lvt)
{
    u2 i;
    
    printf("Local variable table:\n  start length   slot");
    for (i=0; i<lvt->local_variable_table_length; i++) {
        printf("\n %5u  %5u  %5u  ", lvt->local_variable_table[i].start_pc,
            lvt->local_variable_table[i].length,
            lvt->local_variable_table[i].index);
        showConstantUtf8(cf, lvt->local_variable_table[i].name_index, FALSE);
        putchar(':');
        showDescriptorNoArgs(cf, lvt->local_variable_table[i].descriptor_index);
    }
}
