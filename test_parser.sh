#!/bin/bash

# Compilar o programa (ajuste conforme necessário)
gcc -o main main.c

# Arquivo com as expressões de teste
TESTS="
5+2*3
5*(2-4)/2)
5-4*((3)+2)
4*(9/3+2)-1
)2*5
5+3%3
"

# Arquivo temporário para testes
TEST_FILE=$(mktemp)

# Escrever testes no arquivo
echo "$TESTS" > "$TEST_FILE"

# Executar testes
echo "Executando testes..."
while IFS= read -r expr; do
    # Ignorar linhas vazias
    if [ -z "$expr" ]; then
        continue
    fi
    
    echo "Testando: $expr"
    echo "$expr" | ./main
    echo "-----------------------------------"
done < "$TEST_FILE"

# Limpar
rm "$TEST_FILE"