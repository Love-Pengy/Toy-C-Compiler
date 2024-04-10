/*
 * opcodes.c
 * Copyright (c) 1996,1997 Shawn Silverman
 *
*/

char *opcode_name[256] = {
    "nop","aconst_null","iconst_m1","iconst_0","iconst_1",
    "iconst_2","iconst_3","iconst_4","iconst_5","lconst_0",
    "lconst_1","fconst_0","fconst_1","fconst_2","dconst_0",
    "dconst_1","bipush","sipush","ldc","ldc_w",
    "ldc2_w","iload","lload","fload","dload",
    "aload","iload_0","iload_1","iload_2","iload_3",
    "lload_0","lload_1","lload_2","lload_3","fload_0",
    "fload_1","fload_2","fload_3","dload_0","dload_1",
    "dload_2","dload_3","aload_0","aload_1","aload_2",
    "aload_3","iaload","laload","faload","daload",
    "aaload","baload","caload","saload","istore",
    "lstore","fstore","dstore","astore","istore_0",
    "istore_1","istore_2","istore_3","lstore_0","lstore_1",
    "lstore_2","lstore_3","fstore_0","fstore_1","fstore_2",
    "fstore_3","dstore_0","dstore_1","dstore_2","dstore_3",
    "astore_0","astore_1","astore_2","astore_3","iastore",
    "lastore","fastore","dastore","aastore","bastore",
    "castore","sastore","pop","pop2","dup",
    "dup_x1","dup_x2","dup2","dup2_x1","dup2_x2",
    "swap","iadd","ladd","fadd","dadd",
    "isub","lsub","fsub","dsub","imul",
    "lmul","fmul","dmul","idiv","ldiv",
    "fdiv","ddiv","irem","lrem","frem",
    "drem","ineg","lneg","fneg","dneg",
    "ishl","lshl","ishr","lshr","iushr",
    "lushr","iand","land","ior","lor",
    "ixor","lxor","iinc","i2l","i2f",
    "i2d","l2i","l2f","l2d","f2i",
    "f2l","f2d","d2i","d2l","d2f",
    "i2b","i2c","i2s","lcmp","fcmpl",
    "fcmpg","dcmpl","dcmpg","ifeq","ifne",
    "iflt","ifge","ifgt","ifle","if_icmpeq",
    "if_icmpne","if_icmplt","if_icmpge","if_icmpgt","if_icmple",
    "if_acmpeq","if_acmpne","goto","jsr","ret",
    "tableswitch","lookupswitch","ireturn","lreturn","freturn",
    "dreturn","areturn","return","getstatic","putstatic",
    "getfield","putfield","invokevirtual","invokespecial","invokestatic",
    "invokeinterface","xxxunusedxxx","new","newarray","anewarray",
    "arraylength","athrow","checkcast","instanceof","monitorenter",
    "monitorexit","wide","multianewarray","ifnull","ifnonnull",
    "goto_w","jsr_w","breakpoint","NO_OPCODE","NO_OPCODE",
    "NO_OPCODE","NO_OPCODE","NO_OPCODE","NO_OPCODE","NO_OPCODE",
    "NO_OPCODE","NO_OPCODE","NO_OPCODE","NO_OPCODE","NO_OPCODE",
    "NO_OPCODE","NO_OPCODE","NO_OPCODE","NO_OPCODE","NO_OPCODE",
    "NO_OPCODE","NO_OPCODE","NO_OPCODE","NO_OPCODE","NO_OPCODE",
    "NO_OPCODE","NO_OPCODE","NO_OPCODE","NO_OPCODE","NO_OPCODE",
    "NO_OPCODE","NO_OPCODE","NO_OPCODE","NO_OPCODE","NO_OPCODE",
    "NO_OPCODE","NO_OPCODE","NO_OPCODE","NO_OPCODE","NO_OPCODE",
    "NO_OPCODE","NO_OPCODE","NO_OPCODE","NO_OPCODE","NO_OPCODE",
    "NO_OPCODE","NO_OPCODE","NO_OPCODE","NO_OPCODE","NO_OPCODE",
    "NO_OPCODE","NO_OPCODE","NO_OPCODE","NO_OPCODE","impdep1",
    "impdep2"
};

