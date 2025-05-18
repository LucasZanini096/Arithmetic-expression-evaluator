#include "../include/lexer.h"
#include "../include/parser.h"


// Inicializa o parser
Parser* init_parser(Lexer* lexer) {
    Parser* parser = (Parser*)malloc(sizeof(Parser));
    parser->lexer = lexer;
    parser->current_token = lexer_get_next_token(lexer);
    return parser;
}

// Libera a memória do parser
void destroy_parser(Parser* parser) {
    free(parser);
}

// Verifica e consome o token atual
void parser_eat(Parser* parser, TokenType token_type) {
    if (parser->current_token.type == token_type) {
        // printf("Consumindo token: %s\n", parser->current_token.lexeme);
        parser->current_token = lexer_get_next_token(parser->lexer);
    } else {
        // printf("Erro de sintaxe: esperado token tipo %d, mas recebido token tipo %d (%s)\n", 
        //        token_type, parser->current_token.type, parser->current_token.lexeme);
        exit(1);
    }
  }


  //Implementação da gramática
  // E ::= T E'
  void parse_E(Parser* parser) {
      // printf("Analisando E\n");
      parse_T(parser);
      parse_E_prime(parser);
  }

  // E' ::= + T E' | - T E' | ε
  void parse_E_prime(Parser* parser) {
      // printf("Analisando E'\n");
      if (parser->current_token.type == TOKEN_PLUS) {
          parser_eat(parser, TOKEN_PLUS);
          parse_T(parser);
          parse_E_prime(parser);
      } else if (parser->current_token.type == TOKEN_MINUS) {
          parser_eat(parser, TOKEN_MINUS);
          parse_T(parser);
          parse_E_prime(parser);
      }
  }

  // T ::= F T'
  void parse_T(Parser* parser) {
      // printf("Analisando T\n");
      parse_F(parser);
      parse_T_prime(parser);
  }

  // T' ::= *FT' | /FT' | %FT' | ε

  void parse_T_prime(Parser* parser) {
      // printf("Analisando T'\n");
      if (parser->current_token.type == TOKEN_MULT) {
          parser_eat(parser, TOKEN_MULT);
          parse_F(parser);
          parse_T_prime(parser);
      } else if (parser->current_token.type == TOKEN_DIV) {
          parser_eat(parser, TOKEN_DIV);
          parse_F(parser);
          parse_T_prime(parser);
      }

      else if (parser->current_token.type == TOKEN_MOD) {
          parser_eat(parser, TOKEN_MOD);
          parse_F(parser);
          parse_T_prime(parser);
      }
  }

// F ::= num | ( E )

void parse_F(Parser* parser) {
    // printf("Analisando F\n");
    if (parser->current_token.type == TOKEN_NUM) {
        parser_eat(parser, TOKEN_NUM);
    } else if (parser->current_token.type == TOKEN_LPAREN) {
        parser_eat(parser, TOKEN_LPAREN);
        parse_E(parser);
        parser_eat(parser, TOKEN_RPAREN);
    } else {
        // printf("Erro de sintaxe: esperado número ou '(', mas recebido token tipo %d (%s)\n", 
        //        parser->current_token.type, parser->current_token.lexeme);
        exit(1);
    }
}

int parser_parse(Parser* parser) {
    // Verificar se a expressão começa com um parêntese de fechamento
    if (parser->current_token.type == TOKEN_RPAREN) {
        return 0; // Erro sintático: expressão começa com parêntese de fechamento
    } else if (parser->current_token.type == TOKEN_MINUS) {
        return 0;
    }
    else if (parser->current_token.type == TOKEN_PLUS) {
        return 0;
    }
    else if (parser->current_token.type == TOKEN_MULT) {
        return 0;
    }
    else if (parser->current_token.type == TOKEN_DIV) {
        return 0;
    }
    else if (parser->current_token.type == TOKEN_MOD) {
        return 0;
    }
    
    parse_E(parser);
    
    if (parser->current_token.type != TOKEN_EOF) {
        return 0; // Erro sintático: tokens extras após a expressão
    }
    
    return 1;
}