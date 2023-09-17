/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 02:15:44 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/17 08:00:24 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	help_get_cmds(char *line, t_cmd **list)
{
	char	**str;
	int		i;
	char	*cmd;
	char	*tmp;

	tmp = ft_strtrim(line, " ");

	str = ft_split(line, '|');
	i=0;
	if (!str || ft_strcmp(line, "|") == 0
		|| (tmp[0] == '|' && ft_strlen(line) > 1))
	{
		g_an.exit_status = 258;
		write (2, "minishell: syntax error near unexpected token `|'\n", 51);
		return ;
	}
	free (tmp);
	i = 0;
	while (str[i] && strcmp(str[i], " "))
	{
		cmd = ft_strtrim(str[i], " \t");
		ft_lstadd_back(list, ft_lstnew(cmd));
		free (cmd);
		i++;
	}
	// free(line);
	ft_free(str);
}

int	NonClosedQuotes(char *line)
{
	int	Serror;
	int	Derror;
	int	i;

	Derror = 0;
	Serror = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == DQUOTES )
			Derror += 1;
		else if (line[i] == SQUOTE)
			Serror += 1;
		i++;
	}
	if ((Serror % 2) || (Derror % 2))
	{
		write (2, "Error: unclosed quotes !\n",25);
		return (1);
	}
	return (0);
}

int	get_cmds(char *line, t_cmd **list)
{
	int		i;
	// char 	*str;
	i = 0;
	if (!check_linesps(line) || NonClosedQuotes(line))
		return (0);
	// if (line[ft_strlen(line) - 1] == '|')
	// {
	// 	str = line;
	// 	line = ft_strjoin(str, " newline");
	// 	free(str);
	// }
	while (line[i])
	{
		if (line[i] == '|' && line[i + 1] == '|' && line[i + 2] == '|')
		{
			free(line);
			g_an.exit_status = 258;
			write (2, "minishell: syntax error near unexpected token `||'\n", 51);
			return (0);
		}
		i++;
	}
	help_get_cmds(line, list);
	free(line);
	return (1);
}
