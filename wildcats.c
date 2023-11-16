/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcats.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborgian <dborgian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:50:16 by tpiras            #+#    #+#             */
/*   Updated: 2023/11/16 12:35:10 by dborgian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wildthree(t_args *node, char *d_name, int *count)
{
	while (node->argument[count[0]] != '\0' && d_name[count[1]] != '\0')
	{
		if (node->argument[count[0]] == d_name[count[1]] && count[1] != 0)
		{
			count[0]++;
			count[1]++;
		}
		else if (node->argument[count[0]] == '*')
		{
			count[0]++;
			while (node->argument[count[0]] != d_name[count[1]]
				&& d_name[count[1]] != '\0')
				count[1]++;
		}
		else
		{
			count[3] = 1;
			break ;
		}
	}
}

static void	skip(t_args *node, char *d_name, int *count)
{
	while (node->argument[count[0]] == d_name[count[1]])
	{
		count[0]++;
		count[1]++;
	}
}

static void	wildtwo(t_args *node, char *d_name, int *c, char **temp)
{
	c[0] = 0;
	c[1] = 0;
	c[3] = 0;
	while (node->argument[c[0]] != '\0')
	{
		skip(node, d_name, c);
		if (node->argument[c[0]] != d_name[c[1]] && node->argument[c[0]] != '*')
			break ;
		if (node->argument[c[0]] == '*')
		{
			c[0]++;
			while (node->argument[c[0]] != d_name[c[1]]
				&& d_name[c[1]] != '\0')
				c[1]++;
			wildthree(node, d_name, c);
			if (c[3] == 0 && node->argument[c[0]] == '\0')
				temp[c[2]++] = ft_strdup(d_name);
			if (c[3] == 1)
				break ;
		}
		if (node->argument[c[0]] != '*')
			c[0]++;
	}
}

static void	wildfour(t_args *node, DIR *dir, int *count, char **temp)
{
	struct dirent	*test;

	test = readdir(dir);
	while (test != NULL)
	{
		if (ft_strncmp(test->d_name, ".", 1) == 0)
			test = readdir(dir);
		else
			wildtwo(node, test->d_name, count, temp);
		test = readdir(dir);
	}
}

char	**wildone(t_shell *mini, t_args *node)
{
	DIR				*dir;
	struct dirent	*test;
	char			pwd_path[1024];
	char			**temp;
	int				count[4];

	getcwd(pwd_path, sizeof(pwd_path));
	dir = opendir(pwd_path);
	temp = ft_calloc(counting_dir(pwd_path) + 1, sizeof(char *));
	control('*', node);
	count[2] = 0;
	if (ft_strcmp(node->argument, "*") == 0)
	{
		case_one(dir, temp);
		return (temp);
	}
	else
		wildfour(node, dir, count, temp);
	temp[count[2]] = NULL;
	closedir(dir);
	if (temp[0] == NULL)
		return (NULL);
	return (temp);
}
