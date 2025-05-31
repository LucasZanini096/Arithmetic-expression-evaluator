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
            left %= right;
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
    
    fprintf(stderr, "Expressão inválida\n");
    exit(EXIT_FAILURE);
}

// Nova função para avaliar expressão em notação pós-fixa compacta
int evaluatePostfix(const char *postfix) {
    int stack[100];
    int top = -1;
    int i = 0;
    
    while (postfix[i] != '\0') {
        // Se é um dígito, processa o número completo
        if (isdigit(postfix[i])) {
            int num = 0;
            while (i < strlen(postfix) && isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            stack[++top] = num;
        }
        // Se é um operador
        else if (strchr("+-*/%", postfix[i])) {
            if (top < 1) {
                fprintf(stderr, "Expressão inválida\n");
                exit(EXIT_FAILURE);
            }
            
            int operand2 = stack[top--];
            int operand1 = stack[top--];
            int result;
            
            switch (postfix[i]) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0) {
                        fprintf(stderr, "Expressão inválida\n");
                        exit(EXIT_FAILURE);
                    }
                    result = operand1 / operand2;
                    break;
                case '%':
                    if (operand2 == 0) {
                        fprintf(stderr, "Expressão inválida\n");
                        exit(EXIT_FAILURE);
                    }
                    result = operand1 % operand2;
                    break;
                default:
                    fprintf(stderr, "Expressão inválida\n");
                    exit(EXIT_FAILURE);
            }
            
            stack[++top] = result;
            i++;
        }
        else {
            // Pula caracteres não reconhecidos (espaços, etc.)
            i++;
        }
    }
    
    if (top != 0) {
        fprintf(stderr, "Expressão inválida\n");
        exit(EXIT_FAILURE);
    }
    
    return stack[top];
}

// Função para avaliar uma string como expressão aritmética (infixa)
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