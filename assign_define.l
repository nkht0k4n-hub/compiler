%{
#include "assign_define.tab.h"
%}
%%
define {return DEFINE;}
if {return IF;}
array {return ARRAY;}
while {return WHILE;}
else {return ELSE;}
= {return ASSIGN;}
; {return SEMIC;}
[a-zA-Z][a-zA-Z0-9]* {
 yylval.sp= (char*)malloc(sizeof(char) * yyleng);
 strncpy(yylval.sp , yytext, yyleng);
return IDENT;
}
[0-9]+ { yylval.ival = atoi(yytext);
return NUMBER;}
, {return COMMA;}
[ \t]+
"+" {return ADD;}
"-" {return SUB;}
"/" {return DIV;}
"*" {return MUL;}
"==" {return EQ;}
"<" {return LT;}
">" {return GT;}
"{" {return L_BRACE;}
"}" {return R_BRACE;}
"[" {return L_BRACKET;}
"]" {return R_BRACKET;}
"(" {return L_PAREN;}
")" {return R_PAREN;}
\n 
. {return yytext[0];}
