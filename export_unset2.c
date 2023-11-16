/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborgian <dborgian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:52:06 by dborgian          #+#    #+#             */
/*   Updated: 2023/11/09 17:53:32 by dborgian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_export(t_shell *mini, char **envp, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	if (str != 0)
	{
		tmp = ft_substr(str, 0, my_strchr(str, '='));
		command_unset(mini, tmp);
		if (!mini->new_envp)
			copy_envp(mini, mini->envp);
		create_new_var(mini, str);
		order_new_envp(mini);
		free(tmp);
	}
	else
		return ;
}

void	command_unset(t_shell *mini, char *str)
{
	int	i;

	i = -1;
	if (str == NULL)
		return ;
	if (mini->new_envp != NULL)
	{
		while (mini->new_envp[++i] != NULL)
		{
			if (ft_strncmp(mini->new_envp[i], str, ft_strlen(str)) == 0
				&& mini->new_envp[i][ft_strlen(str)] == '=')
			{
				delete_var(mini, i);
				break ;
			}
		}
	}
	else
		command_unset2(mini, str, i);
}
