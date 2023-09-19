/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 21:27:51 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/19 02:15:17 by nait-ali         ###   ########.fr       */
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

char	*get_command(char *cmd, int *start)
{
	char	*ret;
	int		i;
	int		size;
	char	*rest;
	char	*tmp;

	i = *start;
	size = 0;
	rest = NULL;
	ret = NULL;
	while (cmd[*start] && cmd[*start] != ' '
		&& cmd[*start] != '>' && cmd[*start] != '<'
		&& cmd[*start] != DQUOTES && cmd[*start] != SQUOTE)
	{
		size++;
		(*start)++;
	}
	tmp = ft_substr(cmd, i, size);
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

int 	check_rdin_out_err(char *str)
{
		int i = 0;
		while(str[i])
		{
			if(str[i] == '<' && str[i + 1] == '>')
			{
				write(2, "minishell: syntax error near unexpected token `newline'\n",57);
				return(1);
			}
			i++;
		}
		return(0);
}

int	syntaxe_error(t_cmd *ls)
{
	t_cmd		*tmp;
	t_substruct	*tmps;
	int flag = 0;

	tmp = ls;
	while (tmp)
	{
		if (!ft_strcmp(tmp->data, " "))
		{
			ft_putstr_fd("minishell:  syntax error near unexpected token `|'\n", 2);
			return (0);
		}
		tmps = tmp->s_substruct;
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
		tmp = tmp->next;
	}
	return (1);
}
