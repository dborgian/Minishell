/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertiz <ertiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:45:30 by tpiras            #+#    #+#             */
/*   Updated: 2023/09/11 16:59:42 by ertiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	first_command(t_shell *mini, t_pipex *pipes, t_args *cur)
{
	if (cur->infile != NULL)
	{
		if (cur->redirection_quantity == 1)
		{
			pipes->fd = open(cur->infile, O_RDONLY);
			dup2(pipes->fds[1], 1);
		}
		else if (cur->redirection_quantity == 2)
			screening_terminal(mini, cur, pipes->fd);
	}
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
		dup2(pipes->fds[(pipes->i) * 2 + 1], 1);
}

static void	last_command(t_shell *mini, t_pipex *pipes, t_args *cur)
{
	if (cur->infile != NULL)
	{
		if (cur->redirection_quantity == 1)
			pipes->fd = open(cur->infile, O_RDONLY);
		else if (cur->redirection_quantity == 2)
			screening_terminal(mini, cur, pipes->fd);
	}
	if (cur->outfile != NULL)
	{
		if (cur->redirection_quantity == 1)
			pipes->fd_out = open(cur->outfile,
					O_TRUNC | O_CREAT | O_RDWR, 0777);
		else if (cur->redirection_quantity == 2)
			pipes->fd_out = open(cur->outfile,
					O_APPEND | O_CREAT | O_RDWR, 0777);
		dup2(pipes->fd_out, STDOUT_FILENO);
	}
	if (cur->infile == NULL)
		dup2(pipes->fds[(pipes->i - 1) * 2], 0);
}

static void	mid_command(t_shell *mini, t_pipex *pipes, t_args *cur)
{
	if (cur->infile != NULL)
	{
		if (cur->redirection_quantity == 1)
			pipes->fd = open(cur->infile, O_RDONLY);
		else if (cur->redirection_quantity == 2)
			screening_terminal(mini, cur, pipes->fd);
	}
	else
		dup2(pipes->fds[(pipes->i - 1) * 2], 0);
	if (cur->outfile != NULL)
	{
		if (cur->redirection_quantity == 1)
			pipes->fd_out = open(cur->outfile,
					O_TRUNC | O_CREAT | O_RDWR, 0777);
		else if (cur->redirection_quantity == 2)
			pipes->fd_out = open(cur->outfile,
					O_APPEND | O_CREAT | O_RDWR, 0777);
		dup2(pipes->fd_out, STDOUT_FILENO);
	}
	else
		dup2(pipes->fds[pipes->i * 2 + 1], 1);
}

static void	end_builtin(t_pipex *pipes)
{
	dup2(pipes->std_in, 0);
	close(pipes->std_in);
	dup2(pipes->std_out, 1);
	close(pipes->std_out);
	if (pipes->fd != -1000)
		close(pipes->fd);
	if (pipes->fd_out != -1000)
		close(pipes->fd_out);
}

void	builtin_pipe(t_shell *mini, t_pipex *pipes, t_args *cur)
{
	if (pipes->i == 0 && pipes->num_pipes == 0
		&& cur->infile != NULL && cur->redirection_quantity == 1)
	{
		pipes->fd = open(cur->infile, O_RDONLY);
		if (dup2(pipes->fd, 0) == -1)
			perror(".failed to redirect output to pipe");
	}
	if (pipes->i == 0 && pipes->num_pipes == 0 && cur->outfile != NULL)
	{
		if (cur->redirection_quantity == 1)
			pipes->fd_out = open(cur->outfile,
					O_TRUNC | O_CREAT | O_RDWR, 0777);
		else if (cur->redirection_quantity == 2)
			pipes->fd_out = open(cur->outfile,
					O_APPEND | O_CREAT | O_RDWR, 0777);
		dup2(pipes->fd_out, 1);
	}
	else if (pipes->i == 0 && pipes->i != pipes->num_pipes)
		first_command(mini, pipes, cur);
	else if (pipes->i == pipes->num_pipes && pipes->i != 0)
		last_command(mini, pipes, cur);
	else if (pipes->i != 0 && pipes->i != pipes->num_pipes)
		mid_command(mini, pipes, cur);
	builtin_exec(mini, mini->envp, cur, cur->command);
	end_builtin(pipes);
}
