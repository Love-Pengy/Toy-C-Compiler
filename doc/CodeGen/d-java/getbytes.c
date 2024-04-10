/*
 * getbytes.c
 * Copyright (c) 1996,1997 Shawn Silverman
 *
*/

#include <stdio.h>
#include "d-java.h"

static int ch;

int get_signed_byte(FILE *fp, s1 *data)
{
    if ((ch = getc(fp)) == EOF) {
        if (feof(fp)) return ERR_EOF;
        return ERR_READ;
    }
    *data = (s1) ch;
    return ERR_OK;
}

int get_unsigned_byte(FILE *fp, u1 *data)
{
    if ((ch = getc(fp)) == EOF) {
        if (feof(fp)) return ERR_EOF;
        return ERR_READ;
    }
    *data = (u1) ch;
    return ERR_OK;
}

int get_signed_word(FILE *fp, s2 *data)
{
    if ((ch = getc(fp)) == EOF) {
        if (feof(fp)) return ERR_EOF;
        return ERR_READ;
    }
    *data = (s2) ch;
    if ((ch = getc(fp)) == EOF) {
        if (feof(fp)) return ERR_EOF;
        return ERR_READ;
    }
    *data = *data << 8 | (s2) ch;
    return ERR_OK;
}

int get_unsigned_word(FILE *fp, u2 *data)
{
    if ((ch = getc(fp)) == EOF) {
        if (feof(fp)) return ERR_EOF;
        return ERR_READ;
    }
    *data = (u2) ch;
    if ((ch = getc(fp)) == EOF) {
        if (feof(fp)) return ERR_EOF;
        return ERR_READ;
    }
    *data = *data << 8 | (u2) ch;
    return ERR_OK;
}

int get_signed_dword(FILE *fp, s4 *data)
{
    if ((ch = getc(fp)) == EOF) {
        if (feof(fp)) return ERR_EOF;
        return ERR_READ;
    }
    *data = (s4) ch;
    if ((ch = getc(fp)) == EOF) {
        if (feof(fp)) return ERR_EOF;
        return ERR_READ;
    }
    *data = *data << 8 | (s4) ch;
    if ((ch = getc(fp)) == EOF) {
        if (feof(fp)) return ERR_EOF;
        return ERR_READ;
    }
    *data = *data << 8 | (s4) ch;
    if ((ch = getc(fp)) == EOF) {
        if (feof(fp)) return ERR_EOF;
        return ERR_READ;
    }
    *data = *data << 8 | (s4) ch;
    return ERR_OK;
}

int get_unsigned_dword(FILE *fp, u4 *data)
{
    if ((ch = getc(fp)) == EOF) {
        if (feof(fp)) return ERR_EOF;
        return ERR_READ;
    }
    *data = (s4) ch;
    if ((ch = getc(fp)) == EOF) {
        if (feof(fp)) return ERR_EOF;
        return ERR_READ;
    }
    *data = *data << 8 | (u4) ch;
    if ((ch = getc(fp)) == EOF) {
        if (feof(fp)) return ERR_EOF;
        return ERR_READ;
    }
    *data = *data << 8 | (u4) ch;
    if ((ch = getc(fp)) == EOF) {
        if (feof(fp)) return ERR_EOF;
        return ERR_READ;
    }
    *data = *data << 8 | (u4) ch;
    return ERR_OK;
}

int get_bytes(FILE *fp, u1 *data, u4 length)
{
    /*u4 i;*/
    size_t items;
    size_t new_length = (size_t)length;
    
    do {
        items = fread(data, 1, new_length, fp);
        if (items == -1 || (items == 0 && new_length != 0)) {
            /*fprintf(stderr, "ftell(fp) = %ld\n", ftell(fp));*/
            return ERR_READ;
        }
        data += items;
        new_length -= items;
    } while (new_length != 0);
    
    /*for (i=0; i<length; i++) {
        if ((ch = getc(fp)) == EOF) return ERR_EOF;
        *data++ = (u1) ch;
    }*/
    
    return ERR_OK;
}
