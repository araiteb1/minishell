/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 01:04:56 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/19 02:28:15 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_inside_quotes(char *cmd, int *i, int type)
{
	char	*str;
	int		size;
	int		start;

	start = *i;
	size = 0;
	while (cmd[*i])
	{
		if (cmd[*i] == type)
			break ;
		size++;
		(*i)++;
	}
	if (size == 0)
		return (NULL);
	str = ft_substr(cmd, start, size);
	return (str);
}

char	*get_outside_quotes(char *cmd, int *i)
{
	char	*rest;
	int		start;
	int		size;

	rest = NULL;
	size = 0;
	start = *i;
	while (cmd[*i] && is_alpha(cmd[*i]))
	{
		size++;
		(*i)++;
	}
	rest = ft_substr(cmd, start, size);
	return (rest);
}

void	init_qvar(t_qvar *qvr)
{
	qvr->result = NULL;
	qvr->str = NULL;
	qvr->rest = NULL;
}

char	*get_str1(char *cmd, int *i)
{
	t_qvar	*qvr;

	qvr = (t_qvar *)malloc(sizeof(t_qvar));
	init_qvar(qvr);
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
		qvr->tmp = ft_strjoin(qvr->str, qvr->rest);
		ft_free_str(qvr->str);
		qvr->result = ft_strjoin(qvr->result, qvr->tmp);
		free(qvr->tmp);
		ft_free_str(qvr->rest);
	}
	return (qvr->result);
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

void	init_list(t_cmd **l, char *cmd)
{
	(*l)->data = ft_strdup(cmd);
	(*l)->fileout = 1;
	(*l)->filein = 0;
	(*l)->next = NULL;
	(*l)->prev = NULL;
	(*l)->i = 0;
}

char	*separt_cond(char *cmd, int *i)
{
	char	*str;

	if (cmd[*i] == '\'' || cmd[*i] == '"')
	{
		str = get_str1(cmd, i);
			
	}
	else if (cmd[*i] == '>' || cmd[*i] == '<')
		str = get_str2(cmd, i);
	else
		str = get_command(cmd, i);
	return (str);
}

t_cmd	*ft_lstnew(char *cmd)
{
	t_cmd		*l;
	t_substruct	*new;
	char		*str;
	int			i;

	str = NULL;
	l = malloc(sizeof(t_cmd));
	if (!l)
		return (NULL);
	l->s_substruct = NULL;
	i = 0;
	while (cmd[i])
	{
		str = separt_cond(cmd, &i);
		if (str)
		{
			new = n_lstnew(str);
			n_lstadd_back(&(l->s_substruct), new);
		}
		while (cmd[i] == ' ')
			i++;
		ft_free_str(str);
	}
	init_list(&l, cmd);
	return (l);
}
