#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int  evaluateExpression(const char *expression);
int parseExpression(char **expr);
int parseTerm(char **expr);
int parseFactor(char **expr);
void skipSpaces(char **expr);

#endif