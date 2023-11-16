/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertiz <ertiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:49:00 by tpiras            #+#    #+#             */
/*   Updated: 2023/09/11 16:59:42 by ertiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

static void	checking_args(t_args *cur)
{
	int	i;

	i = 0;
	while (cur->argument)
	{
		if (cur->argument[i] == '\0')
		{
			free(cur->argument);
			cur->argument = NULL;
		}
		else if (cur->argument[i] != ' ')
			break ;
		i++;
	}
}

static void	no_infile_or_outfile(t_args *cur, t_args *red, int k)
{
	char	*res;

	res = NULL;
	free(cur->argument);
	if (cur->infile != NULL && ft_strchr(cur->str, '<') != -1)
	{
		cur->argument = ft_strdup(cur->infile);
		if (cur->str[ft_strchr(cur->str, '<') + 1] == '<')
			cur->argument = NULL;
	}
	else if (cur->outfile != NULL && ft_strchr(cur->str, '>') != -1)
	{
		res = ft_substr(cur->str, ft_strlen(cur->command)
				+ 1, ft_strchr(cur->str, '>') - ft_strlen(cur->command) - 1);
		cur->argument = ft_strtrim(res, " ");
	}
	else
	{
		res = ft_substr(cur->str, ft_strlen(cur->command)
				+ k + 1, ft_strchr(cur->str, red->str[0]) - k
				- ft_strlen(cur->command) - 1);
		cur->argument = ft_strtrim(res, " ");
	}
	if (res != NULL)
		free(res);
}

static void	infile_or_outfile(t_args *cur)
{
	if (ft_strchr(cur->str, '|') < ft_strchr(cur->str, '>'))
	{
		free(cur->outfile);
		cur->outfile = NULL;
		cur->redirection_quantity = 0;
	}
	if (ft_strchr(cur->str, '|') < ft_strchr(cur->str, '<'))
	{
		free(cur->infile);
		cur->infile = NULL;
		cur->redirection_quantity = 0;
	}
	if (cur->infile != NULL && cur->outfile != NULL)
	{
		if (ft_strchr(cur->str, '<') < ft_strchr(cur->str, '>'))
		{
			free(cur->outfile);
			cur->outfile = NULL;
		}
		else
		{
			free(cur->infile);
			cur->infile = NULL;
		}
	}
}

void	redirecting_nodes(t_shell *mini, t_args *new, t_args *red)
{
	int		k;
	char	*temp;

	k = 0;
	if ((*mini->high)->flags != NULL)
		k = ft_strlen((*mini->high)->flags);
	init_node(red);
	init_node(new);
	temp = ft_strtrim((*mini->high)->str, " ");
	free((*mini->high)->str);
	(*mini->high)->str = ft_strdup(temp);
	free(temp);
	red->str = ft_strdup((*mini->high)->redirect);
	red->redirect = ft_strdup(red->str);
	new->str = ft_substr((*mini->high)->str,
			ft_strchr((*mini->high)->str, red->str[0])
			+ 1, ft_strlen((*mini->high)->str)
			- ft_strchr((*mini->high)->str, red->str[0]));
	infile_or_outfile((*mini->high));
	no_infile_or_outfile((*mini->high), red, k);
	checking_args((*mini->high));
	free((*mini->high)->redirect);
	(*mini->high)->redirect = NULL;
	(*mini->high) = new;
}
