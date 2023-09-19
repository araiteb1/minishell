/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 21:35:57 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/19 01:24:31 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_type(char *s)
{
	if (!ft_strcmp(s, "|"))
		return (pip);
	else if (!ft_strcmp(s, "<"))
		return (rd_input);
	else if (!ft_strcmp(s, ">"))
		return (rd_output);
	else if (!ft_strcmp(s, ">>"))
		return (rd_output_append);
	else if (!ft_strcmp(s, "<<"))
		return (heredoc);
	else
		return (word);
}

t_substruct	*n_lstnew(char *cmd)
{
	t_substruct	*l;

	l = malloc(sizeof(t_substruct));
	if (!l)
		return (NULL);
	l->data = ft_strdup(cmd);
	l->type = get_type(l->data);
	l->next = NULL;
	l->prev = NULL;
	return (l);
}

int	n_lstsize(t_substruct *lst)
{
	int			cont;
	t_substruct	*tmp;

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

t_substruct	*n_lstlast(t_substruct *lst)
{
	t_substruct	*tmp ;

	tmp = lst;
	if (!tmp)
		return (0);
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		return (tmp);
	}
}

void	n_lstadd_back(t_substruct **lst, t_substruct *new)
{
	t_substruct	*last;

	if (!*lst)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new;
		new->prev = last;
	}
}
