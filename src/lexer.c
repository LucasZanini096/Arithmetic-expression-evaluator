#include "../include/lexer.h"

// Inicializa o lexer
Lexer* init_lexer(char* input) {
    Lexer* lexer = (Lexer*)malloc(sizeof(Lexer));
    lexer->input = input;
    lexer->position = 0;
    lexer->current_char = input[0];
    return lexer;
}

// Libera a memória do lexer
void destroy_lexer(Lexer* lexer) {
    free(lexer);
}

// Avança para o próximo caractere
void lexer_advance(Lexer* lexer) {
    lexer->position++;
    if (lexer->position < strlen(lexer->input)) {
        lexer->current_char = lexer->input[lexer->position];
    } else {
        lexer->current_char = '\0';
    }
}

// Ignora espaços em branco
void lexer_skip_whitespace(Lexer* lexer) {
    while (lexer->current_char != '\0' && isspace(lexer->current_char)) {
        lexer_advance(lexer);
    }
}

// Reconhece números
Token lexer_get_number(Lexer* lexer) {
    Token token;
    token.type = TOKEN_NUM;
    int i = 0;
    
    while (lexer->current_char != '\0' && isdigit(lexer->current_char)) {
        token.lexeme[i++] = lexer->current_char;
        lexer_advance(lexer);
    }
    token.lexeme[i] = '\0';
    token.value = atoi(token.lexeme);
    
    return token;
}

// Reconhece identificadores
Token lexer_get_id(Lexer* lexer) {
    Token token;
    token.type = TOKEN_ID;
    int i = 0;
    
    while (lexer->current_char != '\0' && (isalnum(lexer->current_char) || lexer->current_char == '_')) {
        token.lexeme[i++] = lexer->current_char;
        lexer_advance(lexer);
    }
    token.lexeme[i] = '\0';
    
    return token;
}

// Obtém o próximo token
Token lexer_get_next_token(Lexer* lexer) {
    Token token;
    
    // Pula espaços em branco
    lexer_skip_whitespace(lexer);
    
    // Verifica o tipo do próximo token
    if (lexer->current_char == '\0') {
        token.type = TOKEN_EOF;
        strcpy(token.lexeme, "EOF");
    } else if (isdigit(lexer->current_char)) {
        return lexer_get_number(lexer);
    } else if (isalpha(lexer->current_char) || lexer->current_char == '_') {
        return lexer_get_id(lexer);
    } else if (lexer->current_char == '+') {
        token.type = TOKEN_PLUS;
        strcpy(token.lexeme, "+");
        lexer_advance(lexer);
    } else if (lexer->current_char == '-') {
        token.type = TOKEN_MINUS;
        strcpy(token.lexeme, "-");
        lexer_advance(lexer);
    } else if (lexer->current_char == '*') {
        token.type = TOKEN_MULT;
        strcpy(token.lexeme, "*");
        lexer_advance(lexer);
    } else if (lexer->current_char == '/') {
        token.type = TOKEN_DIV;
        strcpy(token.lexeme, "/");
        lexer_advance(lexer);
    } else if (lexer->current_char == '(') {
        token.type = TOKEN_LPAREN;
        strcpy(token.lexeme, "(");
        lexer_advance(lexer);
    } else if (lexer->current_char == ')') {
        token.type = TOKEN_RPAREN;
        strcpy(token.lexeme, ")");
        lexer_advance(lexer);
    } 
        else if (lexer->current_char == '%') {
        token.type = TOKEN_MOD;
        strcpy(token.lexeme, "%");
        lexer_advance(lexer);
    }
    
    else {
        // printf("Erro: caractere não reconhecido '%c'\n", lexer->current_char);
        exit(1);
    }
    
    return token;
}