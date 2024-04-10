/*
 * opdefs.h
 * Copyright (c) 1996,1997 Shawn Silverman
 *
*/

#ifndef _OPDEFS_H_
#define _OPDEFS_H_

/* Pushing constants onto the stack */
#define BIPUSH	16
#define SIPUSH	17
#define LDC     18
#define LDC_W   19
#define LDC2_W  20
#define ACONST_NULL	1
#define ICONST_M1	2
#define ICONST_0	3
#define ICONST_1	4
#define ICONST_2	5
#define ICONST_3	6
#define ICONST_4	7
#define ICONST_5	8
#define LCONST_0	9
#define LCONST_1	10
#define FCONST_0	11
#define FCONST_1	12
#define FCONST_2	13
#define DCONST_0	14
#define DCONST_1	15

/* Loading local varibles onto the stack */
#define ILOAD	21
#define ILOAD_0	26
#define ILOAD_1	27
#define ILOAD_2	28
#define ILOAD_3	29
#define LLOAD	22
#define LLOAD_0	30
#define LLOAD_1	31
#define LLOAD_2	32
#define LLOAD_3	33
#define FLOAD	23
#define FLOAD_0	34
#define FLOAD_1	35
#define FLOAD_2	36
#define FLOAD_3	37
#define DLOAD	24
#define DLOAD_0	38
#define DLOAD_1	39
#define DLOAD_2	40
#define DLOAD_3	41
#define ALOAD	25
#define ALOAD_0	42
#define ALOAD_1	43
#define ALOAD_2	44
#define ALOAD_3	45

/* Storing stack values into local variables */
#define ISTORE	54
#define ISTORE_0	59
#define ISTORE_1	60
#define ISTORE_2	61
#define ISTORE_3	62
#define LSTORE	55
#define LSTORE_0	63
#define LSTORE_1	64
#define LSTORE_2	65
#define LSTORE_3	66
#define FSTORE	56
#define FSTORE_0	67
#define FSTORE_1	68
#define FSTORE_2	69
#define FSTORE_3	70
#define DSTORE	57
#define DSTORE_0	71
#define DSTORE_1	72
#define DSTORE_2	73
#define DSTORE_3	74
#define ASTORE	58
#define ASTORE_0	75
#define ASTORE_1	76
#define ASTORE_2	77
#define ASTORE_3	78
#define IINC	132

/* Wider index for loading, storing and incrementing */
#define WIDE	196

/* Managing arrays */
#define NEWARRAY	188

#define ANEWARRAY	189
#define MULTIANEWARRAY	197
#define ARRAYLENGTH	190
#define IALOAD	46
#define LALOAD	47
#define FALOAD	48
#define DALOAD	49
#define AALOAD	50
#define BALOAD	51
#define CALOAD	52
#define SALOAD	53
#define IASTORE	79
#define LASTORE	80
#define FASTORE	81
#define DASTORE	82
#define AASTORE	83
#define BASTORE	84
#define CASTORE	85
#define SASTORE	86

/* Stack instructions */
#define NOP	0
#define POP	87
#define POP2	88
#define DUP	89
#define DUP2	92
#define DUP_X1	90
#define DUP2_X1	93
#define DUP_X2	91
#define DUP2_X2	94
#define SWAP	95

/* Arithmetic instructions */
#define IADD	96
#define LADD	97
#define FADD	98
#define DADD	99
#define ISUB	100
#define LSUB	101
#define FSUB	102
#define DSUB	103
#define IMUL	104
#define LMUL	105
#define FMUL	106
#define DMUL	107
#define IDIV	108
#define LDIV	109
#define FDIV	110
#define DDIV	111
#define IREM	112
#define LREM	113
#define FREM	114
#define DREM	115
#define INEG	116
#define LNEG	117
#define FNEG	118
#define DNEG	119

/* Logical instructions */
#define ISHL	120
#define ISHR	122
#define IUSHR	124
#define LSHL	121
#define LSHR	123
#define LUSHR	125
#define IAND	126
#define LAND	127
#define IOR	128
#define LOR	129
#define IXOR	130
#define LXOR	131

/* Conversion operations */
#define I2L	133
#define I2F	134
#define I2D	135
#define L2I	136
#define L2F	137
#define L2D	138
#define F2I	139
#define F2L	140
#define F2D	141
#define D2I	142
#define D2L	143
#define D2F	144
#define INT2BYTE	145
#define INT2CHAR	146
#define INT2SHORT	147
#define I2B	145
#define I2C	146
#define I2S	147

