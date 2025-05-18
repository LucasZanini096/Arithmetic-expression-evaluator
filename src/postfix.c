#include "../include/postfix.h"

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
        if (isalnum(exp[i])) {
            output[j++] = exp[i];
        } else if (exp[i] == '(') {
            stack[++top] = exp[i];
        } else if (exp[i] == ')') {
            while (top != -1 && stack[top] != '(') {
                output[j++] = stack[top--];
            }
            top--; // Remove '('
        } else {
            while (top != -1 && prec(stack[top]) >= prec(exp[i])) {
                output[j++] = stack[top--];
            }
            stack[++top] = exp[i];
        }
    }

    while (top != -1) {
        output[j++] = stack[top--];
    }
    output[j] = '\0';

    printf("%s\n", output);
}