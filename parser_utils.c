/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertiz <ertiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:48:37 by tpiras            #+#    #+#             */
/*   Updated: 2023/09/22 18:09:33 by ertiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static void	red_quantity(t_shell *mini, int res)
{
	if (res == 2 || res == 4)
		(*mini->high)->redirection_quantity = 1;
	else if (res == 1 || res == 3)
		(*mini->high)->redirection_quantity = 2;
}

static void	calculating_flags(t_shell *mini, int res, char *temp)
{
	if (res == 1 && (*mini->high)->infile == NULL)
		mini->flags.redirect_input = 1;
	else if (res == 2 && (*mini->high)->infile == NULL)
		mini->flags.minor = 1;
	else if (res == 3 && (*mini->high)->outfile == NULL)
		mini->flags.redirect_output = 1;
	else if (res == 4 && (*mini->high)->outfile == NULL)
		mini->flags.major = 1;
	else if (res == 6)
		mini->flags.pipes = 1;
	if (ft_strlen(temp) < 3 && temp[0] != '>' && temp[0] != '<')
	{
		if ((*mini->high)->redirect != NULL)
			free((*mini->high)->redirect);
		(*mini->high)->redirect = ft_strdup(temp);
		mini->command_presence = 0;
	}
	else if (ft_strlen(temp) >= 3 && (*mini->high)->argument == NULL)
		(*mini->high)->argument = ft_strdup(temp);
	else if (temp[0] != '>' && temp[0] != '<')
		(*mini->high)->argument = ft_strjoin_mini((*mini->high)->argument, temp,
				NO_FREE, NO_FREE);
	red_quantity(mini, res);
}

static void	making_outfile(t_shell *mini, char *temp)
{
	if ((*mini->high)->command != NULL && (mini->flags.major == 1
			|| mini->flags.redirect_output == 1) && temp[0] != '>')
	{
		(*mini->high)->outfile = ft_strdup(temp);
		mini->flags.redirect_output = 0;
		mini->flags.major = 0;
	}
	if ((*mini->high)->argument != NULL && ((*mini->high)->outfile == NULL)
		&& temp[0] != '>' && temp[0] != '<')
		(*mini->high)->argument = ft_strjoin_mini((*mini->high)->argument,
				temp, FREE, NO_FREE);
	if ((*mini->high)->argument == NULL && ((*mini->high)->outfile == NULL
			&& (*mini->high)->infile == NULL) && temp[0] != '>'
		&& temp[0] != '<')
		(*mini->high)->argument = ft_strdup(temp);
}

static void	making_infile(t_shell *mini, char *temp)
{
	if ((*mini->high)->command != NULL && mini->flags.redirect_input == 1
		&& temp[0] != '<')
	{
		(*mini->high)->infile = ft_strdup(temp);
		mini->flags.redirect_input = 0;
	}
	else if (mini->command_presence != 0 && mini->flags.minor == 1
		&& temp[0] != '<')
	{
		(*mini->high)->infile = ft_strdup(temp);
		mini->flags.minor = 0;
	}
	else if (mini->command_presence == 0 && mini->flags.minor == 1)
	{
		if (temp[0] == '<')
			return ;
		else
		{
			(*mini->high)->infile = ft_strdup(temp);
			mini->flags.minor = 0;
			mini->flags.redirect_input = 0;
		}
	}
}

void	its_not_a_command(t_shell *mini, char *temp, int i)
{
	int	res;

	res = check_redirection(temp);
	if (res == -2)
	{
		mini->exit = 1;
		return ;
	}
	if (res > 0)
		calculating_flags(mini, res, temp);
	if ((*mini->high)->command == NULL && mini->command_presence == 0
		&& mini->flags.minor == 0 && (*mini->high)->redirect == NULL)
	{
		if (mini->flags.major == 0 && mini->flags.redirect_output == 0)
		{
			mini->flag_status = 127;
			g_exit_status = 127;
			return ;
		}
	}
	else
	{
		making_infile(mini, temp);
		making_outfile(mini, temp);
	}
}
