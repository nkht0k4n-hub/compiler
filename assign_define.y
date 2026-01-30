%{
#include <stdio.h>
#include "assign_define.tab.h"
#include "ast.h"
#include <string.h>
extern int yylex();
extern int yyerror();
extern Node *top;

%}
%union{
	struct node *np;
	char *sp;
	int ival;
	//int num;
	//char* str;
}
%define parse.error verbose
%token IDENT ASSIGN NUMBER SEMIC DEFINE COMMA MUL DIV ADD SUB EQ IF ELSE LT GT L_BRACE R_BRACE ARRAY WHILE L_BRACKET R_BRACKET L_PAREN R_PAREN
%type <np> program statements statement assignment_stmt term factor add_op mul_op var declarations decl_statement  idents  expression condition cond_op loop_stmt cond_stmt 
%type <sp> IDENT
%type <ival> NUMBER
%%
my
:program
;

program //プログラム
:declarations statements {top = build_node2(PROGRAM_AST,$1,$2);}
;

statements //文集合
:statement statements {$$ = build_node2(STATEMENTS_AST, $1, $2);}
|statement {$$ = build_node1(STATEMENTS_AST, $1);}
;

statement //文
:assignment_stmt {$$ = build_node1(STATEMENT_AST,$1);}
|loop_stmt {$$ = build_node1(STATEMENT_AST,$1);}
|cond_stmt {$$ = build_node1(STATEMENT_AST,$1);}
;

assignment_stmt //代入分
:idents ASSIGN expression SEMIC {
  $$ = build_node2_Assign(ASSIGNMENT_STMT_AST,$1, $3,-1);
 }
|IDENT L_BRACKET NUMBER R_BRACKET ASSIGN expression SEMIC  {$$ = build_node2_Assign(ASSIGNMENT_STMT_AST,build_node0(IDENT_AST,$1,$3,""),$6,1);}
|IDENT L_BRACKET IDENT R_BRACKET ASSIGN expression SEMIC {$$ = build_node2_Assign(ASSIGNMENT_STMT_AST,build_node0(IDENT_AST,$1,0,$3),$6,2);} //変数の添え字 mikan
|IDENT L_BRACKET IDENT R_BRACKET L_BRACKET IDENT R_BRACKET ASSIGN expression SEMIC {$$ = build_node3_Assign(ASSIGNMENT_STMT_AST,build_node0(IDENT_AST,$1,0,""),build_node2(INDEX_EXPRESSION_AST,build_node0(IDENT_AST,$3,-1,""),build_node0(IDENT_AST,$6,-1,"")),$9,1);}
;
//|IDENT L_BRACKET expression R_BRACKET L_BRACKET expression R_BRACKET ASSIGN expression SEMIC {$$ = build_node3_Assign(ASSIGNMENT_STMT_AST,build_node0(IDENT_AST,$1,0,""),build_node2(INDEX_EXPRESSION_AST,$3,$6),$9,1);}
//var:IDENT L_BRACKET IDENT R_BRACKETがexpressionに還元するのか,IDENT L_BRACKET expression（IDENT） R_BRACKETに還元するのかがわからないので還元競合が起きる.
//終端記号->還元の余地がないが,非終端記号だと解釈の余地がうまれ,1通りに決まらなけばならない

//TODO 後3通り,send indの表

term //項
:term mul_op factor {$$ = build_node2(TERM_AST,$1,build_node2(MUL_OP_AST,$2,$3));}
|factor {$$ = build_node1(TERM_AST,$1);}
;

factor //因子
:var {$$ = build_node1(FACTOR_AST,$1);}
|L_PAREN expression R_PAREN {$$ =  build_node1(FACTOR_AST,$2);}
;

add_op //加減演算子
:ADD {$$=build_node0(ADD_AST,"+",-2,"");}
|SUB {$$=build_node0(SUB_AST,"-",-2,"");}
;

mul_op //乗除演算子
:MUL {$$=build_node0(MUL_AST,"*",-2,"");}
|DIV {$$=build_node0(DIV_AST,"/",-2,"");}///
;

