/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_argu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborgian <dborgian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:50:36 by dborgian          #+#    #+#             */
/*   Updated: 2023/11/16 12:49:30 by dborgian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**new_new_envp(char *s, t_shell *mini)
{
	int		i;
	char	**temp;

	i = 0;
	while (mini->new_envp[i])
		i++;
	temp = malloc((i + 2) * sizeof(char *));
	if (!temp)
		return (NULL);
	i = 0;
	while (mini->new_envp[i])
	{
		temp[i] = ft_strdup(mini->new_envp[i]);
		free(mini->new_envp[i]);
		i++;
	}
	temp[i++] = ft_strdup(s);
	temp[i] = NULL;
	free(mini->new_envp);
	mini->new_envp = temp;
	return (temp);
}

char	**argu(t_args *node)
{
	char	**matrix;
	int		i;
	char	*s;

	i = 0;
	s = ft_quite_strong2(node);
	matrix = ft_split(s, ' ');
	free(s);
	return (matrix);
}

int	ft_contace2(char *str, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			counter++;
		i++;
	}
	return (counter);
}

char	*ft_strongest2(t_args *node, int i, int j, int counter)
{
	char	*tmp;

	tmp = ft_calloc(ft_strlen(node->argument) + (counter + 1), sizeof(char));
	while (node->argument[i] != '\0')
	{
		if (node->argument[i] == '\'' || node->argument[i] == '\"')
			i++;
		tmp[j++] = node->argument[i++];
	}
	tmp[j] = node->argument[i];
	tmp[j++] = '\0';
	return (tmp);
}

char	*ft_quite_strong2(t_args *node)
{
	int		i;
	int		j;
	char	*tmp;
	int		counter;

	i = 0;
	j = 0;
	counter = ft_contace2(node->argument, '=');
	tmp = ft_strongest2(node, i, j, counter);
	return (tmp);
}
