#!/bin/bash

# Caminho para o executável do minishell
MINISHELL="./minishell"

# Arquivo de saída para resultados
OUTPUT_FILE="minishell_test_results.log"
> "$OUTPUT_FILE"  # Limpa o arquivo de saída antes de começar

log_result() {
  echo "$1" >> "$OUTPUT_FILE"
}

run_test() {
  local test_name="$1"
  local command="$2"
  local expected_behavior="$3"

  echo "[TEST] $test_name" | tee -a "$OUTPUT_FILE"
  echo "Comando: $command" | tee -a "$OUTPUT_FILE"

  # Executa o minishell com o comando
  echo "$command" | $MINISHELL > tmp_output.txt 2> tmp_error.txt
  local exit_status=$?

  # Verifica comportamento esperado
  if [[ "$expected_behavior" == "crash" && $exit_status -ne 0 ]]; then
    log_result "[PASS] $test_name: Minishell travou corretamente."
  elif [[ "$expected_behavior" == "incomplete" && $exit_status -ne 0 ]]; then
    log_result "[PASS] $test_name: Comportamento incompleto identificado."
  elif [[ "$expected_behavior" == "success" && $exit_status -eq 0 ]]; then
    log_result "[PASS] $test_name: Executado com sucesso."
  else
    log_result "[FAIL] $test_name: Saída inesperada. Verifique logs abaixo."
    cat tmp_output.txt >> "$OUTPUT_FILE"
    cat tmp_error.txt >> "$OUTPUT_FILE"
  fi

  echo "Saída do comando:" >> "$OUTPUT_FILE"
  cat tmp_output.txt >> "$OUTPUT_FILE"
  echo "Erro (se houver):" >> "$OUTPUT_FILE"
  cat tmp_error.txt >> "$OUTPUT_FILE"
  echo "" >> "$OUTPUT_FILE"

  # Limpa arquivos temporários
  rm -f tmp_output.txt tmp_error.txt
}

# Testes1 - Teste de comandos simples
echo -e "[INICIANDO TESTE 1 - COMANDOS SIMPLES]" | tee -a "$OUTPUT_FILE"

run_test "Comando simples absoluto" "/bin/ls" "success"
run_test "Comando vazio" "" "success"
run_test "Apenas espaços" "   " "success"
run_test "Apenas tabulações" "\t\t\t" "incomplete"

# Testes2 - Teste de argumentos
echo -e "\n[INICIANDO TESTE 2 - ARGUMENTOS]" | tee -a "$OUTPUT_FILE"

run_test "Comando com argumentos" "/bin/ls -l" "success"
run_test "Comando com múltiplos argumentos" "/bin/ls -l -a" "success"
run_test "Comando inexistente" "/bin/command_that_does_not_exist" "incomplete"

# Testes3 - Teste de echo
echo -e "\n[INICIANDO TESTE 3 - ECHO]" | tee -a "$OUTPUT_FILE"

echo_test_cases=(
  ""  # Sem argumentos
  "Hello, World!"  # Com argumento simples
  "-n No newline"  # Com opção -n
  "-n Multiple - arguments"  # Múltiplos argumentos com -n
)

for test_case in "${echo_test_cases[@]}"; do
  run_test "Echo comando: $test_case" "echo $test_case" "success"
done

# Testes4 - Teste de valor de retorno
echo -e "\n[INICIANDO TESTE 4 - VALOR DE RETORNO]" | tee -a "$OUTPUT_FILE"

return_value_tests=(
  "/bin/ls"  # Comando simples
  "/bin/ls nonexistentfile"  # Comando com erro
  "/bin/echo $?"  # Valor de retorno do último comando
  "expr $? + $?"  # Soma de valores de retorno
)

for test_case in "${return_value_tests[@]}"; do
  run_test "Valor de retorno: $test_case" "$test_case" "success"
done