short opcode_length[256] = {
    1,  /* nop */
    1,  /* aconst_null */
    1,  /* iconst_m1 */
    1,  /* iconst_0 */
    1,  /* iconst_1 */
    1,  /* iconst_2 */
    1,  /* iconst_3 */
    1,  /* iconst_4 */
    1,  /* iconst_5 */
    1,  /* lconst_0 */
    1,  /* lconst_1 */
    1,  /* fconst_0 */
    1,  /* fconst_1 */
    1,  /* fconst_2 */
    1,  /* dconst_0 */
    1,  /* dconst_1 */
    2,  /* bipush */
    3,  /* sipush */
    2,  /* ldc */
    3,  /* ldc_w */
    3,  /* ldc2_w */
    2,  /* iload */
    2,  /* lload */
    2,  /* fload */
    2,  /* dload */
    2,  /* aload */
    1,  /* iload_0 */
    1,  /* iload_1 */
    1,  /* iload_2 */
    1,  /* iload_3 */
    1,  /* lload_0 */
    1,  /* lload_1 */
    1,  /* lload_2 */
    1,  /* lload_3 */
    1,  /* fload_0 */
    1,  /* fload_1 */
    1,  /* fload_2 */
    1,  /* fload_3 */
    1,  /* dload_0 */
    1,  /* dload_1 */
    1,  /* dload_2 */
    1,  /* dload_3 */
    1,  /* aload_0 */
    1,  /* aload_1 */
    1,  /* aload_2 */
    1,  /* aload_3 */
    1,  /* iaload */
    1,  /* laload */
    1,  /* faload */
    1,  /* daload */
    1,  /* aaload */
    1,  /* baload */
    1,  /* caload */
    1,  /* saload */
    2,  /* istore */
    2,  /* lstore */
    2,  /* fstore */
    2,  /* dstore */
    2,  /* astore */
    1,  /* istore_0 */
    1,  /* istore_1 */
    1,  /* istore_2 */
    1,  /* istore_3 */
    1,  /* lstore_0 */
    1,  /* lstore_1 */
    1,  /* lstore_2 */
    1,  /* lstore_3 */
    1,  /* fstore_0 */
    1,  /* fstore_1 */
    1,  /* fstore_2 */
    1,  /* fstore_3 */
    1,  /* dstore_0 */
    1,  /* dstore_1 */
    1,  /* dstore_2 */
    1,  /* dstore_3 */
    1,  /* astore_0 */
    1,  /* astore_1 */
    1,  /* astore_2 */
    1,  /* astore_3 */
    1,  /* iastore */
    1,  /* lastore */
    1,  /* fastore */
    1,  /* dastore */
    1,  /* aastore */
    1,  /* bastore */
    1,  /* castore */
    1,  /* sastore */
    1,  /* pop */
    1,  /* pop2 */
    1,  /* dup */
    1,  /* dup_x1 */
    1,  /* dup_x2 */
    1,  /* dup2 */
    1,  /* dup2_x1 */
    1,  /* dup2_x2 */
    1,  /* swap */
    1,  /* iadd */
    1,  /* ladd */
    1,  /* fadd */
    1,  /* dadd */
    1,  /* isub */
    1,  /* lsub */
    1,  /* fsub */
    1,  /* dsub */
    1,  /* imul */
    1,  /* lmul */
    1,  /* fmul */
    1,  /* dmul */
    1,  /* idiv */
    1,  /* ldiv */
    1,  /* fdiv */
    1,  /* ddiv */
    1,  /* irem */
    1,  /* lrem */
    1,  /* frem */
    1,  /* drem */
    1,  /* ineg */
    1,  /* lneg */
    1,  /* fneg */
    1,  /* dneg */
    1,  /* ishl */
    1,  /* lshl */
    1,  /* ishr */
    1,  /* lshr */
    1,  /* iushr */
    1,  /* lushr */
    1,  /* iand */
    1,  /* land */
    1,  /* ior */
    1,  /* lor */
    1,  /* ixor */
    1,  /* lxor */
    3,  /* iinc */
    1,  /* i2l */
    1,  /* i2f */
    1,  /* i2d */
    1,  /* l2i */
    1,  /* l2f */
    1,  /* l2d */
    1,  /* f2i */
    1,  /* f2l */
    1,  /* f2d */
    1,  /* d2i */
    1,  /* d2l */
    1,  /* d2f */
    1,  /* i2b */
    1,  /* i2c */
    1,  /* i2s */
    1,  /* lcmp */
    1,  /* fcmpl */
    1,  /* fcmpg */
    1,  /* dcmpl */
    1,  /* dcmpg */
    3,  /* ifeq */
    3,  /* ifne */
    3,  /* iflt */
    3,  /* ifge */
    3,  /* ifgt */
    3,  /* ifle */
    3,  /* if_icmpeq */
    3,  /* if_icmpne */
    3,  /* if_icmplt */
    3,  /* if_icmpge */
    3,  /* if_icmpgt */
    3,  /* if_icmple */
    3,  /* if_acmpeq */
    3,  /* if_acmpne */
    3,  /* goto */
    3,  /* jsr */
    2,  /* ret */
    99,  /* tableswitch */
    99,  /* lookupswitch */
    1,  /* ireturn */
    1,  /* lreturn */
    1,  /* freturn */
    1,  /* dreturn */
    1,  /* areturn */
    1,  /* return */
    3,  /* getstatic */
    3,  /* putstatic */
    3,  /* getfield */
    3,  /* putfield */
    3,  /* invokevirtual */
    3,  /* invokespecial */
    3,  /* invokestatic */
    5,  /* invokeinterface */
    1,  /* (unused) */
    3,  /* new */
    2,  /* newarray */
    3,  /* anewarray */
    1,  /* arraylength */
    1,  /* athrow */
    3,  /* checkcast */
    3,  /* instanceof */
    1,  /* monitorenter */
    1,  /* monitorexit */
    1,  /* wide */
    4,  /* multianewarray */
    3,  /* ifnull */
    3,  /* ifnonnull */
    5,  /* goto_w */
    5,  /* jsr_w */
    1,  /* breakpoint */
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
};
