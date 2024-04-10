/*
 * shconst.c
 * Copyright (c) 1996,1997 Shawn Silverman
 *
*/

#include <stdio.h>
#include "d-java.h"

void showConstant(ClassFile *cf, u2 index)
{
    switch (cf->constant_pool[index].tag) {
	case CONSTANT_Class:
	    showConstantClass(cf, index);
	    break;
	case CONSTANT_Fieldref:
	    showConstantFieldref(cf, index);
	    break;
	case CONSTANT_Methodref:
	    showConstantMethodref(cf, index);
	    break;
	case CONSTANT_InterfaceMethodref:
	    showConstantInterfaceMethodref(cf, index);
	    break;
	case CONSTANT_String:
	    showConstantString(cf, index);
	    break;
	case CONSTANT_Integer:
	    showConstantInteger(cf, index);
	    break;
	case CONSTANT_Float:
	    showConstantFloat(cf, index);
	    break;
	case CONSTANT_Long:
	    showConstantLong(cf, index);
	    break;
	case CONSTANT_Double:
	    showConstantDouble(cf, index);
	    break;
	case CONSTANT_NameAndType:
	    showConstantNameAndType(cf, index);
	    break;
	case CONSTANT_Utf8:
	    showConstantUtf8(cf, index, FALSE);
	    break;
	default:
	    break;
	    /* return ERR_UNDEFINED_CONSTANT; */
	}
}

void showConstantClass(ClassFile *cf, u2 index)
{
    /* ANEWARRAY and MULTIANEWARRAY show classes as descriptors */
    if (*(char *)cf->constant_pool[cf->constant_pool[index].index1].item.bytes == '[')
        showDescriptorNoArgs(cf, cf->constant_pool[index].index1);
    else
        showConstantUtf8(cf, cf->constant_pool[index].index1, TRUE);
}

void showConstantFieldref(ClassFile *cf, u2 index)
{
    showConstantClass(cf, cf->constant_pool[index].index1);
    putchar('.');
    showConstantNameAndType(cf, cf->constant_pool[index].index2);
}

void showConstantMethodref(ClassFile *cf, u2 index)
{
    showConstantClass(cf, cf->constant_pool[index].index1);
    putchar('.');
    showConstantNameAndType(cf, cf->constant_pool[index].index2);
}

void showConstantInterfaceMethodref(ClassFile *cf, u2 index)
{
    showConstantClass(cf, cf->constant_pool[index].index1);
    putchar('.');
    showConstantNameAndType(cf, cf->constant_pool[index].index2);
}

void showConstantString(ClassFile *cf, u2 index)
{
    putchar('\"');
    showConstantUtf8(cf, cf->constant_pool[index].index1, FALSE);
    putchar('\"');
}

void showConstantInteger(ClassFile *cf, u2 index)
{
    printf("%d", cf->constant_pool[index].item.i);
}

void showConstantFloat(ClassFile *cf, u2 index)
{
    float f = cf->constant_pool[index].item.f;
    /* The version of DJGPP I'm using gives an error when trying to
       print NaN */
    if (f != f)
        printf("NaN");
    else
        printf("%f", f);
}

void showConstantLong(ClassFile *cf, u2 index)
{
    char num[65];

    printf("%s", lltoa(cf->constant_pool[index].item.l, num, 10));
}

void showConstantDouble(ClassFile *cf, u2 index)
{
    double d = cf->constant_pool[index].item.d;
    /* The version of DJGPP I'm using gives an error when trying to
       print NaN */
    if (d != d)
        printf("NaN");
    else
        printf("%f", d);
}

void showConstantNameAndType(ClassFile *cf, u2 index)
{
    showConstantUtf8(cf, cf->constant_pool[index].index1, FALSE);
    if (*(char *)cf->constant_pool[cf->constant_pool[index].index2].item.bytes == '(') {
        putchar('(');
        showDescriptorArgs(cf, cf->constant_pool[index].index2);
        putchar(')');
    }
    putchar(':');
    showDescriptorNoArgs(cf, cf->constant_pool[index].index2);
}

void showConstantUtf8(ClassFile *cf, u2 index, int fullclassname)
{
    showUtf8(cf->constant_pool[index].item.bytes, fullclassname);
}

/*void showConstantUnicode(ClassFile *cf, u2 index)
{
    u2 *bytes = (u2 *)cf->constant_pool[index].item.bytes;

    while (*bytes) {
	if (*bytes <= 0x7F && *bytes != 0x00) {
	    switch (*bytes) {
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

	else {
	    putchar('\\');
	    if (*bytes <= 0xFF)
		printf("x%02X", *bytes);
	    else
		printf("u%04X", *bytes);
	}
	
	bytes++;
    }
}*/
