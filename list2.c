/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 02:51:57 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/20 06:15:15 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*subc_quots(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	ret = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!ret)
		return (NULL);
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
		{
			ret[j] = str[i];
			j++;
		}
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

int	ft_lstsize(t_cmd *lst)
{
	int		cont;
	t_cmd	*tmp;

	tmp = lst;
	if (!tmp)
		return (0);
	cont = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		cont++;
	}
	return (cont);
}

t_cmd	*ft_lstlast(t_cmd *lst)
{
	t_cmd	*tmp;

	tmp = lst;
	if (!tmp)
		return (0);
	if (ft_lstsize(tmp) == 1)
		return (tmp);
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		return (tmp);
	}
}

void	ft_lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	last = ft_lstlast(*lst);
	if (*lst)
	{
		last->next = new;
		new->prev = last;
	}
	else
		*lst = new;
	if (new && new->prev)
		new->i = new->prev->i + 1;
}
