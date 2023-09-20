/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 03:52:08 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/19 03:53:47 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_redirection(char *cmd, int *start)
{
	char	*ret;
	int		size;
	int		i;

	i = (*start);
	size = 0;
	while (cmd[*start] && (cmd[*start] == '>' || cmd[*start] == '<'))
	{
		size++;
		(*start)++;
	}
	ret = ft_substr(cmd, i, size);
	return (ret);
}

int	ft_isalpha(int c)
{
	if (!(c >= 97 && c <= 122) && !(c >= 65 && c <= 90))
		return (0);
	return (1);
}

char	*get_command1(char *cmd, int *start)
{
	char	*tmp;
	int		size;
	int		i;

	tmp = NULL;
	size = 0;
	i = *start;
	while (cmd[*start] && cmd[*start] != ' '
		&& cmd[*start] != '>' && cmd[*start] != '<'
		&& cmd[*start] != DQUOTES && cmd[*start] != SQUOTE)
	{
		size++;
		(*start)++;
	}
	tmp = ft_substr(cmd, i, size);
	return (tmp);
}
