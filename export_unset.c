/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborgian <dborgian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:47:07 by tpiras            #+#    #+#             */
/*   Updated: 2023/11/09 17:54:13 by dborgian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_var(t_shell *mini, int i)
{
	int		j;
	char	**tmp_env;

	j = 0;
	while (mini->new_envp[j] != NULL)
		j++;
	tmp_env = ft_calloc(j + 1, sizeof(char *));
	j = 0;
	while (j != i)
	{
		tmp_env[j] = ft_strdup(mini->new_envp[j]);
		j++;
	}
	j++;
	while (mini->new_envp[j] != NULL)
	{
		tmp_env[j - 1] = ft_strdup(mini->new_envp[j]);
		j++;
	}
	tmp_env[j - 1] = NULL;
	free_matrix(mini->new_envp);
	copy_envp(mini, tmp_env);
	free_matrix(tmp_env);
}

void	delete_var2(t_shell *mini, int i)
{
	int		j;
	char	**tmp_env;

	j = 0;
	while (mini->envp[j])
		j++;
	tmp_env = ft_calloc(j + 1, sizeof(char *));
	j = 0;
	while (j != i)
	{
		tmp_env[j] = ft_strdup(mini->envp[j]);
		j++;
	}
	j++;
	while (mini->envp[j])
	{
		tmp_env[j - 1] = ft_strdup(mini->envp[j]);
		j++;
	}
	tmp_env[j - 1] = NULL;
	free_matrix(mini->envp);
	cloning_envp(mini, tmp_env);
	free_matrix(tmp_env);
}

void	command_unset2(t_shell *mini, char *str, int i)
{
	while (mini->envp[++i] != NULL)
	{
		if (ft_strncmp(mini->envp[i], str, ft_strlen(str)) == 0
			&& mini->envp[i][ft_strlen(str)] == '=')
		{
			delete_var2(mini, i);
			break ;
		}
	}
}

void	order_new_envp(t_shell *mini)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (mini->new_envp[i])
	{
		j = 0;
		while (mini->new_envp[i][j] != '=')
			j++;
		k = i + 1;
		while (mini->new_envp[k])
		{
			if (ft_strncmp(mini->new_envp[i], mini->new_envp[k], j) > 0)
			{
				swap_envp(mini, i, k);
				i = 0;
				break ;
			}
			k++;
		}
		i++;
	}
}
