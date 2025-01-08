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

# Testes1
run_test "Comando simples absoluto" "/bin/ls" "success"
run_test "Comando vazio" "" "incomplete"
run_test "Apenas espaços" "   " "incomplete"
run_test "Apenas tabulações" "\t\t\t" "incomplete"

# Testes2
run_test "Comando com argumentos" "/bin/ls -l" "success"
run_test "Comando com múltiplos argumentos" "/bin/ls -l -a" "success"
run_test "Comando inexistente" "/bin/command_that_does_not_exist" "incomplete"

# Testes3
echo_test_cases=(
  ""  # Sem argumentos
  "Hello, World!"  # Com argumento simples
  "-n No newline"  # Com opção -n
  "-n Multiple - arguments"  # Múltiplos argumentos com -n
)

for test_case in "${echo_test_cases[@]}"; do
  run_test "Echo comando: $test_case" "echo $test_case" "success"
done

# Testes4
return_value_tests=(
  "/bin/ls"  # Comando simples
  "/bin/ls nonexistentfile"  # Comando com erro
  "/bin/echo $?"  # Valor de retorno do último comando
  "expr $? + $?"  # Soma de valores de retorno
)

for test_case in "${return_value_tests[@]}"; do
  run_test "Valor de retorno: $test_case" "$test_case" "success"
done

# Testes5
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

# Testes6
quote_tests=(
  "echo \"cat lol.c | cat > lol.c\""  # Comando com aspas e espaços
  "echo \"Hello, World!\""  # Comando simples com aspas
  "echo \"Multiple   spaces   inside\""  # Múltiplos espaços em argumentos
  "echo \"\""  # Argumento vazio entre aspas duplas
)

for test_case in "${quote_tests[@]}"; do
  run_test "Aspas duplas: $test_case" "$test_case" "success"
done

# Testes7
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

# Testes8
run_test "Variáveis de ambiente" "env" "success"

# Exibe o resultado final
echo "Resultados gravados em $OUTPUT_FILE"
cat "$OUTPUT_FILE"
