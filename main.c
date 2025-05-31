/* 
   PROJETO N2 - Avaliador de expressões aritméticas 
   Semestre: 2025/1 
   Curso: Ciência da Computação - Mackenzie
   Disciplina: Linguagens Formais e Autômatos
   Aluno: Lucas Zanini da Silva - 10417361
   Turma: 5D
   Professor: Leonardo Massayuki Takuno

*/

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

    // Remove a quebra de linha
    input[strcspn(input, "\n")] = 0;

    printf("%s => ", input);
    
    Lexer* lexer = init_lexer(input);
    Parser* parser = init_parser(lexer);
    int success = parser_parse(parser);
    
    if (success && parser->current_token.type == TOKEN_EOF) {

        // Converte a expressão infixa para pós-fixa
        
        char postfix[1000];
        strcpy(postfix, input);
        eliminateWhiteSpaces(postfix);
        infixToPostfix(postfix);

        //Resultado da expressão pós-fixa
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