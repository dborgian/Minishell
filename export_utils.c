/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborgian <dborgian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:47:12 by tpiras            #+#    #+#             */
/*   Updated: 2023/11/09 17:47:20 by dborgian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_envp(t_shell *mini, char **envp)
{
	int		i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	mini->new_envp = malloc((i + 2) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		mini->new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	mini->new_envp[i] = NULL;
}

void	create_new_var(t_shell *mini, char *str)
{
	char	*name;
	char	*value;
	char	*new_var;
	int		i;

	i = 0;
	name = get_env_name(str);
	value = get_env_value(str);
	new_var = malloc((ft_strlen(name) + ft_strlen(value) + 2) * sizeof(char));
	ft_strcpy(new_var, name);
	ft_strcat(new_var, "=");
	ft_strcat(new_var, value);
	mini->new_envp = new_new_envp(new_var, mini);
	free(name);
	free(value);
	free(new_var);
}

char	*get_env_name(char *env)
{
	int		i;
	char	*name;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	name = malloc((i + 1) * sizeof(char));
	ft_strlcpy(name, env, (size_t)(i + 1));
	return (name);
}

char	*get_env_value(char *env)
{
	int		i;
	char	*res;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	res = ft_substr(env, i + 1, ft_strlen(env) - i - 1);
	res[ft_strlen(res)] = '\0';
	return (res);
}

void	swap_envp(t_shell *mini, int i, int k)
{
	char	*temp;

	temp = mini->new_envp[i];
	mini->new_envp[i] = mini->new_envp[k];
	mini->new_envp[k] = temp;
}
