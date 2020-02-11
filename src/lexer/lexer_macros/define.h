/* TODO: ifndef */

#define IS_WHITESPACE(c)  (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\0')
#define STARTS_LABEL(c)   (isalpha(c) || c == '_')
#define IS_LABEL_CHAR(c)  (isalpha(c) || isdigit(c) || c == '_')
#define STARTS_STRING(c)  (c == '\"' || c == '\'')
#define STARTS_NUMBER(c)  (isdigit(c))
#define IS_HEX_DIGIT(c)   (zfind_chr(c, "0123456789ABCDEF"))
#define IS_BIN_DIGIT(c)   (c == '0' || c == '1')
#define IS_DEC_DIGIT(c)   (zfind_chr(c, "0123456789."))
#define IS_OPERATOR(c)    (zfind_chr(c, "+-*/=!"))
#define IS_BRACKET(c)     (zfind_chr(c, "(){}[]"))
#define IS_PUNCTUATION(c) (zfind_chr(c, ".,:;"))