# Testes5 - Teste de sinais
echo -e "\n[INICIANDO TESTE 5 - SINAIS]" | tee -a "$OUTPUT_FILE"

signal_tests=(
  "[TEST] Ctrl-C em prompt vazio" "sleep 1" "success"
  "[TEST] Ctrl-\\ em prompt vazio" "sleep 1" "success"
  "[TEST] Ctrl-D em prompt vazio" "exit" "crash"
  "[TEST] Ctrl-C após entrada" "echo test" "success"
  "[TEST] Ctrl-D após entrada" "echo test" "success"
  "[TEST] Ctrl-\\ após entrada" "echo test" "success"
  "[TEST] Ctrl-C durante cat" "cat" "success"
  "[TEST] Ctrl-\\ durante cat" "cat" "success"
  "[TEST] Ctrl-D durante cat" "cat" "success"
  "[TEST] Ctrl-C durante grep" "grep something" "success"
  "[TEST] Ctrl-\\ durante grep" "grep something" "success"
  "[TEST] Ctrl-D durante grep" "grep something" "success"
)

for test_case in "${signal_tests[@]}"; do
  run_test "Sinais: $test_case" "$test_case" "success"
done

# Testes6 - Teste de aspas duplas
echo -e "\n[INICIANDO TESTE 6 - ASPAS DUPLAS]" | tee -a "$OUTPUT_FILE"

quote_tests=(
  "echo \"cat lol.c | cat > lol.c\""  # Comando com aspas e espaços
  "echo \"Hello, World!\""  # Comando simples com aspas
  "echo \"Multiple   spaces   inside\""  # Múltiplos espaços em argumentos
  "echo \"\""  # Argumento vazio entre aspas duplas
)

for test_case in "${quote_tests[@]}"; do
  run_test "Aspas duplas: $test_case" "$test_case" "success"
done

# Testes7 - Teste de aspas simples
echo -e "\n[INICIANDO TESTE 7 - ASPAS SIMPLES]" | tee -a "$OUTPUT_FILE"

single_quote_tests=(
  "echo '\''"  # Argumento vazio
  "echo 'Hello, World!'"  # Comando simples com aspas simples
  "echo 'Multiple   spaces   inside'"  # Múltiplos espaços em argumentos
  "echo 'cat lol.c | cat > lol.c'"  # Argumento complexo
  "echo '$USER'"  # Não interpretar variáveis
  "echo 'Text with $ and special ! characters'"  # Especial não interpretado
)

for test_case in "${single_quote_tests[@]}"; do
  run_test "Aspas simples: $test_case" "$test_case" "success"
done

# Testes8 - Teste de variáveis de ambiente
echo -e "\n[INICIANDO TESTE 8 - VARIÁVEIS DE AMBIENTE]" | tee -a "$OUTPUT_FILE"

run_test "Variáveis de ambiente" "env" "success"

# Testes9 - Teste de export e variáveis de ambiente
echo -e "\n[INICIANDO TESTE 9 - EXPORT E VARIÁVEIS DE AMBIENTE]" | tee -a "$OUTPUT_FILE"

export_tests=(
    "export NEW_VAR=test"  # Criar nova variável
    "export HOME=new_value"  # Substituir valor existente
    "export PATH=/new/path:$PATH"  # Modificar PATH
    "export"  # Listar todas as variáveis exportadas
    "env"  # Verificar ambiente atual
)

for test_case in "${export_tests[@]}"; do
    run_test "Export: $test_case" "$test_case" "success"
done

# Testes10 - Teste de unset e variáveis de ambiente
echo -e "\n[INICIANDO TESTE 10 - UNSET E VARIÁVEIS DE AMBIENTE]" | tee -a "$OUTPUT_FILE"

