#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Tipos de tokens
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
    TOKEN_EOF       // Fim do arquivo
} TokenType;

// Estrutura do token
typedef struct {
    TokenType type;
    char lexeme[100];
    int value;      // Para números
} Token;

// Analisador léxico
typedef struct {
    char* input;
    int position;
    char current_char;
} Lexer;

Lexer* init_lexer(char* input);

void destroy_lexer(Lexer* lexer);

void lexer_advance(Lexer* lexer);

void lexer_skip_whitespace(Lexer* lexer);

Token lexer_get_next_token(Lexer* lexer);

Token lexer_get_id(Lexer* lexer);

Token lexer_get_next_token(Lexer* lexer);

#endif // LEXER_H