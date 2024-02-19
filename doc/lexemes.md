+ KEYWORD
    + refer to look up table
+ COMMENT
    + //
    + /* */
+ ID's
    + letter (letter | digit)*
+ NUMBER
    + __digits optional_fraction optional_exponent__ where they are defined as: 
        + digits
            + digit digit*
        + optional_fraction
            + . digits | epsilon
        + optional_exponent
            + (E (+ | - | epsilon) digits) | epsilon
+ CHARLITERAL
    + delimited by single quotes and cannot contain new lines
    + empty char is allowed 
    + unterminated char is an error
        + examples
            + ''
            + '2'
+ STRING
    + delimited by double quotes and connot contain new lines
    + unterminates string is an error
    + empty strings are allowed
    + examples
        + ""
        + "meow meow meow meow"
+ RELOP
    + Consists of every one of the following
        + ==
        + != 
        + <
        + <=
        + >=
        + >
+ ADDOP
    + Consists of every one of the following 
        + + 
        + -
        + ||
+ MULOP
    + consists of every one of the following 
        + *
        + /
        + %
        + &&
+ ASSIGNOP
    + = 
+ LPAREN
    + (
+ RPAREN
    + )
+ LCURLY
    + {
+ RCURLY
    + }
+ LBRACKET
    + [
+ RBRACKET
    + ]
+ COMMA
    + , 
+ SEMICOLON
    + ;
+ NOT
    + !
+ COLON
    + :

