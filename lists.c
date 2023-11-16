/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertiz <ertiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:48:06 by tpiras            #+#    #+#             */
/*   Updated: 2023/09/11 16:59:42 by ertiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_args	*create_node(t_shell *mini, char *data)
{
	t_args	*new_node;

	new_node = ft_calloc(1, sizeof(t_args));
	if (new_node == NULL)
	{
		free(new_node);
		return (NULL);
	}
	init_node(new_node);
	new_node->str = ft_strdup(data);
	if (new_node->str == NULL)
	{
		free(new_node);
		return (NULL);
	}
	if ((*mini->list) == NULL)
	{
		(*mini->list) = new_node;
		(*mini->high) = new_node;
	}
	new_node->next = NULL;
	return (new_node);
}

void	insert_last_with_delimiter(t_shell *mini, char delim)
{
	int		i;
	char	**tokens;
	t_args	*new_node;

	tokens = ft_mini_split(mini, mini->input, delim);
	if (tokens == NULL)
		return ;
	i = -1;
	while (tokens[++i] != NULL)
	{
		new_node = create_node(mini, tokens[i]);
		if (new_node == NULL)
			return ;
		if (*mini->list != new_node)
			test(mini, new_node);
		analizer(mini, mini->envp);
		if (mini->exit == 1)
		{
			free_matrix(tokens);
			return ;
		}
	}
	free_matrix(tokens);
	ultimating_commands(mini);
}

void	print_list(t_args **head)
{
	t_args	*current;

	if (head == NULL)
		printf("La lista è vuota.\n");
	else
	{
		current = *head;
		while (current != NULL)
		{
			printf("node numb = %d\n", current->order);
			printf("str = %s\n", current->str);
			printf("com = %s\n", current->command);
			printf("flags = %s\n", current->flags);
			printf("arg = %s\n", current->argument);
			printf("redi = %s\n", current->redirect);
			printf("infi = %s\n", current->infile);
			printf("out = %s\n", current->outfile);
			printf("qnt = %d\n", current->redirection_quantity);
			current = current->next;
		}
		printf("NULL\n");
	}
}
