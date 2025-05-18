#include "../include/expression.h"


// Função para pular espaços em branco
void skipSpaces(char **expr) {
    while (isspace(**expr))
        (*expr)++;
}

// Função principal para analisar expressões
int parseExpression(char **expr) {
    int left = parseTerm(expr);
    
    skipSpaces(expr);
    while (**expr == '+' || **expr == '-') {
        char op = **expr;
        (*expr)++;
        int right = parseTerm(expr);
        
        if (op == '+')
            left += right;
        else
            left -= right;
        
        skipSpaces(expr);
    }
    
    return left;
}

// Função para analisar termos (multiplicação e divisão)
int parseTerm(char **expr) {
    int left = parseFactor(expr);
    
    skipSpaces(expr);
    while (**expr == '*' || **expr == '/' || **expr == '%') {
        char op = **expr;
        (*expr)++;
        int right = parseFactor(expr);
        
        if (op == '*')
            left *= right;
        else if (op == '/') {
            if (right == 0) {
                fprintf(stderr, "Erro: Divisão por zero\n");
                exit(EXIT_FAILURE);
            }
            left /= right;  // Divisão inteira
        }
        else if (op == '%') {
            if (right == 0) {
                fprintf(stderr, "Erro: Módulo por zero\n");
                exit(EXIT_FAILURE);
            }
            left %= right;  // Operação módulo
        }
        
        skipSpaces(expr);
    }
    
    return left;
}

// Função para analisar fatores (números inteiros e parênteses)
int parseFactor(char **expr) {
    skipSpaces(expr);
    
    // Caso de parênteses
    if (**expr == '(') {
        (*expr)++;
        int value = parseExpression(expr);
        
        skipSpaces(expr);
        if (**expr != ')') {
            fprintf(stderr, "Erro: Parêntese de fechamento ausente\n");
            exit(EXIT_FAILURE);
        }
        (*expr)++;
        
        return value;
    }
    
    // Caso de número inteiro
    if (isdigit(**expr)) {
        int value = 0;
        while (isdigit(**expr)) {
            value = value * 10 + (**expr - '0');
            (*expr)++;
        }
        return value;
    }
    
    // Caso de número negativo
    if (**expr == '-') {
        (*expr)++;
        return -parseFactor(expr);
    }
    
    fprintf(stderr, "Erro: Expressão inválida\n");
    exit(EXIT_FAILURE);
}

// Função para avaliar uma string como expressão aritmética
int evaluateExpression(const char *expression) {
    char *expr = strdup(expression);
    char *start = expr;
    
    int result = parseExpression(&expr);
    
    skipSpaces(&expr);
    if (*expr != '\0') {
        fprintf(stderr, "Aviso: Caracteres extras após a expressão\n");
    }
    
    free(start);
    return result;
}