/* Control transfer instructions */
#define IFEQ	153
#define IFNULL	198
#define IFLT	155
#define IFLE	158
#define IFNE	154
#define IFNONNULL	199
#define IFGT	157
#define IFGE	156
#define IF_ICMPEQ	159
#define IF_ICMPNE	160
#define IF_ICMPLT	161
#define IF_ICMPGT	163
#define IF_ICMPLE	164
#define IF_ICMPGE	162
#define LCMP	148
#define FCMPL	149
#define FCMPG	150
#define DCMPL	151
#define DCMPG	152
#define IF_ACMPEQ	165
#define IF_ACMPNE	166
#define GOTO	167
#define GOTO_W	200
#define JSR	168
#define JSR_W	201
#define RET	169
/*#define RET_W	209 */

/* Function return */
#define IRETURN	172
#define LRETURN	173
#define FRETURN	174
#define DRETURN	175
#define ARETURN	176
#define RETURN	177

/* Table jumping */
#define TABLESWITCH	170
#define LOOKUPSWITCH	171

/* Manipulating object fields */
#define PUTFIELD	181
#define GETFIELD	180
#define PUTSTATIC	179
#define GETSTATIC	178

/* Method invocation */
#define INVOKEVIRTUAL	182
#define INVOKESPECIAL	183
#define INVOKESTATIC	184
#define INVOKEINTERFACE	185

/* Exception handling */
#define ATHROW	191

/* Miscellaneous object operations */
#define NEW	187
#define CHECKCAST	192
#define INSTANCEOF	193

/* Monitors */
#define MONITORENTER	194
#define MONITOREXIT	195

/* unused */
#define XXXUNUSEDXXX	186

/* Reserved */
#define BREAKPOINT	202
#define IMPDEP1	254
#define IMPDEP2	255

/* _quick variants */
/*#define LDC_QUICK 203
#define LDC_W_QUICK 204
#define LDC2_W_QUICK 205
#define GETFIELD_QUICK 206
#define PUTFIELD_QUICK 207
#define GETFIELD2_QUICK 208
#define PUTFIELD2_QUICK 209
#define GETSTATIC_QUICK 210
#define PUTSTATIC_QUICK 211
#define GETSTATIC2_QUICK 212
#define PUTSTATIC2_QUICK 213
#define INVOKEVIRTUAL_QUICK 214
#define INVOKENONVIRTUAL_QUICK 215
#define INVOKESUPER_QUICK 216
#define INVOKESTATIC_QUICK 217
#define INVOKEINTERFACE_QUICK 218
#define INVOKEVIRTUALOBJECT_QUICK 219
#define INVOKEIGNORED_QUICK 220
#define NEW_QUICK 221
#define ANEWARRAY_QUICK 222
#define MULTIANEWARRAY_QUICK 223
#define CHECKCAST_QUICK 224
#define INSTANCEOF_QUICK 225
#define INVOKEVIRTUAL_QUICK_W 226
#define GETFIELD_QUICK_W 227
#define PUTFIELD_QUICK_W 228
#define FIRST_UNUSED_INDEX 229
#define SOFTWARE 254
#define HARDWARE 255*/

