/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 21:27:51 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/20 01:27:24 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command(char *cmd, int *start)
{
	char	*ret;
	char	*rest;
	char	*tmp;

	rest = NULL;
	ret = NULL;
	tmp = get_command1(cmd, start);
	if (cmd[*start] == DQUOTES || cmd[*start] == SQUOTE)
		rest = get_str1(cmd, start);
	if (rest)
		ret = ft_strjoin(tmp, rest);
	else
		return (tmp);
	ft_free_str(rest);
	ft_free_str(tmp);
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

int	check_rdin_out_err(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '>')
		{
			write(2, "minishell: syntax error \
			near unexpected token `newline'\n", 57);
			return (1);
		}
		i++;
	}
	return (0);
}

int	synt_errord(t_cmd *tmp)
{
	int			flag;
	t_substruct	*tmps;

	tmps = tmp->s_substruct;
	flag = 0;
	while (tmps)
	{
		if (chack_status(tmps, tmp) == 1)
		{
			g_an.exit_status = 258;
			write (2, "minishell: syntax error near ", 30);
			write(2, "unexpected token `newline'\n", 28);
			return (0);
		}
		tmps = tmps->next;
	}
	tmps = tmp->s_substruct;
	while (tmps)
	{
		flag = check_rdin_out_err(tmps->data);
		if (flag == 1)
			return (0);
		tmps = tmps->next;
	}
	return (1);
}

int	syntaxe_error(t_cmd *ls)
{
	t_cmd		*tmp;
	int			flag;

	tmp = ls;
	flag = 0;
	while (tmp)
	{
		if (!ft_strcmp(tmp->data, " "))
		{
			ft_putstr_fd("minishell:  syntax error \
				near unexpected token `|'\n", 2);
			return (0);
		}
		flag = synt_errord(tmp);
		if (flag == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
