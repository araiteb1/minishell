/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 21:27:51 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/14 06:54:30 by araiteb          ###   ########.fr       */
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
char *supp_char(char *str, char c)
{
	char 	*ret;
	int i = 0;
	int j = 0;

	ret = malloc(sizeof(char) * ft_strlen(str));
	while(str[i])
	{
		if(str[i] == c)
			i++;
		ret[j] = str[i];
		j++;
		i++;
	}
	ret[j] = '\0';
	return(ret);
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
	while (cmd[*start])
	{
		if(cmd[*start] == quote && (cmd[*start + 1] == ' ' || cmd[*start + 1] == '\0') )
			break;
		size++;
		(*start)++;
	}
	if (size == 0)
		return (NULL);
	quot = supp_char(ft_substr(cmd, i, size), quote);
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
		tmps = tmp->s_substruct;
		while (tmps)
		{
			if (chack_status(tmps, tmp) == 1)
			{
				an.exit_status = 258;
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
