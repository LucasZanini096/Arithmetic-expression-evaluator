#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Função para retornar o resultado de uma expressão
int  evaluateExpression(const char *expression);
// Função para avaliar uma expressão pós-fixa
int  evaluatePostfix(const char *postfix); 
// Função principal para analisar expressões
int  parseExpression(char **expr);
// Função para analisar termos (multiplicação e divisão)
int  parseTerm(char **expr);
// Função para analisar fatores (números e parênteses)
int  parseFactor(char **expr);
// Função para pular espaços em branco
void skipSpaces(char **expr);

#endif