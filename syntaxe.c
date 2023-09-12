/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 21:27:51 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/12 12:08:32 by araiteb          ###   ########.fr       */
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

char	*get_quotes(char *cmd, int *start, int type)
{
	char	*quot;
	int		size;
	int		i;
	char	quote;

	if (type == DQUOTES)
		quote = '"';
	else
		quote = '\'';
	i = *start;
	size = 0;
	if (cmd[(*start) + 1] && cmd[(*start) + 1] == type)
		return (NULL);
	while (cmd[*start] && cmd[*start] != quote)
	{
		size++;
		(*start)++;
	}
	if (size == 0)
		return (NULL);
	quot = ft_substr(cmd, i, size);
	return (quot);
}

char	*get_command(char *cmd, int *start)
{
	char	*ret;
	int		i;
	int		size;

	i = *start;
	size = 0;
	while (cmd[*start] && cmd[*start] != ' '
		&& cmd[*start] != '>' && cmd[*start] != '<')
	{
		size++;
		(*start)++;
	}
	ret = ft_substr(cmd, i, size);
	return (ret);
}

int	chack_status(t_substruct *tmps, t_cmd *tmp)
{
	if ((tmps
			&& (tmps->type == rd_input || tmps->type == rd_output
				|| tmps->type == rd_output_append
				|| tmps->type == heredoc)
			&& (!tmps->next
				|| (tmps->next && tmps->next->type != word)))
		|| (tmps->type == word
			&& (tmp->next && tmp->next->s_substruct
				&& tmp->next->s_substruct->type == newline)))
		return (1);
	else
		return (0);
}

int	syntaxe_error(t_cmd *ls)
{
	t_cmd		*tmp;
	t_substruct	*tmps;

	tmp = ls;
	while (tmp)
	{
		tmps = tmp->s_substruct;
		while (tmps)
		{
			if (chack_status(tmps, tmp) == 1)
			{
				an.exit_status = 258;
				write (2, "minishell: syntax error near", 29);
				write(2, "unexpected token `newline'\n", 28);
				return (0);
			}
			tmps = tmps->next;
		}
		tmp = tmp->next;
	}
	return (1);
}
