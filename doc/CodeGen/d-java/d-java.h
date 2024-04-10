/*
 * d-java.h
 * Copyright (c) 1996,1997 Shawn Silverman
 *
*/

#include <stdio.h>

/* typedefs */
/* these particular ones are for DJGPP */
typedef unsigned char	u1;
typedef unsigned short	u2;
typedef unsigned int	u4;

typedef signed char	s1;
typedef signed short	s2;
typedef signed int	s4;
typedef signed long long s8;

/* constant defs */
/* used for escape sequences in strings */
#define BS		0x08
#define TAB		0x09
#define LF		0x0A
#define FF		0x0C
#define CR		0x0D
#define BACKSLASH	0x5C
#define SINGQUOTE	0x27
#define DOUBQUOTE	0x22

#define TRUE  1
#define FALSE 0

#define CHECK_STATUS(f) if ((status = (f)) != ERR_OK) return status

/* Error constants */
#define ERR_OK		0
#define ERR_USAGE	1
#define ERR_OPEN	2
#define ERR_CLOSE	3
#define ERR_EOF		4
#define ERR_NOT_CLASS_FILE	5
#define ERR_ZERO_CONSTANT_POOL	6
#define ERR_UNDEFINED_CONSTANT	7
#define ERR_INVALID_CP_INDEX	8
#define ERR_ZERO_CODE_LENGTH	9
#define ERR_READ	10
#define ERR_MEM		11
#define ERR_FIELD_TYPE	12
#define ERR_UNDEFINED_OPCODE	13
#define ERR_NO_BB	14

/* Constants for dealing with the classfile */
#include "clconst.h"
/* Classfile structures */
#include "clstruct.h"
/* Opcode constants */
#include "opdefs.h"

/* Options */
typedef struct {
    unsigned showLVT    	: 1;
    unsigned showLNT    	: 1;
    unsigned jasmin     	: 1;
    unsigned javaa      	: 1;
    unsigned verbose    	: 1;
    unsigned fieldsOnly		: 1;
    unsigned redirect_stderr	: 1;
    unsigned attributesOnly	: 1;
    unsigned decompile		: 1;
    unsigned indent		: 6;
} Options;

/* Global variables */
extern Options options;
extern FILE *errfile;
extern int status;
extern char *err_string[];
extern char *opcode_name[256];
extern short opcode_length[256];
extern char *packages[];
extern u4 *labels;
extern u4 num_labels;

/* Exported functions from d-java.c */
void print_info(FILE *);
void print_info_jasmin(FILE *);

/* Exported functions from getbytes.c */
int get_signed_byte(FILE *, s1 *);
int get_unsigned_byte(FILE *, u1 *);
int get_signed_word(FILE *, s2 *);
int get_unsigned_word(FILE *, u2 *);
int get_signed_dword(FILE *, s4 *);
int get_unsigned_dword(FILE *, u4 *);
int get_bytes(FILE *, unsigned char *, u4);

#define CHECK_U1(field)\
 if ((status = get_unsigned_byte(fp, &(field))) != ERR_OK) return status
#define CHECK_U2(field)\
 if ((status = get_unsigned_word(fp, &(field))) != ERR_OK) return status
#define CHECK_U4(field)\
 if ((status = get_unsigned_dword(fp, &(field))) != ERR_OK) return status
#define CHECK_S1(field)\
 if ((status = get_signed_byte(fp, &(field))) != ERR_OK) return status
#define CHECK_S2(field)\
 if ((status = get_signed_word(fp, &(field))) != ERR_OK) return status
#define CHECK_S4(field)\
 if ((status = get_signed_dword(fp, &(field))) != ERR_OK) return status
#define CHECK_BYTES(field, length)\
 if ((status = get_bytes(fp, field, length)) != ERR_OK) return status

/* Exported functions from labels.c */
u4 scanForLabels(ClassFile *, Code_attribute *);
u4 insertLabels(ClassFile *, Code_attribute *, u4 []);
u4 getLabel(u4 [], u4, u4);

/* Exported functions from lltoa.c */
char *lltoa(long long, char *, int);

/* Exported functions from reclass.c */
int readClassFile(FILE *, ClassFile **);
void freeClassFile(ClassFile *);

/* Exported functions from shattrib.c */
void showAttributeSourceFile(ClassFile *, SourceFile_attribute *);
void showAttributeConstantValue(ClassFile *, ConstantValue_attribute *);
void showAttributeExceptions(ClassFile *, Exceptions_attribute *);
void showAttributeCode(ClassFile *, Code_attribute *);
void showAttributeLineNumberTable(ClassFile *, LineNumberTable_attribute *);
void showAttributeLocalVariableTable(ClassFile *, LocalVariableTable_attribute *);

/* Exported functions from shclass.c */
int showClassFile(ClassFile *);
u4 nextOpcode(u1 *, u4);
void showAccessFlags(u2);
short getPadding(u4);
void showCode(ClassFile *, Code_attribute *);
void showDescriptorNoArgs(ClassFile *, u2);
void showDescriptorArgs(ClassFile *, u2);
void showUtf8(u1 *, short);
u2 u1tou2(u1 *);
s2 u1tos2(u1 *);
s4 u1tos4(u1 *);

/* Exported functions from shconst.c */
void showConstant(ClassFile *, u2);
void showConstantClass(ClassFile *, u2);
void showConstantFieldref(ClassFile *, u2);
void showConstantMethodref(ClassFile *, u2);
void showConstantInterfaceMethodref(ClassFile *, u2);
void showConstantString(ClassFile *, u2);
void showConstantInteger(ClassFile *, u2);
void showConstantFloat(ClassFile *, u2);
void showConstantLong(ClassFile *, u2);
void showConstantDouble(ClassFile *, u2);
void showConstantNameAndType(ClassFile *, u2);
void showConstantUtf8(ClassFile *, u2, int);
void showConstantUnicode(ClassFile *, u2);

/* Exported functions from shjasmin.c */
int showClassFile_jasmin(ClassFile *);

/* Decompilation stuff */
#define ONEWAY_NODE		1
#define TWOWAY_NODE		2
#define NWAY_NODE		3
#define FALL_NODE		4
#define INVOKE_NODE		5
#define RETURN_NODE		6

#define TRY_NODE		7
#define FINALLY_NODE		8
#define CATCH_NODE		9

#define SYNCH_NODE		10
#define ENDSYNCH_NODE		11

#define INTERVAL_NODE		12

#define NULL_NODE		0

/* These traversal flags must not equal 0 */
#define DFS_JMP		1
#define DFS_NUM		2

/*typedef struct _BB {
    short nodeType;
    
    int traversed;
    int index;

    int numInEdges;
    struct _BB **inEdges;
    int numOutEdges;
    union _edge {
        u4 pc;
        struct _BB *pBB;
    } *outEdges;
    
    u4 start_pc;
    u4 length;
    
    int dfsNumber;
    
    struct _BB *next;
} BB;
typedef BB *PBB;

typedef struct _Method {
    BB cfg;
    int numCFGs;
    
    
    PBB *dfsNum;
    int numBBs;
    
    ClassFile *cf;
    Code_attribute *c;
} Method;
typedef Method *PMethod;*/

/* Exported functions from frontend.c */
/*int createCFG(PMethod);
void freeCFG(PBB);*/

/* Exported functions from decomp.c */
/*int decompileClassFile(ClassFile *);*/
