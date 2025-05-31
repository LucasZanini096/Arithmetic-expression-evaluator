#include "../include/postfix.h"

//Função para eliminar espaços em branco de uma expressão
void eliminateWhiteSpaces(char* exp) {
    char* src = exp;
    char* dst = exp;

    while (*src) {
        if (*src != ' ') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0'; // Adiciona o terminador nulo
}

// Função para verificar a precedência dos operadores
int prec(char c) {
    switch (c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        case '^':
            return 3;
        case '(':
        case ')':
            return 0;
        default:
            return -1;
    }
}

// Função para converter expressão infixa para pós-fixa
void infixToPostfix(char* exp) {
    char stack[100];
    int top = -1;
    char output[100];
    int j = 0;

    for (int i = 0; exp[i]; i++) {
        // Se é um dígito, processe o número completo
        if (isdigit(exp[i])) {
            // Adiciona todos os dígitos do número
            while (i < strlen(exp) && isdigit(exp[i])) {
                output[j++] = exp[i++];
            }
            i--; // Volta um índice porque o for vai incrementar
        }
        // Se é parêntese de abertura
        else if (exp[i] == '(') {
            stack[++top] = exp[i];
        }
        // Se é parêntese de fechamento
        else if (exp[i] == ')') {
            while (top != -1 && stack[top] != '(') {
                output[j++] = stack[top--];
            }
            top--; // Remove '('
        }
        // Se é um operador
        else if (prec(exp[i]) > 0) {
            while (top != -1 && prec(stack[top]) >= prec(exp[i])) {
                output[j++] = stack[top--];
            }
            stack[++top] = exp[i];
        }
    }

    // Remove operadores restantes da pilha
    while (top != -1) {
        output[j++] = stack[top--];
    }
    
    output[j] = '\0';

    printf("%s", output);
}