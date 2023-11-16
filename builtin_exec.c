/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborgian <dborgian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:45:24 by tpiras            #+#    #+#             */
/*   Updated: 2023/11/16 12:51:11 by dborgian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	command_env(t_shell *mini)
{
	int		j;
	char	*dollar;
	char	*argument;

	printf("env\n");
	j = 0;
	dollar = "$";
	if (mini->new_envp == NULL)
	{
		printf("envp is NULL\n");
		while (mini->envp[j] != NULL)
		{
			printf("%s\n", mini->envp[j]);
			j++;
		}
	}
	else
		command_env2(mini, dollar);
}

void	command_pwd(t_shell *mini, t_args *current)
{
	char	pwd_path[1024];

	if (getcwd(pwd_path, sizeof(pwd_path)) != NULL)
		printf("%s\n", pwd_path);
	else
	{
		printf("pwd: error\n");
		mini->flag_status = 1;
		g_exit_status = 1;
	}
}

static void	create_path(t_shell *mini, char *path)
{
	char	*temp;

	temp = ft_strtrim(mini->main_path, "$ ");
	free(mini->main_path);
	mini->main_path = ft_strjoin(temp, "/", FREE,
			NO_FREE);
	mini->main_path = ft_strjoin(mini->main_path, path, FREE,
			NO_FREE);
	temp = ft_strtrim(mini->main_path, "/");
	free(mini->main_path);
	mini->main_path = ft_strjoin(temp, "$ ", FREE,
			NO_FREE);
}

static void	command_cd2(t_shell *mini, char *path)
{
	char	*temp;
	char	*res;

	if (ft_strcmp(path, "..") == 0)
	{
		res = rev_string(mini->main_path);
		temp = ft_substr(mini->main_path, 0,
				ft_strlen(mini->main_path)
				- ft_strchr(res, '/') - 1);
		free(res);
		free(mini->main_path);
		mini->main_path = ft_strjoin(temp, "$ ", FREE,
				NO_FREE);
	}
	else if (ft_strcmp(path, ".") == 0)
		return ;
	else
		create_path(mini, path);
}

void	command_cd(t_shell *mini, t_args *node, char *arg)
{
	char	*curr_path;
	char	*path;

	curr_path = get_my_env(mini, "PWD");
	if (!arg)
		path = get_my_env(mini, "HOME");
	else
		path = ft_strdup(arg);
	if (chdir(path) == -1)
	{
		printf("chdir error: Bad address %s\n", path);
		mini->flag_status = 1;
		g_exit_status = 1;
	}
	free(curr_path);
	free(path);
}
