Sua shell deve:

- Exibir um prompt ao esperar um novo comando.
- Ter um histórico funcional.
- Buscar e executar o executável correto (com base na variável PATH ou usando um caminho relativo ou absoluto).
- Evitar o uso de mais de uma variável global para indicar um sinal recebido. Essa variável não deve fornecer acesso a dados ou estruturas além do número do sinal recebido. Assim, é proibido usar estruturas “norm” no escopo global.

  **Cuidado:** Essa variável global não pode fornecer nenhuma outra informação ou acesso a dados além do número do sinal recebido.

- Não interpretar aspas não fechadas ou caracteres especiais que não sejam exigidos pelo enunciado, como `\` (barra invertida) ou `;` (ponto e vírgula).
- Lidar com `'` (aspas simples), que devem impedir a shell de interpretar metacaracteres na sequência entre aspas.
- Lidar com `"` (aspas duplas), que devem impedir a shell de interpretar metacaracteres na sequência entre aspas, exceto `$` (sinal de dólar).
- Implementar redirecionamentos:
  - `<` deve redirecionar a entrada.
  - `>` deve redirecionar a saída.
  - `<<` deve ser seguido de um delimitador, lendo a entrada até que uma linha contendo o delimitador seja encontrada (não precisa atualizar o histórico).
  - `>>` deve redirecionar a saída em modo de anexo.
- Implementar pipes (`|`), conectando a saída de cada comando na tubulação à entrada do próximo comando.
- Lidar com variáveis de ambiente (`$` seguido de uma sequência de caracteres), que devem expandir para seus respectivos valores.
- Lidar com `$?`, que deve expandir para o status de saída do último pipeline em primeiro plano executado.
- Lidar com `ctrl-C`, `ctrl-D` e `ctrl-\`, que devem se comportar como no bash.
- Em modo interativo:
  - `ctrl-C` exibe um novo prompt em uma nova linha.
  - `ctrl-D` sai da shell.
  - `ctrl-\` não faz nada.
- Sua shell deve implementar os seguintes comandos internos:
  - `echo` com a opção `-n`
  - `cd` apenas com caminho relativo ou absoluto
  - `pwd` sem opções
  - `export` sem opções
  - `unset` sem opções
  - `env` sem opções ou argumentos
  - `exit` sem opções

A função `readline()` pode causar vazamentos de memória. Você não precisa corrigir esses vazamentos, mas o seu próprio código **não deve ter vazamentos de memória**.

Limite-se à descrição do enunciado. Qualquer coisa que não for solicitada não é necessária.
Em caso de dúvida sobre algum requisito, tome o bash como referência.