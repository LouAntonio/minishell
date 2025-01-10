#!/bin/bash

# Caminho para o seu executável minishell
MINISHELL_PATH="./minishell"

# Teste os comandos fornecidos
commands=(
  "'"
  '"'
  "                               "
  "<>"
  "<<>>"
  " <<      >>      "
  " <      >      "
)

# Executar os comandos
echo "Iniciando testes no Minishell..."
for cmd in "${commands[@]}"; do
  echo "Testando comando: '$cmd'"
  echo "$cmd" | $MINISHELL_PATH
  if [ $? -ne 0 ]; then
    echo "Erro detectado no comando: '$cmd'"
  else
    echo "Comando executado com sucesso: '$cmd'"
  fi
  sleep 1
done

echo "Testes finalizados."
