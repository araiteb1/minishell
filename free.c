/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 01:14:42 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/17 03:00:14 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	ft_free_str(char *str)
{
	if(str)
	{
		free(str);
		str = NULL;
	}
}

int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '-')
		return (1);
	return (0);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
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
	while ((*substruct))
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
	while ((*list))
	{
		tmp = (*list)->next;
		free ((*list)->data);
		if((*list)->s_substruct)
			free_sublist(&(*list)->s_substruct);
		free (*list);
		(*list) = tmp;
	}
}

