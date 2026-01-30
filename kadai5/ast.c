#include "ast.h"
#include "generate.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void print_tree_in_json(Node *n) { 
    if (n != NULL) { 
        int num = 0; 
        printf("{"); 
        print_tree(n, num); 
        printf("}"); 
    } 
}



int print_tree(Node *n, int num) { 
    printf("\"%s_%d\": {", node_types[n->type], num++); 
    if (n->child != NULL) { 
        num = print_tree(n->child, num); 
    } 
    printf("}"); 
    if (n->brother != NULL) { 
        printf(","); 
        num = print_tree(n->brother, num); 
    } 
    return num; 
}



void print_node_type(int node_type) {
printf("Node type: %s\n", node_types[node_type]);
}
// プリント用
char *node_types[] = {
"IDENT_AST",
"IDENTS_AST",
"NUMBER_AST",
"STATEMENTS_AST",
"STATEMENT_AST",
"PROGRAM_AST",
"ASSIGNMENT_STMT_AST",
"TERM_AST",
"FACTOR_AST",
"ADD_OP_AST",
"MUL_OP_AST",
"VAR_AST",
"DECLARATIONS_AST",
"DECL_STATEMENT_AST",
"IDENTS_AST",
"EXPRESSION_AST",
"CONDITION_AST",
"COND_OP_AST",
"LOOP_STMT_AST",
"COND_STMT_AST",
"LT_AST",
"GT_AST",
"EQ_AST",
"LT_OR_EQ_AST",
"GT_OR_EQ_AST",
"ADD_AST",
"SUB_AST",
"MUL_AST",
"DIV_AST",
"COND_OP_AST",
"ELIF_STMT_AST",
};

Node *top; // 抽象構文木のルートノード保存用
Node *build_node0(NType t,char* s,int u,char*n) {
Node *p;
p = (Node *)malloc(sizeof(Node));
if (p == NULL) {
yyerror("out of memory");
}
p->type = t;
p->child = NULL;
//p->child->brother = NULL;
p->ident=malloc(sizeof(char)*(strlen(s)+1));
p->ideIdx=malloc(sizeof(char)*(strlen(n)+1));
if(strcmp(node_types[p->type],"IDENT_AST")==0){
  strcpy(p->ident,s);
  if(u==-1)
   p->number=-1;
  else
   p->number=u;
   }

if(strcmp(node_types[p->type],"NUMBER_AST")==0){
  strcpy(p->ident,s);/* 追加*/
  p->number=u;
   }
strcpy(p->ideIdx,n);
 
return p;
}

Node* build_node0_array2(NType t, char* s, int u,char* n,Node *p2) {
    Node* p;
    p = (Node*)malloc(sizeof(Node));
    if (p == NULL) {
        yyerror("out of memory");
    }
    p->type = t;
    p->child = NULL;
    //p->child->brother = NULL;
    p->ident = malloc(sizeof(char) * (strlen(s) + 1));
    p->ideIdx = malloc(sizeof(char) * (strlen(n) + 1));
    if (strcmp(node_types[p->type], "IDENT_AST") == 0) {
        strcpy(p->ident, s);
        if (u == -1)
            p->number = -1;
        else
            p->number = u;
    }

    p->exp_ind = p2;

    if (strcmp(node_types[p->type], "NUMBER_AST") == 0) {
        strcpy(p->ident, s);/* 追加*/
        p->number = u;
    }
    strcpy(p->ideIdx, n);

    return p;
}



Node *build_node1(NType t, Node *p1) {
Node *p;
p = (Node *)malloc(sizeof(Node));
if (p == NULL) {
yyerror("out of memory");
}
p->type = t;
p->child = p1;
p->child->brother = NULL;
p->number=-1;
return p;
}

Node *build_node1_Decl(NType t, Node *p1,int u) {
Node *p;
p = (Node *)malloc(sizeof(Node));
if (p == NULL) {
yyerror("out of memory");
}
p->type = t;
p->child = p1;
p->child->brother = NULL;
p->number=u;
return p;
}

Node *build_node2(NType t, Node *p1, Node *p2) {
Node *p;
p = (Node *)malloc(sizeof(Node));
if (p == NULL) {
yyerror("out of memory");
}
p->type = t;
p->child = p1;
p->child->brother = p2;
return p;
}

Node *build_node2_Assign(NType t, Node *p1, Node *p2,int u) {
Node *p;
p = (Node *)malloc(sizeof(Node));
if (p == NULL) {
yyerror("out of memory");
}
p->type = t;
p->child = p1;
p->child->brother = p2;
p->number=u;
p->exp_ind=NULL;
return p;
}

Node *build_node3_Assign(NType t, Node *p1, Node *p2,Node *p3,int u) {
Node *p;
p = (Node *)malloc(sizeof(Node));
if (p == NULL) {
yyerror("out of memory");
}
p->type = t;
p->child = p1;
p->child->brother = p3;
p->number=u;
p->exp_ind=p2;
return p;
}


Node* build_node2_Decl(NType t, Node* p1, Node* p2, int u) {
    Node* p;
    p = (Node*)malloc(sizeof(Node));
    if (p == NULL) {
        yyerror("out of memory");
    }
    p->type = t;
    p->child = p1;
    p->child->brother = p2;
    p->number = u;
    return p;
}

Node* build_node3_Decl(NType t,Node* p1,int u,int v) {
    Node* p;
    p = (Node*)malloc(sizeof(Node));
    if (p == NULL) {
        yyerror("out of memory");
    }
    p->type = t;
    p->child = p1;
    p->child->brother = NULL;
    p->number = u*v;
    //second_dim_num=v;
    p->second_dim_num = v;
    
    return p;
}


void print_node(Node *n) { 
    if (n != NULL) { 
        printf("type: %s\n", node_types[n->type]); 
   } 
}


int main(void) {
if (yyparse()) {
fprintf(stderr, "Error!\n");
return 1;
}
// AST生成完了
//printf("[*] AST generation is completed\n");
//AST
//print_tree_in_json(top); 
//コード生成
defined_num=0;
defining=0;

assined_num=0;
assing=0;
offset_count=0;

expressioning=0;
terming = 0;
 
secDimIdx = 0;

cur=talloc();
cur->name=NULL;
cur->next=NULL;
cur->offset=-1;
first=cur;

cur_exp=exp_talloc();
cur_exp->haveNumber=-1;
cur_exp->number=0;
cur_exp->offset=-1;
cur_exp->index = -1;
cur_exp->next=NULL;
cur_exp->bef=NULL;
first_exp=cur_exp;

whiling=0;

using_if = 0;
IWIdx=0;
else_num=0;
else_end_num=0;
conditionning=0;

if_num=0;
while_num=0;
 
init_code();
gen_code(top);

printf("    jr $ra\n");
printf("    nop\n");
printf("    .data 0x10004000\n");
printf("RESULT:\n");

return 0;
}



