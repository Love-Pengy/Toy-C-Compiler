/*
 * clstruct.h
 * Copyright (c) 1996,1997 Shawn Silverman
 *
*/

/*typedef struct {
    u2 index;
    unsigned char *utf8;
    unsigned char *string;
} utf8;*/

/* Constant pool */
/*typedef struct {
    u1 tag;
    u2 name_index;
} CONSTANT_Class_info;

typedef struct {
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
} CONSTANT_Fieldref_info;

typedef struct {
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
} CONSTANT_Methodref_info;

typedef struct {
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
} CONSTANT_MethodInterfaceref_info;

typedef struct {
    u1 tag;
    u2 string_index;
} CONSTANT_String_info;

typedef struct {
    u1 tag;
    u4 bytes;
} CONSTANT_Integer_info;

typedef struct {
    u1 tag;
    u4 bytes;
} CONSTANT_Float_info;

typedef struct {
    u1 tag;
    u4 high_bytes;
    u4 low_bytes;
} CONSTANT_Long_info;

typedef struct {
    u1 tag;
    u4 high_bytes;
    u4 low_bytes;
} CONSTANT_Double_info;

typedef struct {
    u1 tag;
    u2 name_index;
    u2 descriptor_index;
} CONSTANT_NameAndType_info;

typedef struct {
    u1 tag;
    u2 length;
    u1 *bytes;
} CONSTANT_Utf8_info;

typedef struct {
    u1 tag;
    u2 length;
    u2 *bytes;
} CONSTANT_Unicode_info;*/

struct tagGenericAttribute_info;
struct tagSourceFile_attribute;
struct tagConstantValue_attribute;
struct tagCode_attribute;
struct tagExceptions_attribute;
struct tagLineNumberTable_attribute;
struct tagLocalVariableTable_attribute;
typedef union {
    unsigned char *pointer;
    struct tagGenericAttribute_info *ga;
    struct tagSourceFile_attribute *sf;
    struct tagConstantValue_attribute *cv;
    struct tagCode_attribute *c;
    struct tagExceptions_attribute *e;
    struct tagLineNumberTable_attribute *lnt;
    struct tagLocalVariableTable_attribute *lvt;
} attribute_info;

/* Fields */

typedef struct {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info *attributes;
} field_info;

/* Attributes */

typedef struct tagGenericAttribute_info {
    u2 attribute_name;
    u4 attribute_length;
    u1 info[1];
} GenericAttribute_info;

typedef struct tagSourceFile_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 sourcefile_index;
} SourceFile_attribute;

typedef struct tagConstantValue_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 constantvalue_index;
} ConstantValue_attribute;

typedef struct {
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
} exception_table_info;
typedef struct tagCode_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1 *code;
    u2 exception_table_length;
    exception_table_info *exception_table;
    u2 attributes_count;
    attribute_info *attributes;
} Code_attribute;

typedef struct tagExceptions_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 number_of_exceptions;
    u2 *exception_index_table;
} Exceptions_attribute;

typedef struct {
    u2 start_pc;
    u2 line_number;
} line_number_table_info;
typedef struct tagLineNumberTable_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 line_number_table_length;
    line_number_table_info *line_number_table;
} LineNumberTable_attribute;

typedef struct {
    u2 start_pc;
    u2 length;
    u2 name_index;
    u2 descriptor_index;
    u2 index;
} local_variable_table_info;
typedef struct tagLocalVariableTable_attribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 local_variable_table_length;
    local_variable_table_info *local_variable_table;
} LocalVariableTable_attribute;

/* Methods */

typedef struct {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info *attributes;
} method_info;


/* ClassFile definition */

typedef struct {
    u1 tag;
    long fpos;
    u2 index1;
    u2 index2;
    u2 length;
    union {
	int i;  /* 4 bytes */
	float f;  /* 4 bytes */
	long long l;  /* 8 bytes */
	double d;  /* 8 bytes */
        u1 *bytes;
    } item;
} cp_info;

typedef struct {
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    cp_info *constant_pool;
    u2 access_flags;
    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    u2 *interfaces;
    u2 fields_count;
    field_info *fields;
    u2 methods_count;
    method_info *methods;
    u2 attributes_count;
    attribute_info *attributes;
} ClassFile;
