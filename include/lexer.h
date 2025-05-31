#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Enumeração de tokens
typedef enum {
    TOKEN_INTEGER,  // Número inteiro
    TOKEN_ID,       // Identificador
    TOKEN_NUM,      // Número
    TOKEN_PLUS,     // +
    TOKEN_MINUS,    // -
    TOKEN_MULT,     // *
    TOKEN_DIV,      // /
    TOKEN_LPAREN,   // (
    TOKEN_RPAREN,   // )
    TOKEN_MOD,      // %
    TOKEN_EOF,      // Fim do arquivo
    TOKEN_ERROR    // Token de erro para caracteres inválidos
} TokenType;

// Estrutura do token
typedef struct {
    TokenType type;
    char lexeme[100];
    int value;      // Para números
} Token;

// Estrutura do analisador léxico
typedef struct {
    char* input;
    int position;
    char current_char;
} Lexer;

// Função para inicializar o lexer
Lexer* init_lexer(char* input);

// Função para destruir o lexer
void destroy_lexer(Lexer* lexer);

// Função para avançar o lexer para o próximo caractere
void lexer_advance(Lexer* lexer);

// Função para avançar o lexer e ignorar espaços em branco
void lexer_skip_whitespace(Lexer* lexer);

// Função para capturar o próximo token
Token lexer_get_next_token(Lexer* lexer);

// Função para capturar um identificador
Token lexer_get_id(Lexer* lexer);

// Função para capturar um próximo número
Token lexer_get_next_token(Lexer* lexer);

#endif // LEXER_H