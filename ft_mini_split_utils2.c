/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_split_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertiz <ertiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:47:36 by tpiras            #+#    #+#             */
/*   Updated: 2023/09/11 16:59:42 by ertiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**mini_choosing_final(t_shell *mini, char **matrix, char *s)
{
	char	**final;

	final = NULL;
	if ((operator_checker(s, '|') != 0) || (operator_checker(s, '&') != 0))
	{
		mini->flags.operators = 1;
		mini->flags.command_separator = 1;
	}
	if (mini->flags.operators == 1)
	{
		final = creting_matrix_to_populate_nodes(matrix);
		free_matrix(matrix);
	}
	else
	{
		final = new_function(matrix);
		if (final == NULL)
		{
			final = ft_calloc(2, sizeof(char *));
			final[0] = ft_strdup(s);
			final[1] = NULL;
		}
		free_matrix(matrix);
	}
	return (final);
}

char	**ft_mini_split(t_shell *mini, char *s, char c)
{
	unsigned int	i;
	char			**matrix;
	char			**final;

	final = NULL;
	if (!s)
		return (NULL);
	i = ft_mini_counter(s, c);
	matrix = ft_calloc(i + 2, sizeof(char *));
	if (!matrix)
		return (NULL);
	if (i == 0)
		matrix[0] = NULL;
	else if (i == 1 && !ft_mini_strcheck(s, c))
	{
		matrix[0] = ft_substr(s, 0, ft_strlen(s));
		matrix[1] = NULL;
	}
	else
		ft_mini_cicle(mini, s, matrix, i);
	if (mini->exit == 1)
		return (final);
	final = mini_choosing_final(mini, matrix, s);
	return (final);
}

char	**creting_matrix_to_populate_nodes(char **matrix)
{
	int		i;
	int		k;
	int		z;
	char	**final;

	i = 0;
	k = 0;
	z = 1;
	while (matrix[i])
	{
		if ((ft_strcmp(matrix[i], "&&") == 0)
			|| (ft_strcmp(matrix[i], "||") == 0))
			k++;
		i++;
	}
	if (k == 0)
		return (matrix);
	final = ft_calloc(((2 * k) + 2), sizeof(char *));
	final = coping_matrix(matrix, final);
	return (final);
}

static char	*putil(char **final, char **matr, int k, int i)
{
	char	*res;

	res = ft_strjoin_mini(final[k], matr[i], FREE, NO_FREE);
	final[k] = ft_strtrim(res, ". ");
	free(res);
	return (final[k]);
}

char	**coping_matrix(char **matr, char **final)
{
	int		i;
	int		k;

	i = -1;
	k = 0;
	while (matr[++i])
	{
		final[k] = ft_calloc(ft_strlen(matr[i]) + 1, sizeof(char));
		final[k] = ft_memcpy(final[k], ".", 1);
		while (matr[i] && ((ft_strcmp(matr[i], "&&") != 0)
				&& (ft_strcmp(matr[i], "||") != 0)))
		{
			final[k] = putil(final, matr, k, i);
			i++;
		}
		if (matr[i] == NULL)
			break ;
		if ((ft_strcmp(matr[i], "&&") == 0) || (ft_strcmp(matr[i], "||") == 0))
		{
			k++;
			final[k++] = ft_strdup(matr[i]);
		}
	}
	return (final);
}
