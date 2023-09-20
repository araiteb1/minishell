/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 02:15:44 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/20 07:35:03 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_sps(char **str, t_cmd **list)
{
	int		i;
	char	*cmd;

	i = 0;
	while (str[i] && ft_strcmp(str[i], " "))
	{
		cmd = ft_strtrim(str[i], " \t");
		ft_lstadd_back(list, ft_lstnew(cmd));
		free (cmd);
		i++;
	}
}

void	help_get_cmds(char *line, t_cmd **list)
{
	char	**str;
	int		i;
	char	*tmp;

	tmp = ft_strtrim(line, " ");
	str = ft_split(line, '|');
	i = 0;
	if (!str || ft_strcmp(line, "|") == 0
		|| (tmp[0] == '|' && ft_strlen(line) > 1))
	{
		g_an.exit_status = 258;
		write (2, "minishell: syntax error near unexpected token `|'\n", 51);
		free(str);
		free(tmp);
		return ;
	}
	check_sps(str, list);
	ft_free(str);
	free(line);
}

void	pr_cmpquot(char c, char type, int *cmp1, int *cmp2)
{
	if (c == type && (*cmp1) == 0)
	{
		if ((*cmp2) != 0)
			(*cmp2) -= 1;
		else
			(*cmp2) += 1;
	}
}

int	non_closed_quotes(char *line)
{
	int	serror;
	int	derror;
	int	i;

	derror = 0;
	serror = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == DQUOTES)
			pr_cmpquot(line[i], DQUOTES, &serror, &derror);
		else if (line[i] == SQUOTE)
			pr_cmpquot(line[i], SQUOTE, &derror, &serror);
		i++;
	}
	if ((serror % 2) || (derror % 2))
	{
		write (2, "Error: unclosed quotes !\n", 25);
		return (1);
	}
	return (0);
}

int	line_filpip(char *line)
{
	char	*str;

	if (!check_linesps(line) || non_closed_quotes(line))
		return (0);
	if (line[ft_strlen(line) - 1] == '|')
	{
		str = line;
		line = ft_strjoin(str, " newline");
		ft_putstr_fd("minishell: syntax error: unexpected end of file \n", 2);
		free (str);
		return (0);
	}
	return (1);
}

int	get_cmds(char *line, t_cmd **list)
{
	int		i;

	if (!line_filpip(line))
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] == '|' && line[i + 1] == '|' && line[i + 2] == '|')
		{
			g_an.exit_status = 258;
			ft_putstr_fd("minishell: syntax error \
				near unexpected token `||'\n", 2);
			free(line);
			return (0);
		}
		i++;
	}
	help_get_cmds(line, list);
	return (1);
}
