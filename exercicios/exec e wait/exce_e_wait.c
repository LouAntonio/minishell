#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int	gerar_ps_filho(char *programa, char **command_line)
{
	pid_t	pid_filho;

	pid_filho = fork();
	if (pid_filho != 0)
		return (pid_filho);
	else
	{
		execvp(programa, command_line);
		fprintf(stderr, "erro em execvp\n");
		exit(1);
	}
}

int	main(void)
{
	int		status_filho;
	char	*command_line[] = {"ls", "-l", "/", NULL};

	gerar_ps_filho(command_line[0], command_line);
	wait(&status_filho);
	if (WIFEXITED(status_filho))
		printf("O processo filho terminou normalmente, com codigo de saida: %d\n", WEXITSTATUS(status_filho));
    else
        printf("O processo filho terminou anormalmente\n");
        
	return (0);
}
