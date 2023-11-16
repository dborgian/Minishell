/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertiz <ertiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:47:47 by tpiras            #+#    #+#             */
/*   Updated: 2023/09/11 16:59:42 by ertiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apices(const char *s, char control, int pos)
{
	int	i;
	int	z;
	int	flag;

	flag = 0;
	z = 0;
	i = 0;
	while (i <= pos)
	{
		if (flag == 0 && s[i] == control)
			flag = 1;
		else if (flag == 1 && s[i] == control)
			flag = 0;
		i++;
	}
	if (flag == 1)
	{
		while (s[i] != '\0')
		{
			if (s[i] == control)
				return (0);
			i++;
		}
	}
	return (1);
}

char	*ft_strjoin_mini(char const *s1, char const *s2, int free1, int free2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	j = 0;
	i = 0;
	s3 = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) + 2 * sizeof(char));
	if (!s3)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		((char *)s3)[i] = s1[i];
		i++;
	}
	s3[i++] = ' ';
	while (s2 && s2[j] != '\0')
		((char *)s3)[i++] = s2[j++];
	((char *)s3)[i] = '\0';
	if (s1 && free1 == FREE)
		free((void *)s1);
	if (s2 && free2 == FREE)
		free((void *)s2);
	return (s3);
}

int	checking_brackets_for_operator(const char *s, int pos)
{
	int	i;
	int	z;
	int	flag;

	flag = 0;
	z = 0;
	i = 0;
	while (i <= pos)
	{
		if (flag == 0 && s[i] == '(')
			flag = 1;
		if (flag == 1 && s[i] == ')')
			flag = 0;
		i++;
	}
	if (flag == 1)
	{
		while (s[i] != '\0')
		{
			if (s[i] == ')')
				return (0);
			i++;
		}
	}
	return (1);
}

static int	new_new_new_function(char **matrix, char **final, int k, int i)
{
	if (matrix[i][0] == '|' || matrix[i][0] == '<' || matrix[i][0] == '>')
	{
		k++;
		final[k++] = ft_strdup(matrix[i]);
	}
	return (k);
}

char	**new_new_function(char **matrix, char **final)
{
	int		i;
	int		k;
	char	*temp;

	i = -1;
	k = 0;
	while (matrix[++i])
	{
		final[k] = ft_calloc(ft_strlen(matrix[i]) + 1, sizeof(char));
		final[k] = ft_memcpy(final[k], ".", 1);
		while (matrix[i] && (matrix[i][0] != '|' || matrix[i][0] != '<'
			|| matrix[i][0] != '>'))
		{
			final[k] = ft_strjoin_mini(final[k], matrix[i], FREE, NO_FREE);
			temp = ft_strtrim(final[k], ". ");
			free(final[k]);
			final[k] = ft_strdup(temp);
			free(temp);
			i++;
		}
		if (matrix[i] == NULL)
			break ;
		k = new_new_new_function(matrix, final, k, i);
	}
	return (final);
}
