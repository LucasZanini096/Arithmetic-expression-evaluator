#ifndef PARSER_H
#define PARSER_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

//Estrutura de dados para o parser
typedef struct {
    Lexer* lexer;
    Token current_token;
} Parser;

Parser* init_parser(Lexer* lexer);

void destroy_parser(Parser* parser);

void parser_eat(Parser* parser, TokenType token_type);

void parse_E(Parser* parser);

void parse_E_prime(Parser* parser);

void parse_T(Parser* parser);

void parse_T_prime(Parser* parser);

void parse_F(Parser* parser);

int parser_parse(Parser* parser);

#endif // PARSER_H