unset_and_env_tests=(
    # Criar algumas variáveis para teste
    "export TEST_VAR1=value1"
    "export TEST_VAR2=value2"
    "export TEST_VAR3=value3"
    
    # Verificar se foram criadas
    "env | grep TEST_VAR"
    
    # Remover variáveis com unset
    "unset TEST_VAR1"
    "unset TEST_VAR2"
    
    # Verificar se foram removidas
    "env | grep TEST_VAR"
    
    # Tentar usar variável não definida
    "echo \$TEST_VAR1"
    
    # Verificar variável que não foi removida
    "echo \$TEST_VAR3"
    
    # Tentar fazer unset de variável que não existe
    "unset NONEXISTENT_VAR"
    
    # Verificar estado final do ambiente
    "env"
)

for test_case in "${unset_and_env_tests[@]}"; do
    run_test "Unset e ENV: $test_case" "$test_case" "success"
done

# Testes11 - Teste do comando cd
echo -e "\n[INICIANDO TESTE 11 - COMANDO CD]" | tee -a "$OUTPUT_FILE"

cd_tests=(
    # Teste com diretório existente
    "cd /home"
    "cd /tmp"
    "cd /etc"
    
    # Voltar para o diretório home
    "cd"
    
    # Teste com caminho relativo
    "cd .."
    "cd ../.."
    
    # Teste com diretório atual
    "cd ."
    "cd ./"
    
    # Testes que devem falhar
    "cd /diretorio_inexistente"
    "cd /root"  # Deve falhar sem permissão
    
    # Teste com múltiplos argumentos (deve falhar)
    "cd /tmp /home"
    
    # Teste com argumento vazio
    "cd \"\""
    
    # Verificar PWD após cada cd
    "cd /tmp"
    "pwd"
    "cd .."
    "pwd"
    "cd"
    "pwd"
)

for test_case in "${cd_tests[@]}"; do
    run_test "CD: $test_case" "$test_case" "success"
done

# Testes12 - Teste de Redirecionamentos
echo -e "\n[INICIANDO TESTE 12 - REDIRECIONAMENTOS]" | tee -a "$OUTPUT_FILE"

# Criar arquivo temporário para testes de entrada
echo "Hello World" > temp_input.txt
echo "Second line" >> temp_input.txt
echo "Third line" >> temp_input.txt

redirect_tests=(
    # Testes com >
    "echo 'test' > output1.txt"
    "/bin/ls > output2.txt"
    "echo 'overwrite' > output1.txt"
    
    # Testes com >>
    "echo 'append1' >> output3.txt"
    "echo 'append2' >> output3.txt"
    "echo 'append3' >> output3.txt"
    
    # Testes com <
    "cat < temp_input.txt"
    "grep 'Second' < temp_input.txt"
    "wc -l < temp_input.txt"
    
    # Combinação de < e >
    "cat < temp_input.txt > output4.txt"
    
    # Teste de erro com arquivo inexistente
    "cat < nonexistent_file.txt"
    
    # Teste de erro com permissão negada
    "echo 'test' > /root/test.txt"
    
    # Teste de here-document (<<)
    "cat << EOF
First Line
Second Line
Third Line
EOF"

    "cat << LIMIT
Testing here document
with multiple lines
LIMIT"

    # Teste here-document com palavra diferente
    "cat << CUSTOM
Custom delimiter
testing
CUSTOM"
)

for test_case in "${redirect_tests[@]}"; do
    run_test "Redirecionamento: $test_case" "$test_case" "success"
done

# Verificar conteúdo dos arquivos criados
echo "Verificando conteúdo dos arquivos:" >> "$OUTPUT_FILE"
for file in output*.txt; do
    if [ -f "$file" ]; then
        echo "Conteúdo de $file:" >> "$OUTPUT_FILE"
        cat "$file" >> "$OUTPUT_FILE"
        echo "---" >> "$OUTPUT_FILE"
    fi
done

# Limpar arquivos temporários
rm -f temp_input.txt output*.txt


# Exibe o resultado final
echo "Resultados gravados em $OUTPUT_FILE"
cat "$OUTPUT_FILE"