/*typedef enum {
    opc_nop,
    opc_aconst_null
    opc_iconst_m1
    opc_iconst_0
    opc_iconst_1
    opc_iconst_2
    opc_iconst_3
    opc_iconst_4
    opc_iconst_5
    opc_lconst_0,
    opc_lconst_1,
    opc_fconst_0,
    opc_fconst_1,
    opc_fconst_2,
    opc_dconst_0,
    opc_dconst_1,
    opc_bipush,
    opc_sipush,
    opc_ldc,
    opc_ldc_w,
    opc_ldc2_w,
    opc_iload,
    opc_lload,
    opc_fload,
    opc_dload,
    opc_aload,
    opc_iload_0,
    opc_iload_1,
    opc_iload_2,
    opc_iload_3,
    opc_lload_0,
    opc_lload_1,
    opc_lload_2,
    opc_lload_3,
    opc_fload_0,
    opc_fload_1,
    opc_fload_2,
    opc_fload_3,
    opc_dload_0,
    opc_dload_1,
    opc_dload_2,
    opc_dload_3,
    opc_aload_0,
    opc_aload_1,
    opc_aload_2,
    opc_aload_3,
    opc_iaload,
    opc_laload,
    opc_faload,
    opc_daload,
    opc_aaload,
    opc_baload,
    opc_caload,
    opc_saload,
    opc_istore,
    opc_lstore,
    opc_fstore,
    opc_dstore,
    opc_astore,
    opc_istore_0,
    opc_istore_1,
    opc_istore_2,
    opc_istore_3,
    opc_lstore_0,
    opc_lstore_1,
    opc_lstore_2,
    opc_lstore_3,
    opc_fstore_0,
    opc_fstore_1,
    opc_fstore_2,
    opc_fstore_3,
    opc_dstore_0,
    opc_dstore_1,
    opc_dstore_2,
    opc_dstore_3,
    opc_astore_0,
    opc_astore_1,
    opc_astore_2,
    opc_astore_3,
    opc_iastore,
    opc_lastore,
    opc_fastore,
    opc_dastore,
    opc_aastore,
    opc_bastore,
    opc_castore,
    opc_sastore,
    opc_pop,
    opc_pop2,
    opc_dup,
    opc_dup_x1,
    opc_dup_x2,
    opc_dup2,
    opc_dup2_x1,
    opc_dup2_x2,
    opc_swap,
    opc_iadd,
    opc_ladd,
    opc_fadd,
    opc_dadd,
    opc_isub,
    opc_lsub,
    opc_fsub,
    opc_dsub,
    opc_imul,
    opc_lmul,
    opc_fmul,
    opc_dmul,
    opc_idiv,
    opc_ldiv,
    opc_fdiv,
    opc_ddiv,
    opc_irem,
    opc_lrem,
    opc_frem,
    opc_drem,
    opc_ineg,
    opc_lneg,
    opc_fneg,
    opc_dneg,
    opc_ishl,
    opc_lshl,
    opc_ishr,
    opc_lshr,
    opc_iushr,
    opc_lushr,
    opc_iand,
    opc_land,
    opc_ior,
    opc_lor,
    opc_ixor,
    opc_lxor,
    opc_iinc,
    opc_i2l,
    opc_i2f,
    opc_i2d,
    opc_l2i,
    opc_l2f,
    opc_l2d,
    opc_f2i,
    opc_f2l,
    opc_f2d,
    opc_d2i,
    opc_d2l,
    opc_d2f,
    opc_int2byte,
    opc_int2char,
    opc_int2short,
    //i2b,
    //i2c,
    //i2s,
    opc_lcmp,
    opc_fcmpl,
    opc_fcmpg,
    opc_dcmpl,
    opc_dcmpg,
    opc_ifeq,
    opc_ifne,
    opc_iflt,
    opc_ifge,
    opc_ifgt,
    opc_ifle,
    opc_if_icmpeq,
    opc_if_icmpne,
    opc_if_icmplt,
    opc_if_icmpge,
    opc_if_icmpgt,
    opc_if_icmple,
    opc_if_acmpeq,
    opc_if_acmpne,
    opc_goto,
    opc_jsr,
    opc_ret,
    opc_tableswitch,
    opc_lookupswitch,
    opc_ireturn,
    opc_lreturn,
    opc_freturn,
    opc_dreturn,
    opc_areturn,
    opc_return,
    opc_getstatic,
    opc_putstatic,
    opc_getfield,
    opc_putfield,
    opc_invokevirtual,
    opc_invokenonvirtual,
    //invokespecial,
    opc_invokestatic,
    opc_invokeinterface,
    opc_xxxunusedxxx,
    opc_new,
    opc_newarray,
    opc_anewarray,
    opc_arraylength,
    opc_athrow,
    opc_checkcast,
    opc_instanceof,
    opc_monitorenter,
    opc_monitorexit,
    opc_wide,
    opc_multianewarray,
    opc_ifnull,
    opc_ifnonnull,
    opc_goto_w,
    opc_jsr_w,
    opc_breakpoint
} Opcode;*/

/*typedef enum {
    iop_push,
    iop_pop,
    iop_inc,
    iop_length,
    iop_nop,
    iop_drop,
    iop_dup,
    iop_swap,
    iop_convert,
    iop_if,
    iop_compare,
    iop_goto,
    iop_finalize,
    iop_endfinalize,
    iop_return,
    iop_switch,
    iop_invoke,
    iop_throw,
    iop_new,
    iop_lock,
    iop_unlock,
    iop_cast,
    iop_instanceof,

    iop_add,
    iop_sub,
    iop_mul,
    iop_div,
    iop_rem,
    iop_neg,
    iop_shl,
    iop_shr,
    iop_ushr,
    iop_and,
    iop_or,
    iop_xor
} IOpcode;*/

/*typedef enum {
    iop_asgn,
    iop_jmp,
    iop_jcond,
    iop_call,
    iop_ret,
    iop_push,
    iop_pop,
    iop_switch,
    iop_swap,
    iop_try,
    iop_finalize,
    iop_throw,
    iop_lock,
    iop_unlock,
    iop_cast,
    iop_instaceof
} IOpcode;*/

/*
// Higher level opcodes
#define OP_ASGN	0
#define OP_JMP	1
#define OP_JCOND	2
#define OP_CALL	3
#define OP_RET	4
#define OP_PUSH	5
#define OP_POP	6

#define OP_SWITCH	7
*/

/*
// Associated stack values
#define BYTE	'B'
#define CHAR	'C'
#define DOUBLE	'D'
#define FLOAT	'F'
#define INT	'I'
#define LONG	'J'
#define OBJECT	'A'
#define SHORT	'S'
#define BOOLEAN	'Z'
*/

#endif /* !_OPDEFS_H_ */
