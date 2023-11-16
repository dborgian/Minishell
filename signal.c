/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborgian <dborgian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:49:53 by tpiras            #+#    #+#             */
/*   Updated: 2023/11/08 16:11:08 by dborgian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	handlectrl(t_shell *mini, char **envp)
{
	char	input[256];

	if (!mini->input)
	{
		clear_mini(mini, 1);
		write(1, "exit\n", 5);
		exit(0);
	}
}

void	handlectrlc(int signal)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