var //変数
:idents {$$=build_node1(VAR_AST,$1);}
|NUMBER {$$=build_node1(VAR_AST,build_node0(NUMBER_AST,"",$1,""));}
|IDENT L_BRACKET NUMBER R_BRACKET {$$=build_node1(VAR_AST,build_node0(IDENT_AST,$1,$3,""));}//mikan
|IDENT L_BRACKET IDENT R_BRACKET {$$=build_node1(VAR_AST,build_node0(IDENT_AST,$1,0,$3));}
//|IDENT L_BRACKET NUMBER R_BRACKET  L_BRACKET NUMBER R_BRACKET {$$=build_node1(VAR_AST,build_node0(IDENT_AST,$1,-1));}//mikan
;

declarations //変数宣言部
:decl_statement declarations {$$ = build_node2(DECLARATIONS_AST,$1, $2);}
|decl_statement {$$ = build_node1(DECLARATIONS_AST,$1);}
;

decl_statement //宣言文
:DEFINE idents SEMIC  {$$ = build_node1_Decl(DECL_STATEMENT_AST,$2,-1);}//-1->define 
|ARRAY IDENT L_BRACKET NUMBER R_BRACKET SEMIC  {$$ = build_node2_Decl(DECL_STATEMENT_AST,build_node0(IDENT_AST,$2,-1,""),build_node0(NUMBER_AST,"",$4,""),1);}//1->array
|ARRAY IDENT L_BRACKET NUMBER R_BRACKET L_BRACKET NUMBER R_BRACKET SEMIC  {$$ = build_node3_Decl(DECL_STATEMENT_AST,build_node0(IDENT_AST,$2,-1,""),$4,$7);}//else->array [][n]
//|ARRAY IDENT L_BRACKET NUMBER R_BRACKET SEMIC L_BRACKET NUMBER R_BRACKET SEMIC  {$$ = build_node1(DECL_STATEMENT_AST,build_node0(IDENT_AST,$2,-1));}
;

idents //複数の識別子
:IDENT COMMA idents {$$ = build_node2(IDENTS_AST,build_node0(IDENT_AST,$1,-1,"") , $3);}
|IDENT {$$=build_node0(IDENT_AST,$1,-1,"");}
//|IDENT L_BRACKET IDENT R_BRACKET {$$=build_node0(IDENT_AST,$1,-1);} //これをするとdecl_statementでidentsがIDENT L_BRACKET IDENT R_BRACKETなのかIDENTなのかがわからない.(シフト還元の衝突)
//|IDENT L_BRACKET IDENT R_BRACKET をidents L_BRACKET idents R_BRACKETと還元するかidentsと還元するかの2通りある.
;

expression //算術式
:expression add_op term
{
	$$ = build_node2(EXPRESSION_AST,$1,build_node2(ADD_OP_AST,$2,$3));
}
|term {$$=build_node1(EXPRESSION_AST,$1);}
//|IDENT L_BRACKET IDENT R_BRACKET {$$=build_node0(IDENT_AST,$1,-1);} //conditionなどで用いるためにexpressionに配置する. mikan
;

condition //条件式
:expression cond_op expression {$$ = build_node2(CONDITION_AST,$1, build_node2(COND_OP_AST,$2,$3));}
;

cond_op //比較演算子
:EQ {$$=build_node0(EQ_AST,"==",-3,"");}
|GT {$$=build_node0(GT_AST,">",-3,"");}
|LT {$$=build_node0(LT_AST,"<",-3,"");}
|GT ASSIGN {$$=build_node0(GT_OR_EQ_AST,">=",-3,"");}
|LT ASSIGN {$$=build_node0(LT_OR_EQ_AST,"<=",-3,"");}
;

loop_stmt //ループ文
:WHILE L_PAREN condition R_PAREN L_BRACE statements R_BRACE {$$ = build_node2(LOOP_STMT_AST,$3,$6);}
;

cond_stmt //条件分岐文
:IF L_PAREN condition R_PAREN L_BRACE statements R_BRACE  {$$ = build_node2(COND_STMT_AST,$3, $6);}
|IF L_PAREN condition R_PAREN L_BRACE statements R_BRACE ELSE L_BRACE statements  R_BRACE {$$ = build_node2(COND_STMT_AST,build_node2(ELIF_STMT_AST,$3, $6),$10);}
;

%%


  //|number PLUS number {printf("OK! %d+%d",$1,$3);}
  //|NUMBER MINUS NUMBER {printf("OK! %d-%d",$1,$3);}
  //|NUMBER DIVIDE NUMBER {printf("OK! %d/%d",$1,$3);}
  //|NUMBER TIMES NUMBER {printf("OK! %d*%d",$1,$3);}
