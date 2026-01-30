assign_define:assign_define.tab.c lex.yy.c ast.c
	gcc assign_define.tab.c lex.yy.c ast.c -o assign_define -lfl -ly

assign_define.tab.c:assign_define.y
	bison -d assign_define.y

lex.yy.c:assign_define.l
	flex assign_define.l
