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
    if (parser->current_token.type == TOKEN_NUM) {
        parser_eat(parser, TOKEN_NUM);
    } else if (parser->current_token.type == TOKEN_LPAREN) {
        parser_eat(parser, TOKEN_LPAREN);
        parse_E(parser);
        parser_eat(parser, TOKEN_RPAREN);
    } else {
        // Token inválido - força erro
        // fprintf(stderr, "Erro de sintaxe: token inválido '%s'\n", parser->current_token.lexeme);
        exit(1);
    }
}

int parser_parse(Parser* parser) {
    // Primeiro verifica se há algum token de erro
    if (parser->current_token.type == TOKEN_ERROR) {
        return 0;
    }

    // Verifica se começa com parêntese direito (inválido)
    if (parser->current_token.type == TOKEN_RPAREN) {
        return 0;
    }

    // Verifica se começa com operadores (inválido)
    if (parser->current_token.type == TOKEN_MOD || 
        parser->current_token.type == TOKEN_MULT || 
        parser->current_token.type == TOKEN_DIV || 
        parser->current_token.type == TOKEN_PLUS || 
        parser->current_token.type == TOKEN_MINUS) {
        return 0;
    }

    // Verifica se é EOF no início (entrada vazia)
    if (parser->current_token.type == TOKEN_EOF) {
        return 0;
    }
    
    // Tenta fazer o parse da expressão
    parse_E(parser);
    
    // Verifica se chegou ao final corretamente
    if (parser->current_token.type != TOKEN_EOF) {
        return 0;
    }
    
    return 1;
}