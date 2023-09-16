/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 01:04:56 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/16 02:30:36 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_str(char *str)
{
	if (str[0] == '>' && str[1] == '>')
	{
		g_an.exit_status = 258;
		write(2, "minishell: syntax error", 23);
		write(2, "near unexpected token `>>'\n", 27);
	}
	if (str[0] == '<' && str[1] == '<')
	{
		g_an.exit_status = 258;
		write(2, "minishell: syntax error", 23);
		write(2, "near unexpected token `<<'\n", 27);
	}
}

int __isAlpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '-')
		return (1);
	return (0);
}

char *getInsideQuotes(char *cmd, int *i, int type)
{
	char	*str;
	int		size;
	int		start;

	start = *i;
	size = 0;
	while (cmd[*i])
	{
		if (cmd[*i] == type)
			break;
		size++;
		(*i)++;
	}
	if (size == 0)
		return NULL;
	str = ft_substr(cmd, start, size);
	return (str);
}

char *getOutsideQuotes(char *cmd, int *i)
{
	char	*rest;
	int		start;
	int		size;
	
	rest = NULL;
	size = 0;
	start = *i;
	while (cmd[*i] && __isAlpha(cmd[*i]))
	{
		size++;
		(*i)++;
	}
	rest = ft_substr(cmd, start, size);
	return (rest);
}

char	*get_str1(char *cmd, int *i)
{
	char	*result;
	char	*str;
	char	*rest;
	char	*tmp;
	int		type;

	result = NULL;
	str = NULL;
	rest = NULL;
	while (cmd[*i] && cmd[*i] != ' ')
	{
		if (cmd[*i] == SQUOTE || cmd[*i] == DQUOTES)
		{
			type = SQUOTE;
			if (cmd[*i] == DQUOTES)
				type = DQUOTES;
			(*i)++;
			str = getInsideQuotes(cmd, i, type);
			(*i)++;
		}
		if (cmd[*i] && __isAlpha(cmd[*i]))
			rest = getOutsideQuotes(cmd, i);
		tmp = ft_strjoin(str, rest);
		result = ft_strjoin(result, tmp);
		if (rest)
		{
			free (rest);
			rest = NULL;
		}
	}
	return (result);
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

t_cmd	*ft_lstnew(char *cmd)
{
	t_cmd	*l;
	char	*str;
	int		i;

	str = NULL;
	l = malloc(sizeof(t_cmd));
	if (!l)
		return (NULL);
	l->s_substruct = NULL;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			str = get_str1(cmd, &i);
		else if (cmd[i] == '>' || cmd[i] == '<')
			str = get_str2(cmd, &i);
		else
			str = get_command(cmd, &i);
		if (str)
			n_lstadd_back(&(l->s_substruct), n_lstnew(str));
		while (cmd[i] == ' ')
			i++;
	}
	init_list(&l, cmd);
	return (l);
}
