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

// Função para inicializar o parser
Parser* init_parser(Lexer* lexer);

// Função para destruir o parser
void destroy_parser(Parser* parser);

// Função para consumir o token atual e avançar para o próximo
void parser_eat(Parser* parser, TokenType token_type);

// Funções de análise sintática baseadas na gramática
void parse_E(Parser* parser);
void parse_E_prime(Parser* parser);
void parse_T(Parser* parser);
void parse_T_prime(Parser* parser);
void parse_F(Parser* parser);
int parser_parse(Parser* parser);

#endif // PARSER_H