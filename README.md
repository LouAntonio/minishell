# Minishell Project

Este repositório contém um resumo das principais funções em C que são fundamentais para a implementação do projeto **Minishell**. Abaixo, você encontrará detalhes sobre a assinatura, bibliotecas, retorno, propósito e exemplos de uso dessas funções.

## Funções de Leitura de Linha e Histórico

### `readline`
- **Biblioteca**: `readline/readline.h`
- **Assinatura**: `char *readline(const char *prompt);`
- **Retorno**: Ponteiro para a string lida ou `NULL` em erro.
- **O que faz**: Lê uma linha de entrada com um prompt personalizado.
- **Exemplo**:
  ```c
  char *input = readline("minishell> ");

### `add_history`
- **Biblioteca**: `readline/readline.h`
- **Assinatura**: `void add_history(const char *line);`
- **Retorno**: Nenhum.
- **O que faz**: Adiciona uma linha ao histórico de comandos.
- **Exemplo**:
  ```c
  add_history(input);

### `rl_clear_history`
- **Biblioteca**: `readline/readline.h`
- **Assinatura**: `void rl_clear_history(void);`
- **Retorno**: Nenhum.
- **O que faz**: Limpa o histórico de comandos..

### `rl_on_new_line`
- **Biblioteca**: `readline/readline.h`
- **Assinatura**: `int rl_on_new_line(void);`
- **Retorno**: 0 em sucesso.
- **O que faz**: Indica que o cursor está em uma nova linha.

### `rl_replace_line`
- **Biblioteca**: `readline/readline.h`
- **Assinatura**: `int rl_replace_line(const char *text, int clear_undo);`
- **Retorno**: 0 em sucesso.
- **O que faz**: Substitui o texto da linha atual.

### `rl_redisplay`
- **Biblioteca**: `readline/readline.h`
- **Assinatura**: `void rl_redisplay(void);`
- **Retorno**: Nenhum.
- **O que faz**: Redesenha o prompt e a linha de entrada.
