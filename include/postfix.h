#ifndef POSTFIX_H
#define POSTFIX_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Função para verificar a precedência dos operadores
int prec(char c);

// Função para converter expressão infixa para pós-fixa
void infixToPostfix(char* exp);

// Função para eliminar espaços em branco de uma expressão
void eliminateWhiteSpaces(char* exp);

#endif // POSTFIX_H