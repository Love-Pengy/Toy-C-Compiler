/*
 * clconst.h
 * Copyright (c) 1996,1997 Shawn Silverman
 *
*/

/* Magic */
#define MAGIC	0xCAFEBABE

/* Access_flags */
#define ACC_PUBLIC	0X0001
#define ACC_PRIVATE	0X0002
#define ACC_PROTECTED	0X0004
#define ACC_STATIC	0X0008
#define ACC_FINAL	0X0010
#define ACC_SUPER	0x0020
#define ACC_SYNCHRONIZED	0X0020
#define ACC_VOLATILE	0X0040
#define ACC_TRANSIENT	0X0080
#define ACC_NATIVE	0X0100
#define ACC_INTERFACE	0X0200
#define ACC_ABSTRACT	0X0400

/* newarray types */
#define T_CLASS	2
#define T_BOOLEAN	4
#define T_CHAR	5
#define T_FLOAT	6
#define T_DOUBLE	7
#define T_BYTE	8
#define T_SHORT	9
#define T_INT	10
#define T_LONG	11

/* Constant pool */
#define CONSTANT_Class		7
#define CONSTANT_Fieldref	9
#define CONSTANT_Methodref	10
#define CONSTANT_InterfaceMethodref	11
#define CONSTANT_String		8
#define CONSTANT_Integer	3
#define CONSTANT_Float		4
#define CONSTANT_Long		5
#define CONSTANT_Double		6
#define CONSTANT_NameAndType	12
#define CONSTANT_Utf8		1

/* Signatures */
#define SIG_BYTE	'B'
#define SIG_CHAR	'C'
#define SIG_DOUBLE	'D'
#define SIG_FLOAT	'F'
#define SIG_INT	'I'
#define SIG_LONG	'J'
#define SIG_CLASS	'L'
#define SIG_SHORT	'S'
#define SIG_BOOLEAN	'Z'
#define SIG_ARRAY	'['
#define SIG_VOID	'V'
#define SIG_ENDCLASS	';'
#define SIG_METHOD	'('
#define SIG_ENDMETHOD	')'
#define SIG_PACKAGE	'/'
