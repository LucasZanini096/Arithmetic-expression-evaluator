#ifndef POSTFIX_H
#define POSTFIX_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int prec(char c);

void infixToPostfix(char* exp);

void eliminateWhiteSpaces(char* exp);

#endif // POSTFIX_H