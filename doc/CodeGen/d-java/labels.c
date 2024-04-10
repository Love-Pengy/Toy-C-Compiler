/*
 * labels.c
 * Copyright (c) 1996,1997 Shawn Silverman
 *
*/

#include <stdlib.h>
#include <string.h>
#include "d-java.h"

/*static short inList(u4 [], u4, u4);*/
static int qsort_label_cmp(const void *, const void *);
static u4 removeDuplicateLabels(u4 [], u4);
static u4 isLabel(u4 [], u4, u4);

u4 scanForLabels(ClassFile *cf, Code_attribute *c)
/* This function scans all the opcodes so it can track labels */
{
    u1 *code = c->code;
    u4 pc = 0, add, num_labels = 0;
    u2 i;
    short padding;
    s4 npairs, low, high;
    
    /* Scan the exception table */
    num_labels += c->exception_table_length * 3;
    
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
	    case GOTO_W: case JSR_W:
	        num_labels++;
	        break;
	    case LOOKUPSWITCH:
	        padding = getPadding(pc);
	        npairs = u1tos4(code+1 + padding + 4);
	        num_labels += 1 + npairs;
	        break;
	    case TABLESWITCH:
	        padding = getPadding(pc);
	        low = u1tos4(code+1 + padding + 4);
	        high = u1tos4(code+1 + padding + 8);
	        num_labels += 1 + (high-low+1);
	        break;
	    default:
	        break;
	}
	add = nextOpcode(code, pc);
	pc += add;
	code += add;
    }
    
    /* Scan the local variable table */
    /* Only scan if we are not decompiling */
    /* -- relevant to fall-through basic-blocks */
    /*    where the next basic-block must begin with a label */
    if (!options.decompile && options.showLVT)
        for (i=0; i<c->attributes_count; i++) {
            /* Find the first attribute that's a local variable table */
            if (!strcmp((char *)cf->constant_pool[c->attributes[i].ga->attribute_name].item.bytes, "LocalVariableTable")) {
                num_labels += c->attributes[i].lvt->local_variable_table_length * 2;
                break;
            }
        }

    return num_labels;
}

u4 insertLabels(ClassFile *cf, Code_attribute *c, u4 labels[])
/* This function puts all the labels into a list then sorts 'em
   Note: there will be duplicates */
{
    u1 *code = c->code;
    u4 pc, add, curr_label = 0;
    u2 i, j;
    short padding;
    s4 npairs, low, high, k;
    local_variable_table_info lvt_info;
    
    /* Scan the exception table */
    for (k=0; k<c->exception_table_length; k++) {
        labels[curr_label++] = c->exception_table[k].start_pc;
        labels[curr_label++] = c->exception_table[k].end_pc;
        labels[curr_label++] = c->exception_table[k].handler_pc;
    }

    pc = 0;
    /* Insert into the list, ignoring duplicates */
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
	        /*if (pc + u1tos2(code+1) != labels[curr_label])*/
	            labels[curr_label++] = pc + u1tos2(code+1);
	        break;
	    case GOTO_W: case JSR_W:
	        /*if (pc + u1tos4(code+1) != labels[curr_label])*/
	            labels[curr_label++] = pc + u1tos4(code+1);
	        break;
	    case LOOKUPSWITCH:
	        padding = getPadding(pc);
	        labels[curr_label++] = pc + u1tos4(code+1 + padding);
	        npairs = u1tos4(code+1 + padding + 4);
	        for (k=1; k<=npairs; k++)
	            /*if (pc + u1tos4(code+1 + padding + 4 + 8*k) != labels[curr_label])*/
	                labels[curr_label++] = pc + u1tos4(code+1 + padding + 4 + 8*k);
	        break;
	    case TABLESWITCH:
	        padding = getPadding(pc);
	        labels[curr_label++] = pc + u1tos4(code+1 + padding);
	        low = u1tos4(code+1 + padding + 4);
	        high = u1tos4(code+1 + padding + 8);
	        for (k=1; k<=high-low+1; k++)
	            /*if (pc + u1tos4(code+1 + padding + 8 + 4*k) != labels[curr_label])*/
	                labels[curr_label++] = pc + u1tos4(code+1 + padding + 8 + 4*k);
	        break;
	    default:
	        break;
	}
	add = nextOpcode(code, pc);
	pc += add;
	code += add;
    }
    
    /* Scan the local variable table */
    if (!options.decompile && options.showLVT)
        for (i=0; i<c->attributes_count; i++) {
            /* Find the first attribute that's a local variable table */
            if (!strcmp((char *)cf->constant_pool[c->attributes[i].ga->attribute_name].item.bytes, "LocalVariableTable")) {
                for (j=0; j<c->attributes[i].lvt->local_variable_table_length; j++) {
                    lvt_info = c->attributes[i].lvt->local_variable_table[j];
                    labels[curr_label++] = lvt_info.start_pc;
                    labels[curr_label++] = lvt_info.start_pc + lvt_info.length;
                }
                break;
            }
        }
        
    qsort(labels, curr_label, sizeof(u4), qsort_label_cmp);
    
    return (removeDuplicateLabels(labels, curr_label));
}

static int qsort_label_cmp(const void *e1, const void *e2)
{
    if (*(u4 *)e1 > *(u4 *)e2) return 1;
    if (*(u4 *)e1 < *(u4 *)e2) return -1;
    return 0;
}

static u4 removeDuplicateLabels(u4 labels[], u4 num_labels)
{
    u4 look_ahead, p;
    
    if (num_labels == 1) return 1;
    
    look_ahead = p = 1;
    
    while (1) {
        while (look_ahead < num_labels && labels[look_ahead] == labels[look_ahead-1])
            look_ahead++;
        if (look_ahead == num_labels) return p;
        labels[p] = labels[look_ahead];
        p++;
        look_ahead++;
    }
}

static u4 isLabel(u4 labels[], u4 num_labels, u4 line)
/* Perform a binary search */
{
    s4 p1, p2, p;
    
    if (num_labels == 0) return 0;
    
    p1 = 0;
    p2 = num_labels - 1;

    while (p1 <= p2) {
        p = (p1 + p2) >> 1;
        if (line == labels[p]) return p + 1;
        if (line > labels[p]) p1 = p + 1;
        if (line < labels[p]) p2 = p - 1;
    }
    
    return 0;
}

u4 getLabel(u4 labels[], u4 num_labels, u4 line)
/* This function assumes there are labels (num_labels >= 1) */
{
    return isLabel(labels, num_labels, line);
    
    /*
    static curr_label;
    u4 retval;

    if (line == 0) curr_label = 0;
    
    // Don't even bother if the line is not within the range of labels
    if (line < labels[curr_label] || line > labels[num_labels-1])
        return 0;

    // At this point, the line must be in the list so increment the pointer
    while (curr_label < num_labels-1 && labels[curr_label] == labels[curr_label+1])
        curr_label++;
    retval = curr_label + 1;
    if (++curr_label == num_labels) curr_label--;
    
    return retval;
    */
}
