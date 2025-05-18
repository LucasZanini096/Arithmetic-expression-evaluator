#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/lexer.c"
#include "src/parser.c"
#include "src/postfix.c"
#include "src/expression.c"


int main (int argc, char *argv[]) {
    
    char input[1000];
    
    fgets(input, sizeof(input), stdin);

    printf("%s => ", input);
    
    // Remove a quebra de linha
    input[strcspn(input, "\n")] = 0;
    
    Lexer* lexer = init_lexer(input);
    Parser* parser = init_parser(lexer);
    
    int success = parser_parse(parser);

    printf("Sucesso: %d\n", success);
    
    if (success) {

        // Converte a expressão infixa para pós-fixa
        char postfix[1000];
        strcpy(postfix, input);
        eliminateWhiteSpaces(postfix);
        infixToPostfix(postfix);

        printf("%s", postfix);

        int result = evaluateExpression(postfix);
        printf("=%d\n", result);


    } else {
        printf("Erro Sintático \n");
    }


    // Libera a memória
    destroy_parser(parser);
    destroy_lexer(lexer);
    
    return 0;
}