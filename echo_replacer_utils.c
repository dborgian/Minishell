/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_replacer_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborgian <dborgian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:42:25 by dborgian          #+#    #+#             */
/*   Updated: 2023/11/16 16:12:39 by dborgian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_contace(char *str, char c, int *dollar_pos)
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

int	check(char	*s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"')
			return (1);
		if (s[i] == '\'')
			return (0);
		i++;
	}
	return (1);
}

void	argu_export(t_shell *mini, char **envp, t_args *node)
{
	int		i;
	char	**argo;

	i = 0;
	argo = NULL;
	argo = argu(node);
	while (argo[i] != NULL)
	{
		command_export(mini, envp, argo[i]);
		i++;
	}
	free_matrix(argo);
}

void	argu_unset(t_shell *mini, char **envp, t_args *node)
{
	int		j;
	char	**argi;

	j = 0;
	argi = NULL;
	argi = argu(node);
	while (argi[j] != NULL)
	{
		command_unset(mini, argi[j]);
		j++;
	}
	free_matrix(argi);
}

char	*echo_rep_supp(t_shell *mini, char **matrix, char *en, int *dollars_pos)
{
	char	*str;
	int		i;

	i = 0;
	while (matrix[i] != NULL)
	{
		if (checking(i, dollars_pos) == true)
			matrix[i] = echo_expanding_d(mini, matrix[i]);
		if (matrix[i] == NULL && checking(i, dollars_pos) == true)
		{
			free(matrix[i]);
			i++;
			continue ;
		}
		en = ft_strjoin(en, matrix[i], FREE, NO_FREE);
		str = ft_strtrim(en, "\"");
		free(en);
		en = ft_strdup(str);
		free(str);
		free(matrix[i]);
		i++;
	}
	return (en);
}
