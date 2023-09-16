/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 02:15:44 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/16 04:21:25 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char    *lineQuo(char *line)
// {
//     int i;
//     int size;
//     int start;
//     char *resul;

    
    
// }

void	help_get_cmds(char *line, t_cmd **list)
{
	char	**str;
    // char *str1;
	int		i;
	t_cmd	*new;
	char	*cmd;

	str = ft_split(line, '|');
	i = 0;
	if (!str || strcmp(line, "|") == 0
		|| (ft_strtrim(line, " ")[0] == '|' && ft_strlen(line) > 1))
	{
		g_an.exit_status = 258;
		write (2, "minishell: syntax error near unexpected token `|'\n", 51);
		return ;
	}
	i = 0;
	while (str[i])
	{
		cmd = ft_strtrim(str[i], " \t");
		new = ft_lstnew(cmd);
		ft_lstadd_back(list, new);
		free (cmd);
		i++;
	}
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

	i = 0;
	if (!check_linesps(line) || NonClosedQuotes(line) )
		return (0);
	if (line[ft_strlen(line) - 1] == '|')
		line = ft_strjoin(line, " newline");
	while (line[i])
	{
		if (line[i] == '|' && line[i + 1] == '|' && line[i + 2] == '|')
		{
			g_an.exit_status = 258;
			write (2, "minishell: syntax error near unexpected token `||'\n", 51);
			return (0);
		}
		i++;
	}
	help_get_cmds(line, list);
	return (1);
}
