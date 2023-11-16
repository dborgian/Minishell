/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborgian <dborgian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:49:19 by tpiras            #+#    #+#             */
/*   Updated: 2023/11/13 18:48:13 by dborgian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	close_n_wait(t_pipex *pipes)
{
	pipes->i = 0;
	while (pipes->i < pipes->num_pipes * 2)
	{
		close(pipes->fds[pipes->i]);
		pipes->i++;
	}
	if (pipes->fd != -1000)
		close(pipes->fd);
	if (pipes->fd_out != -1000)
		close(pipes->fd_out);
	pipes->i = 0;
	while (pipes->i <= pipes->num_pipes)
	{
		waitpid(-1, &g_exit_status, 0);
		pipes->i++;
	}
}

void	august(t_shell *mini, t_pipex *pipes, t_args *cur, char ***commands)
{
	pipes->i = 0;
	while (pipes->i <= pipes->num_pipes)
	{
		free_matrix(commands[pipes->i]);
		pipes->i++;
	}
	free(commands);
	free(pipes->fds);
	free(pipes);
	if (cur->next != NULL && ft_strncmp(cur->next->redirect, "||", 2) == 0
		&& (WEXITSTATUS(g_exit_status) != 0 || mini->flag_status != 0))
		execpipe(mini, cur->next->next);
	if (cur->next != NULL && ft_strncmp(cur->next->redirect, "&&", 2) == 0)
		execpipe(mini, cur->next->next);
}

t_args	*while_in_pipes(t_shell *mini, t_pipex *pipes, t_args *cur,
		char ***commands)
{
	int	pid;

	while (++pipes->i <= pipes->num_pipes)
	{
		init_fd(pipes);
		if (check_builtin_presence(mini, cur->command) == 0)
			builtin_pipe(mini, pipes, cur);
		else if (check_builtin_presence(mini, cur->command) > 0)
		{
			pid = fork();
			if (pid == 0)
			{
				no_pipes(mini, pipes, cur, commands);
				first_command_in_pipe(mini, pipes, cur, commands);
				last_command_in_pipe(mini, pipes, cur, commands);
				mid_command_in_pipe(mini, pipes, cur, commands);
				while (++pipes->j < pipes->num_pipes * 2)
					close(pipes->fds[pipes->j]);
				execve(commands[pipes->i][0], commands[pipes->i], mini->envp);
			}
		}
		if (pipes->i < pipes->num_pipes)
			cur = cur->next->next;
	}
	return (cur);
}

void	execpipe(t_shell *mini, t_args *node)
{
	t_args	*cur;
	int		pid;
	char	***commands;
	t_pipex	*pipes;

	commands = NULL;
	cur = node;
	pipes = malloc(sizeof(t_pipex));
	init_pipexxx(pipes, mini, cur);
	commands = malloc((pipes->num_pipes + 1) * sizeof(char **));
	cur = node;
	pipes->i = 0;
	while (pipes->i < pipes->num_pipes)
	{
		pipe(pipes->fds + (pipes->i * 2));
		commands[pipes->i] = create_matri(cur);
		cur = cur->next->next;
		pipes->i++;
	}
	commands[pipes->num_pipes] = create_matri(cur);
	cur = node;
	pipes->i = -1;
	cur = while_in_pipes(mini, pipes, cur, commands);
	close_n_wait(pipes);
	august(mini, pipes, cur, commands);
}

void	screening_terminal(t_shell *mini, t_args *node, int temp_fd)
{
	char	*buffer;
	char	*res;

	res = ft_strdup("");
	while (1)
	{
		buffer = get_next_line(0);
		if (ft_strncmp(buffer, node->infile, ft_strlen(node->infile)) == 0)
			break ;
		res = ft_strjoin(res, buffer, FREE, NO_FREE);
	}
	free(buffer);
	free(node->infile);
	node->infile = NULL;
	if (ft_strcmp(node->command, "/usr/bin/cat") == 0)
	{
		temp_fd = open(".fa", O_TRUNC | O_CREAT | O_RDWR, 0777);
		ft_putstr_fd(res, temp_fd);
		free(node->argument);
		node->argument = ft_strdup(".fa");
		close(temp_fd);
	}
	else
		node->argument = ft_strdup(res);
	free(res);
}
