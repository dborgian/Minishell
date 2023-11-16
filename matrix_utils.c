/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertiz <ertiz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:48:23 by tpiras            #+#    #+#             */
/*   Updated: 2023/09/11 16:59:42 by ertiz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_size(t_args *node)
{
	int		size;
	char	**arguments;
	int		j;

	size = 0;
	if (node->command != NULL)
		size++;
	if (node->flags != NULL)
		size++;
	if (node->argument != NULL)
	{
		arguments = ft_split(node->argument, ' ');
		j = 0;
		while (arguments[j])
		{
			size++;
			j++;
		}
		free_matrix(arguments);
	}
	return (size);
}

char	**allocate_memory(int size)
{
	char	**temp;

	temp = malloc((size + 1) * sizeof(char *));
	if (temp == NULL)
	{
		perror(".failed to allocate memory");
		return (NULL);
	}
	return (temp);
}

void	copy_arguments(char **temp, char **arguments)
{
	int	j;
	int	index;

	j = 0;
	index = 0;
	while (arguments[j])
	{
		temp[index] = ft_strdup(arguments[j]);
		index++;
		j++;
	}
}

char	**create_matri(t_args *node)
{
	char	**arguments;
	int		size;
	char	**temp;
	int		index;

	index = 0;
	size = count_size(node);
	temp = allocate_memory(size);
	if (temp == NULL)
		return (NULL);
	if (node->command != NULL)
		temp[index++] = ft_strdup(node->command);
	if (node->flags != NULL)
		temp[index++] = ft_strdup(node->flags);
	if (node->argument != NULL)
	{
		arguments = ft_split(node->argument, ' ');
		copy_arguments(temp + index, arguments);
		free_matrix(arguments);
	}
	temp[size] = NULL;
	return (temp);
}
