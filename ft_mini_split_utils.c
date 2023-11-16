/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_split_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertiz <ertiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:47:30 by tpiras            #+#    #+#             */
/*   Updated: 2023/09/11 16:59:42 by ertiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	ft_mini_counter(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (s[i] != '\0' && s[i] == c)
			count++;
	}
	return (count);
}

int	ft_mini_strcheck(char const *s, char c)
{
	int			i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	mini_g(t_shell *mini, char *s, int i, char c)
{
	int	z;

	z = i + 1;
	while (s[z] != c && s[z])
		z++;
	if (s[z] == c)
	{
		mini->flags.quote_flag = 1;
		return (z);
	}
	else if (mini->flags.quote_flag == 0)
	{
		printf("Error: missing final %c\n", c);
		mini->exit = 1;
	}
	return (0);
}

void	mini_h(t_shell *mini, char *s, int i)
{
	int	z;

	z = i + 1;
	while (s[z] != '\0')
	{
		if (s[z] == ')' && (apices(s, '\"', z) == 1
				&& apices(s, '\'', z) == 1))
		{
			mini->flags.brackets = 1;
		}
		z++;
	}
	if (mini->flags.brackets == 0)
	{
		printf("Error: missing final brackets\n");
		mini->exit = 1;
	}
}

char	*mini_p(t_shell *mini, int i, int j, int z)
{
	char	*str;
	char	*s;
	char	*temp;

	str = NULL;
	s = mini->input;
	if (mini->flags.quote_flag == 1)
		str = ft_substr(s, j, (size_t)(z + 1 - j));
	else
	{
		str = ft_substr(s, j, (size_t)(i - j));
		temp = ft_strtrim(str, "(");
		free(str);
		str = ft_strtrim(temp, ")");
		free(temp);
	}
	mini->flags.quote_flag = 0;
	return (str);
}
