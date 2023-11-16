/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertiz <ertiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:47:17 by tpiras            #+#    #+#             */
/*   Updated: 2023/09/11 16:59:42 by ertiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	ft_echo_counter(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static void	ft_echo_cicle(t_shell *mini, char const *s,
	char **str, unsigned int count)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	int				z;

	i = 0;
	k = 0;
	z = 0;
	while (s[i] != '\0')
	{
		while (s[i] == ' ')
			i++;
		j = i;
		while (s[i] != ' ' && s[i] != '\0')
		{
			z = i;
			if (s[i] == '\'' || s[i] == '\"')
				z = check_quotes(mini, s, i, s[i]);
			i = z;
			i++;
		}
		str[k++] = ft_substr(s, j, (size_t)(i - j));
	}
	str[k] = NULL;
}

char	**ft_echo_split(t_shell *mini, char const *s, char c)
{
	unsigned int	i;
	char			**matrix;

	if (!s)
		return (NULL);
	i = ft_echo_counter(s, c);
	matrix = (char **)malloc((i + 1) * sizeof (char *));
	if (!matrix)
		return (NULL);
	if (i == 0)
		matrix[0] = NULL;
	else if (i == 1 && !ft_echo_strcheck(s, c))
	{
		matrix[0] = ft_substr(s, 0, ft_strlen(s));
		matrix[1] = NULL;
	}
	else
		ft_echo_cicle(mini, s, matrix, i);
	return (matrix);
}
