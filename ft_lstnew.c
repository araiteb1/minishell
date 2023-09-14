/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 01:04:56 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/14 01:05:43 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_str(char *str)
{
	if (str[0] == '>' && str[1] == '>')
	{
		an.exit_status = 258;
		write(2, "minishell: syntax error", 23);
		write(2, "near unexpected token `>>'\n", 27);
	}
	if (str[0] == '<' && str[1] == '<')
	{
		an.exit_status = 258;
		write(2, "minishell: syntax error", 23);
		write(2, "near unexpected token `<<'\n", 27);
	}
}

char	*get_str1(char *cmd, int *i)
{
	char	*str;

	str = NULL;
	if (cmd[*i] == '\'')
	{
		(*i)++;
		str = get_quotes(cmd, &(*i), SQUOTE);
		if (!str)
			str = ft_strdup(" ");
		(*i)++;
	}
	else if (cmd[*i] == '"')
	{
		(*i)++;
		str = get_quotes(cmd, &(*i), DQUOTES);
		if (!str)
			str = ft_strdup(" ");
		(*i)++;
	}
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

void	init_list(t_cmd **l, char *cmd)
{
	(*l)->data = cmd;
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
