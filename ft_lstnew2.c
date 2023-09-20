/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 03:14:54 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/20 06:47:12 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_qvar(t_qvar **qvr)
{
	*qvr = (t_qvar *)malloc(sizeof(t_qvar));
	if (!*qvr)
		return ;
	(*qvr)->result = NULL;
	(*qvr)->str = NULL;
	(*qvr)->rest = NULL;
}

void	join_result(t_qvar	**qvr)
{
	(*qvr)->tmp = ft_strjoin((*qvr)->str, (*qvr)->rest);
	ft_free_str((*qvr)->str);
	(*qvr)->result = ft_strjoin((*qvr)->result, (*qvr)->tmp);
	free((*qvr)->tmp);
	ft_free_str((*qvr)->rest);
}

char	*get_str1(char *cmd, int *i)
{
	t_qvar	*qvr;
	char	*str;

	init_qvar(&qvr);
	while (cmd[*i] && cmd[*i] != ' ')
	{
		if (cmd[*i] == SQUOTE || cmd[*i] == DQUOTES)
		{
			qvr->type = SQUOTE;
			if (cmd[*i] == DQUOTES)
				qvr->type = DQUOTES;
			(*i)++;
			qvr->str = get_inside_quotes(cmd, i, qvr->type);
			(*i)++;
		}
		if (cmd[*i] && is_alpha(cmd[*i]))
			qvr->rest = get_outside_quotes(cmd, i);
		join_result(&qvr);
	}
	str = qvr->result;
	free (qvr);
	return (str);
}

char	*get_str2(char *cmd, int *i)
{
	char	*str;

	str = NULL;
	str = get_redirection(cmd, &(*i));
	if (ft_strlen(str) > 2 || ft_strlen(str) < 1)
	{
		error_str(str);
		return (NULL);
	}
	return (str);
}
