/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_ASSIGN_DEFINE_TAB_H_INCLUDED
# define YY_YY_ASSIGN_DEFINE_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENT = 258,                   /* IDENT  */
    ASSIGN = 259,                  /* ASSIGN  */
    NUMBER = 260,                  /* NUMBER  */
    SEMIC = 261,                   /* SEMIC  */
    DEFINE = 262,                  /* DEFINE  */
    COMMA = 263,                   /* COMMA  */
    MUL = 264,                     /* MUL  */
    DIV = 265,                     /* DIV  */
    ADD = 266,                     /* ADD  */
    SUB = 267,                     /* SUB  */
    EQ = 268,                      /* EQ  */
    IF = 269,                      /* IF  */
    ELSE = 270,                    /* ELSE  */
    LT = 271,                      /* LT  */
    GT = 272,                      /* GT  */
    L_BRACE = 273,                 /* L_BRACE  */
    R_BRACE = 274,                 /* R_BRACE  */
    ARRAY = 275,                   /* ARRAY  */
    WHILE = 276,                   /* WHILE  */
    L_BRACKET = 277,               /* L_BRACKET  */
    R_BRACKET = 278,               /* R_BRACKET  */
    L_PAREN = 279,                 /* L_PAREN  */
    R_PAREN = 280                  /* R_PAREN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 11 "assign_define.y"

	struct node *np;
	char *sp;
	int ival;
	//int num;
	//char* str;

#line 97 "assign_define.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_ASSIGN_DEFINE_TAB_H_INCLUDED  */
