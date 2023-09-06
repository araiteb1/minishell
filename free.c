/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 01:14:42 by araiteb           #+#    #+#             */
/*   Updated: 2023/08/06 04:53:41 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free (str);
	str = NULL;
}

void	free_sublist(t_substruct **substruct)
{
	t_substruct	*tmp;

	tmp = (*substruct);
	while (tmp)
	{
		tmp = (*substruct)->next;
		free ((*substruct)->data);
		free ((*substruct));
		(*substruct) = tmp;
	}
}

void	free_list(t_cmd **list)
{
	t_cmd	*tmp;

	tmp = (*list);
	while (tmp)
	{
		tmp = (*list)->next;
		free ((*list)->data);
		free_sublist(&(*list)->s_substruct);
		free (*list);
		(*list) = tmp;
	}
}
