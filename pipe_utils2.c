/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertiz <ertiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:49:14 by tpiras            #+#    #+#             */
/*   Updated: 2023/09/11 16:59:42 by ertiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	first_command_in_pipe(t_shell *mini, t_pipex *pipes,
			t_args *cur, char ***commands)
{
	if (pipes->i == 0 && pipes->i != pipes->num_pipes)
	{
		if (cur->infile != NULL)
		{
			if (cur->redirection_quantity == 1)
			{
				pipes->fd = open(cur->infile, O_RDONLY, 0777);
				dup2(pipes->fd, 0);
			}
			else if (cur->redirection_quantity == 2)
			{
				screening_terminal(mini, cur, pipes->fd);
				if (ft_strcmp(cur->command, "/usr/bin/cat") == 0)
					commands[0] = create_matri(cur);
			}
		}
		first_command_w_outfile(pipes, cur);
	}
}

void	last_command_w_outfile(t_pipex *pipes, t_args *cur)
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
}

void	last_command_in_pipe(t_shell *mini, t_pipex *pipes,
			t_args *cur, char ***commands)
{
	if (pipes->i == pipes->num_pipes && pipes->i != 0)
	{
		if (cur->infile != NULL)
		{
			if (cur->redirection_quantity == 1)
			{
				pipes->fd = open(cur->infile, O_RDONLY, 0777);
				dup2(pipes->fd, 0);
			}
			else if (cur->redirection_quantity == 2)
			{
				screening_terminal(mini, cur, pipes->fd);
				if (ft_strcmp(cur->command, "/usr/bin/cat") == 0)
					commands[pipes->i] = create_matri(cur);
			}
		}
		else if (cur->infile == NULL)
			dup2(pipes->fds[(pipes->i - 1) * 2], 0);
		last_command_w_outfile(pipes, cur);
	}
}

void	mid_command_w_outfile(t_pipex *pipes, t_args *cur)
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
	else if (cur->outfile == NULL)
		dup2(pipes->fds[pipes->i * 2 + 1], 1);
}

void	mid_command_in_pipe(t_shell *mini, t_pipex *pipes, t_args *cur,
				char ***commands)
{
	if (pipes->i != 0 && pipes->i != pipes->num_pipes)
	{
		if (cur->infile != NULL)
		{
			if (cur->redirection_quantity == 1)
			{
				pipes->fd = open(cur->infile, O_RDONLY, 0777);
				dup2(pipes->fd, 0);
			}
			else if (cur->redirection_quantity == 2)
			{
				screening_terminal(mini, cur, pipes->fd);
				if (ft_strcmp(cur->command, "/usr/bin/cat") == 0)
					commands[pipes->i] = create_matri(cur);
			}
		}
		else if (cur->infile == NULL)
			dup2(pipes->fds[(pipes->i - 1) * 2], 0);
		mid_command_w_outfile(pipes, cur);
	}
}
