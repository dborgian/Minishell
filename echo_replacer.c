/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_replacer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborgian <dborgian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:45:39 by tpiras            #+#    #+#             */
/*   Updated: 2023/11/16 16:13:10 by dborgian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// norma ok
extern int	g_exit_status;

static char	*ft_strongest(t_args *node, int i, int j, int counter)
{
	char	*tmp;

	tmp = ft_calloc((ft_strlen(node->argument) + (2 * counter) + 1),
			sizeof(char));
	while (node->argument[i] != '\0')
	{
		if (node->argument[i] == '$' && check(node->argument) != 0)
		{
			tmp[j++] = 6;
			i++;
			while (node->argument[i] != ' ' && node->argument[i] != '\''
				&& node->argument[i] != '\"' && node->argument[i] != '\0')
				tmp[j++] = node->argument[i++];
			if (node->argument[i] != '\0')
				tmp[j++] = 6;
			if (node->argument[i] == '\0')
			{
				tmp[j] = '\0';
				return (tmp);
			}
		}
		tmp[j++] = node->argument[i++];
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*ft_quite_strong(t_args *node, int *dollars_pos)
{
	int		i;
	int		j;
	char	*tmp;
	int		counter;

	i = 0;
	j = 0;
	counter = ft_contace(node->argument, '$', dollars_pos);
	tmp = ft_strongest(node, i, j, counter);
	return (tmp);
}

bool	checking(int i, int *dollars_pos)
{
	int	j;

	j = 0;
	while (dollars_pos[j] != -1)
	{
		if (dollars_pos[j] == i)
			return (true);
		j++;
	}
	return (false);
}

static int	*brrum(char *str, char c, int *counter)
{
	int	i;
	int	j;
	int	k;

	j = 0;
	k = 1;
	if (str[0] == c)
		k = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			counter[j] = k;
			j++;
			k = k + 2;
		}
		i++;
	}
	return (counter);
}

void	echo_replacer(t_shell *mini, t_args *node)
{
	int		i;
	char	*en;
	char	**matrix;
	char	*str;
	int		dollars_pos[20];

	i = 0;
	while (i < 20)
	{
		dollars_pos[i] = -1;
		i++;
	}
	brrum(node->argument, '$', dollars_pos);
	matrix = NULL;
	en = ft_strdup("");
	if (node->argument != NULL && my_strchr(node->argument, '$') != -1)
	{
		matrix = tyu(node, dollars_pos);
		en = echo_rep_supp(mini, matrix, en, dollars_pos);
		free(matrix);
		free(node->argument);
		node->argument = ft_strdup(en);
	}
	free(en);
}
