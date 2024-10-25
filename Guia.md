# 1. (Conceitos sobre Sistemas Operacionais)[https://www.fabriciobreve.com/class-materials/sistemas-operacionais-ii/] 

## Processos e Execução de Comandos
- Entender como os processos funcionam.
- Criar e gerenciar processos usando `fork()`.
- Substituir o processo atual com um novo comando usando `execve()`.
- Esperar que processos terminem usando `wait()` ou `waitpid()`.

## Redirecionamento de Entrada e Saída
- Aprender a redirecionar a saída e a entrada padrão (`stdin`, `stdout`, `stderr`) usando operadores como `>`, `<`, e `|`.

## Sinais
- Saber como lidar com sinais, como `SIGINT` (Ctrl + C) e `SIGQUIT` (Ctrl + \), usando `signal()` ou `sigaction()` para capturar e gerenciar esses sinais.

# 2. Manipulação de Strings

## Parsing
- Ser capaz de quebrar a linha de comando em diferentes partes (tokens) usando funções como `strtok()`, `split()`, ou implementando seu próprio parser.

## Tratamento de Cotas e Variáveis
- Aprender a lidar com aspas simples e duplas, assim como variáveis de ambiente (ex: `$HOME`), e expandi-las adequadamente.

# 3. Execução de Comandos Simples e Combinados

## Comandos Internos (Built-ins)
- Certos comandos como `cd`, `echo`, `exit`, e `export` precisam ser implementados manualmente. Eles são executados diretamente pela shell e não necessitam de processos filhos.

## Pipes e Encadeamento de Comandos
- Implementar pipes (`|`) para que a saída de um comando seja a entrada de outro. Isso envolve manipulação de descritores de arquivos.

# 4. Ambiente de Shell

## Variáveis de Ambiente
- Entender como acessar e modificar variáveis de ambiente usando funções como `getenv()`, `setenv()`, e `unsetenv()`.

## Comandos PATH
- Entender como a shell resolve o caminho de um comando (usando a variável `PATH`).

# 5. Estruturas de Dados

## Listas Ligadas
- Elas são úteis para armazenar comandos ou redirecionamentos temporariamente.

# Passos Iniciais
- **Compreensão da Shell Existente:** Use o terminal para executar comandos e veja como diferentes funcionalidades funcionam, como o redirecionamento, pipes e sinais.
- **Estrutura Básica:** Comece implementando a leitura da entrada do usuário e o parsing básico (separando os comandos).
- **Execução de Comandos Simples:** Com base no que o usuário digita, execute comandos externos usando `fork()` e `execve()`.
- **Adicionar Funcionalidades:** Aos poucos, vá adicionando redirecionamento de entrada/saída, tratamento de sinais e built-ins.
