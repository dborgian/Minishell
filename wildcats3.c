/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcats3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborgian <dborgian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:50:28 by tpiras            #+#    #+#             */
/*   Updated: 2023/11/16 12:50:14 by dborgian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	counting_dir(char *cartella)
{
	int				nb;
	DIR				*dir;
	struct dirent	*test;

	nb = 0;
	dir = opendir(cartella);
	test = readdir(dir);
	if (!dir)
		return (0);
	while (test != NULL)
	{
		if (ft_strncmp(test->d_name, ".", 1) != 0)
			nb++;
		test = readdir(dir);
	}
	closedir(dir);
	return (nb);
}

void	**case_one( DIR *dir, char **temp)
{
	int				k;
	struct dirent	*test;

	k = 0;
	test = readdir(dir);
	while (test != NULL)
	{
		if (ft_strncmp(test->d_name, ".", 1) != 0)
		{
			temp[k] = ft_strdup(test->d_name);
			k++;
		}
		test = readdir(dir);
	}
	temp[k] = NULL;
	closedir(dir);
}

static void	hub(t_args *node, char *temp)
{
	free(node->argument);
	node->argument = NULL;
	node->argument = ft_strdup(temp);
}

void	control(char c, t_args *node)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = ft_calloc(ft_strlen(node->argument) + 1, sizeof(char));
	while (node->argument[i] != '\0')
	{
		if (node->argument[i] == c)
		{
			temp[j] = node->argument[i];
			while (node->argument[i] == c)
				i++;
		}
		else if (node->argument[i] != '\0' && node->argument[i] != c)
		{
			temp[j] = node->argument[i];
			i++;
		}
		j++;
	}
	temp[j] = '\0';
	hub(node, temp);
	free(temp);
}
