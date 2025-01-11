/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:20:22 by hmateque          #+#    #+#             */
/*   Updated: 2024/12/14 18:20:22 by hmateque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sigquit_received(void)
{
	if (g_signal == 0)
	{
		ft_putendl_fd("minishell (◕‿◕): warning:\
here-document delimited by end of file", STDERR_FILENO);
		update_exit_status(0);
	}
}

int	create_heredoc_temp(t_node *node)
{
	static int	num;
	int			fd;
	char		*filename;
	char		*temp_path;

	filename = ft_itoa(num);
	temp_path = ft_strjoin("/tmp/.here_", filename);
	collect_mem(temp_path);
	fd = open(temp_path, O_CREAT | O_RDWR | O_TRUNC, 0777);
	node->value = temp_path;
	num++;
	free(filename);
	return (fd);
}

int	check_delimiter(int fd, t_node *head, char *heredoc_input, char *delimiter)
{
	while (heredoc_input && ft_strcmp(heredoc_input, delimiter) != 0)
	{
		collect_mem(heredoc_input);
		if (head->next->type != DOUB_QUOTE && head->next->type != SING_QUOTE)
			heredoc_input = expand_heredoc(heredoc_input);
		if (heredoc_input)
			heredoc_input = ft_strjoin(heredoc_input, "\n");
		else
			heredoc_input = ft_strdup("\n");
		collect_mem(heredoc_input);
		write(fd, heredoc_input, ft_strlen(heredoc_input));
		heredoc_input = readline("> ");
	}
	if (!heredoc_input)
	{
		sigquit_received();
		if (g_signal == 130)
			return (1);
	}
	return (0);
}

void	check_heredoc(t_node *head)
{
	int		fd;
	char	*heredoc_input;
	char	*delimiter;

	fd = -1;
	while (head->next)
	{
		if (head->type == HEREDOC)
		{
			join_delimiter(head->next);
			signal(SIGINT, sigint_cmd_handler);
			delimiter = head->next->value;
			check_quote_delimiter(head, &delimiter);
			fd = create_heredoc_temp(head->next);
			heredoc_input = readline("> ");
			if (check_delimiter(fd, head, heredoc_input, delimiter))
				break ;
		}
		head = head->next;
	}
}
