/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertiz <ertiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:49:10 by tpiras            #+#    #+#             */
/*   Updated: 2023/09/11 16:59:42 by ertiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fd(t_pipex *pipes)
{
	pipes->fd = -1000;
	pipes->fd_out = -1000;
	pipes->std_out = dup(1);
	pipes->std_in = dup(0);
}

void	init_pipexxx(t_pipex *pipes, t_shell *mini, t_args *cur)
{
	pipes->num_pipes = 0;
	pipes->j = -1;
	while (cur != NULL && cur->next != NULL
		&& cur->next->redirect[0] == '|' && cur->next->redirect[1] != '|')
	{
		pipes->num_pipes++;
		cur = cur->next->next;
	}
	pipes->i = 0;
	pipes->fds = malloc(pipes->num_pipes * 2 * sizeof(int));
}

char	**redirect_input_no_pipes(t_shell *mini, t_args *node,
		char ***commands, char **envp)
{
	int	temp_fd;

	temp_fd = 1;
	if (node->infile != NULL)
	{
		if (node->redirection_quantity == 2)
		{
			screening_terminal(mini, node, temp_fd);
			if (ft_strcmp(node->command, "/usr/bin/cat") == 0)
			{
				temp_fd = open(".fa", O_RDONLY, 0777);
				free_matrix(commands[0]);
				commands[0] = create_matri(node);
			}
		}
		dup2(1, temp_fd);
		close(temp_fd);
	}
}

void	no_pipes(t_shell *mini, t_pipex *pipes,
		t_args *cur, char ***commands)
{
	if (pipes->i == 0 && pipes->num_pipes == 0 && cur->infile != NULL
		&& cur->redirection_quantity == 2)
		redirect_input_no_pipes(mini, cur, commands, mini->envp);
	if (pipes->i == 0 && pipes->num_pipes == 0 && cur->infile != NULL
		&& cur->redirection_quantity == 1)
	{
		pipes->fd = open(cur->infile, O_RDONLY, 0777);
		dup2(pipes->fd, 0);
		close(pipes->fd);
	}
	if (pipes->i == 0 && pipes->num_pipes == 0 && cur->outfile != NULL)
	{
		if (cur->redirection_quantity == 1)
			pipes->fd_out = open(cur->outfile,
					O_TRUNC | O_CREAT | O_RDWR, 0777);
		else if (cur->redirection_quantity == 2)
			pipes->fd_out = open(cur->outfile,
					O_APPEND | O_CREAT | O_RDWR, 0777);
		dup2(pipes->fd_out, STDOUT_FILENO);
	}
}

void	first_command_w_outfile(t_pipex *pipes, t_args *cur)
{
	if (cur->outfile != NULL)
	{
		if (cur->redirection_quantity == 1)
			pipes->fd_out = open(cur->outfile,
					O_TRUNC | O_CREAT | O_RDWR, 0777);
		else if (cur->redirection_quantity == 2)
			pipes->fd_out = open(cur->outfile,
					O_APPEND | O_CREAT | O_RDWR, 0777);
		dup2(pipes->fd_out, 1);
	}
	if (cur->outfile == NULL)
		dup2(pipes->fds[1], 1);
}
