/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertiz <ertiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:49:59 by tpiras            #+#    #+#             */
/*   Updated: 2023/09/11 16:59:42 by ertiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	first(t_varie *var, char *str, int len)
{
	while (++var->i < len)
	{
		if (str[var->i] == '\'')
		{
			var->withinquotes = !var->withinquotes;
			if (var->withinquotes)
				var->quotesstack++;
			else
				var->quotesstack--;
		}
		else if (str[var->i] == '\"')
		{
			var->withindoublequotes = !var->withindoublequotes;
			if (var->withindoublequotes)
				var->doublequotesstack++;
			else
				var->doublequotesstack--;
		}
		else if (!var->withinquotes && !var->withindoublequotes
			&& is_delimiter(str[var->i], str, var->i))
			var->newlen++;
	}
}

static void	second(t_varie *var)
{
	if (var->quotesstack != 0)
		var->newlen -= var->quotesstack;
	else
		var->newlen = var->newlen;
	if (var->doublequotesstack != 0)
		var->newlen -= var->doublequotesstack;
	else
		var->newlen = var->newlen;
	var->newstr = ft_calloc(var->newlen +2, sizeof(char));
	var->j = 0;
	var->withinquotes = 0;
	var->withindoublequotes = 0;
	var->i = -1;
}

static void	third(t_varie *var, char *str)
{
	if (var->newstr[var->j] != '|')
		var->newstr[var->j++] = ' ';
	var->newstr[var->j++] = str[var->i];
	if (str[var->i] == '|')
	{
		if (var->newstr[var->j + 1] == '|' && var->newstr[var->j - 1] != '|')
		{
			var->newstr[++var->j] = '|';
			var->j++;
		}
	}
}

static void	forth(t_varie *var, char *str)
{
	if (str[var->i] == '&')
	{
		var->newstr[var->j++] = '&';
		var->i++;
	}
	if (str[var->i] == '|')
	{
		var->newstr[var->j] = '|';
		if (var->newstr[var->j + 1] == '|')
		{
			var->newstr[++var->j] = '|';
			var->j++;
		}
	}
	var->newstr[var->j++] = str[var->i];
}

char	*insert_spaces(char *str, int len)
{
	t_varie	*var;
	char	*res;

	var = ft_calloc(1, sizeof(t_varie));
	init_varie(var, len);
	first(var, str, len);
	second(var);
	while (++var->i < len)
	{
		if (str[var->i] == '\'')
			var->withinquotes = !var->withinquotes;
		else if (str[var->i] == '\"')
			var->withindoublequotes = !var->withindoublequotes;
		if (!var->withinquotes && !var->withindoublequotes
			&& is_delimiter(str[var->i], str, var->i))
			third(var, str);
		else
			forth(var, str);
	}
	var->newstr[var->j] = '\0';
	res = ft_strdup(var->newstr);
	free(str);
	free(var->newstr);
	free(var);
	return (res);
}
