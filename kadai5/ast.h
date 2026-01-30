#include <stdio.h>
#include <stdlib.h>
extern int yyparse();

// ノードタイプ
typedef enum{
IDENT_AST=0,
IDENTS_AST,
NUMBER_AST,
STATEMENTS_AST,
STATEMENT_AST,
PROGRAM_AST,
ASSIGNMENT_STMT_AST,
FACTOR_AST,
TERM_AST,
ADD_OP_AST,
MUL_OP_AST,
VAR_AST,
DECLARATIONS_AST,
DECL_STATEMENT_AST,
EXPRESSION_AST,
CONDITION_AST,
COND_OP_AST,
EQ_AST,
GT_AST,
LT_AST,
GT_OR_EQ_AST,
LT_OR_EQ_AST,
LOOP_STMT_AST,
COND_STMT_AST,
ADD_AST,
SUB_AST,
MUL_AST,
DIV_AST,
ELIF_STMT_AST,
INDEX_EXPRESSION_AST
} NType;
// プリント用
extern char *node_types[];
// プロトタイプ宣言
void print_node_type(int node_type);

// 抽象構文木のノードのデータ構造
typedef struct node{
NType type;
struct node *child;
struct node *brother;
char* ident;
int number;
	char* ideIdx;
	struct node* exp_ind;
	int second_dim_num;
} Node;
// 抽象構文木のノードの生成
Node *build_node0(NType t,char *s,int u,char *n);
Node *build_node0_array2(NType t,char *s,int u,char *n,Node *p2);

Node *build_node1(NType t, Node *p1);
Node *build_node1_Decl(NType t, Node *p1,int u);
Node *build_node2(NType t, Node *p1, Node *p2);
Node *build_node2_Assign(NType t, Node *p1, Node *p2,int u);
Node* build_node3_Assign(NType t, Node* p1, Node* p2,Node* p3,int u);

Node* build_node2_Decl(NType t, Node* p1, Node* p2, int u);
Node* build_node3_Decl(NType t, Node* p1,int u, int v);
