/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dborgian <dborgian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:48:02 by tpiras            #+#    #+#             */
/*   Updated: 2023/11/16 12:48:25 by dborgian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test(t_shell *mini, t_args *new_node)
{
	t_args	*last;

	last = *mini->list;
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	new_node->previous = last;
	new_node->next = NULL;
	*mini->high = new_node;
}

static void	freaks(t_args *current)
{
	if (current->redirect != NULL)
		free(current->redirect);
	if (current->infile != NULL)
		free(current->infile);
	if (current->outfile != NULL)
		free(current->outfile);
}

void	clear_list(t_shell *mini)
{
	t_args	*current;
	t_args	*next;

	current = *mini->list;
	while (current != NULL)
	{
		next = current->next;
		if (current->str != NULL)
			free(current->str);
		if (current->command != NULL)
			free(current->command);
		if (current->flags != NULL)
			free(current->flags);
		if (current->argument != NULL)
			free(current->argument);
		freaks(current);
		free(current);
		current = next;
	}
	free(mini->list);
	free(mini->high);
}

void	init_node(t_args *node)
{
	node->command = NULL;
	node->flags = NULL;
	node->argument = NULL;
	node->redirect = NULL;
	node->str = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	node->redirection_quantity = 0;
}

void	clear_mini(t_shell *mini, int flag)
{
	clear_list(mini);
	free(mini->input);
	if (flag == 1)
	{
		free(mini->main_path);
		free_matrix(mini->envp);
		if (mini->new_envp != NULL)
			free_matrix(mini->new_envp);
		free(mini);
	}
}
