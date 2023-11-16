/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborgian <dborgian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:46:22 by tpiras            #+#    #+#             */
/*   Updated: 2023/11/13 18:53:18 by dborgian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	cloning_envp(t_shell *mini, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	mini->envp = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		mini->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	mini->envp[i] = NULL;
}

static void	init_first_stage(t_shell *mini, char **envp)
{
	char	*temp;

	mini->syntax = "$";
	mini->exit = 0;
	mini->home = NULL;
	mini->input = NULL;
	mini->command_presence = 0;
	mini->new_envp = NULL;
	cloning_envp(mini, envp);
	mini->home = getcwd(mini->home, sizeof(mini->home));
	temp = get_my_env(mini, "PWD");
	mini->main_path = ft_strjoin(temp, "$ ", NO_FREE, NO_FREE);
	mini->flag_status = 0;
	free(temp);
}

static void	second_stage(t_shell *mini)
{
	wild(mini);
	mini->flags.operators = 0;
	replacer(mini);
	execpipe(mini, *mini->list);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*mini;

	mini = ft_calloc(1, sizeof(t_shell));
	signal(SIGINT, handlectrlc);
	signal(SIGQUIT, SIG_IGN);
	init_first_stage(mini, envp);
	while (mini->exit == 0)
	{
		mini->list = ft_calloc(1, sizeof(t_args *));
		mini->high = ft_calloc(1, sizeof(t_args *));
		init_flags(mini);
		mini->input = readline("Minishell--> ");
		handlectrl(mini, envp);
		if (ft_strlen(mini->input) != 0)
			add_history(mini->input);
		if (start(mini) == 1)
		{
			insert_last_with_delimiter(mini, ' ');
			if (mini->exit == 0)
				second_stage(mini);
		}
		clear_mini(mini, 0);
		mini->exit = 0;
	}
	return (0);
}

void	init_flags(t_shell *mini)
{
	mini->flags.command_separator = 0;
	mini->flags.operators = 0;
	mini->flags.major = 0;
	mini->flags.minor = 0;
	mini->flags.redirect_input = 0;
	mini->flags.redirect_output = 0;
	mini->flags.brackets = 0;
	mini->flags.pipes = 0;
	mini->flags.quote_flag = 0;
	mini->dollar_flag = 0;
	mini->command_presence = 0;
}
