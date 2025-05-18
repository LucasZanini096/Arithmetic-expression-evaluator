# Parser de Expressão Matemática

Este projeto implementa um analisador léxico, sintático e avaliador para expressões matemáticas em linguagem C. O sistema é capaz de analisar, converter para notação pós-fixa (polonesa reversa) e avaliar expressões aritméticas.

## Funcionalidades

- **Análise Léxica**: Tokenização da entrada em números, operadores e parênteses
- **Análise Sintática**: Verificação da estrutura gramatical das expressões
- **Conversão Infixa para Pós-fixa**: Transformação de expressões convencionais para notação polonesa reversa
- **Avaliação de Expressões**: Cálculo do resultado de expressões válidas

## Estrutura do Projeto

```
├── include/
│   ├── expression.h  # Funções para avaliação de expressões
│   ├── lexer.h       # Analisador léxico (tokenização)
│   ├── parser.h      # Analisador sintático
│   └── postfix.h     # Conversão para notação pós-fixa
├── src/
│   ├── expression.c  # Implementação do avaliador de expressões
│   ├── lexer.c       # Implementação do analisador léxico
│   ├── parser.c      # Implementação do analisador sintático
│   └── postfix.c     # Implementação da conversão para notação pós-fixa
├── main.c            # Ponto de entrada do programa
└── test_parser.sh    # Script de teste para o parser
```

## Gramática Implementada

O parser implementa a seguinte gramática para expressões matemáticas:

```
E  ::= T E'
E' ::= + T E' | - T E' | ε
T  ::= F T'
T' ::= *FT' | /FT' | %FT' | ε
F  ::= num | ( E )
```

Onde:
- `E` representa Expressão
- `T` representa Termo
- `F` representa Fator
- `num` representa um número
- `ε` representa uma produção vazia

## Operadores Suportados

- Adição (`+`)
- Subtração (`-`)
- Multiplicação (`*`)
- Divisão (`/`)
- Módulo (`%`)
- Parênteses para agrupar expressões

## Compilação e Execução

Para compilar o projeto:

```bash
gcc -o main main.c
```

Para executar o programa:

```bash
./main
```

O programa espera uma expressão matemática como entrada e retorna:
1. A expressão original
2. O resultado da análise sintática (sucesso ou erro)
3. A expressão convertida para notação pós-fixa (se válida)
4. O valor calculado da expressão (se válida)

## Exemplos de Uso

```bash
$ echo "5+2*3" | ./main
5+2*3 => Sucesso: 1
523*+
=11

$ echo "5*(2-4)/2" | ./main
5*(2-4)/2 => Sucesso: 1
524-*2/
=-5
```

## Testes Automatizados

O script `test_parser.sh` pode ser usado para executar vários casos de teste:

```bash
./test_parser.sh
```

## Limitações e Tratamento de Erros

- O programa verifica erros sintáticos como parênteses desbalanceados
- Divisão por zero é detectada e tratada
- Expressões inválidas geram mensagens de erro apropriadas
