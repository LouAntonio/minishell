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

## Gerenciamento de Arquivos e Processos

### `fork`
- **Biblioteca**: `unistd.h`
- **Assinatura**: `pid_t fork(void);`
- **Retorno**: PID do processo filho para o pai, 0 para o filho, -1 em erro.
- **O que faz**: Cria um novo processo.
- **Exemplo**:
  ```c
  pid_t pid = fork();

### `wait`
- **Biblioteca**: `sys/wait.h`
- **Assinatura**: `pid_t wait(int *wstatus);`
- **Retorno**: PID do processo filho ou -1 em erro.
- **O que faz**: Aguarda a finalização de um processo filho.
- **Exemplo**:
  ```c
  wait(NULL);

### `open`
- **Biblioteca**: `fcntl.h`
- **Assinatura**: `int open(const char *pathname, int flags, mode_t mode);`
- **Retorno**: Descritor de arquivo ou -1 em erro.
- **O que faz**: Abre ou cria um arquivo.
- **Exemplo**:
  ```c
  int fd = open("file.txt", O_RDONLY);

### `read`
- **Biblioteca**: `unistd.h`
- **Assinatura**: `ssize_t read(int fd, void *buf, size_t count);`
- **Retorno**: Número de bytes lidos ou -1 em erro.
- **O que faz**: Lê dados de um descritor de arquivo.
- **Exemplo**:
  ```c
  read(fd, buffer, 100);

### `close`
- **Biblioteca**: `unistd.h`
- **Assinatura**: `int close(int fd);`
- **Retorno**: 0 em sucesso, -1 em erro.
- **O que faz**: Fecha um descritor de arquivo.
- **Exemplo**:
  ```c
  close(fd);

### `execve`
- **Biblioteca**: `unistd.h`
- **Assinatura**: `int execve(const char *filename, char *const argv[], char *const envp[]);`
- **Retorno**: Não retorna em sucesso, -1 em erro.
- **O que faz**:  Executa um programa.
- **Exemplo**:
  ```c
  char *args[] = {"/bin/ls", NULL};
  execve("/bin/ls", args, NULL);

