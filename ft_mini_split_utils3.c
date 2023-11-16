/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_split_utils3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertiz <ertiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:47:42 by tpiras            #+#    #+#             */
/*   Updated: 2023/09/11 16:59:42 by ertiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	operator_checker(const char *s, char control)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == control)
		{
			if (s[i + 1] == control && s[i - 1] != '\\')
			{
				if ((apices(s, '\"', i) == 0)
					|| (apices(s, '\'', i) == 0))
					return (0);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void	ft_mini_cicle(t_shell *mini, char *s, char **str, unsigned int count)
{
	int				i;
	unsigned int	j;
	unsigned int	k;
	int				z;

	i = 0;
	k = -1;
	while (s[i] != '\0')
	{
		while (s[i] == ' ')
			i++;
		j = i;
		while (s[i] != ' ' && s[i] != '\0')
		{
			z = i;
			if (s[i] == '\'' || s[i] == '\"' || s[i] == '(')
				z = mini_g(mini, s, i, s[i]);
			i = z;
			if (mini->exit == 1)
				return ;
			i++;
		}
		str[++k] = mini_p(mini, i, j, z);
	}
	str[++k] = NULL;
}

char	**new_function(char **matrix)
{
	int		i;
	int		k;
	int		z;
	char	**final;

	i = 0;
	k = 0;
	z = 1;
	final = NULL;
	while (matrix[i])
	{
		if (matrix[i][0] == '|' || matrix[i][0] == '<' || matrix[i][0] == '>')
			k++;
		i++;
	}
	if (k == 0)
		return (NULL);
	final = ft_calloc(((2 * k) + 2), sizeof(char *));
	final = new_new_function(matrix, final);
	return (final);
}
