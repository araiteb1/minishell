/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 02:15:44 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/19 06:01:58 by nait-ali         ###   ########.fr       */
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
	free (tmp);
	i = 0;
	while (str[i] && ft_strcmp(str[i], " "))
	{
		cmd = ft_strtrim(str[i], " \t");
		ft_lstadd_back(list, ft_lstnew(cmd));
		free (cmd);
		i++;
	}
	ft_free(str);
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
			derror += 1;
		else if (line[i] == SQUOTE)
			serror += 1;
		i++;
	}
	if ((serror % 2) || (derror % 2))
	{
		write (2, "Error: unclosed quotes !\n", 25);
		return (1);
	}
	return (0);
}

int	get_cmds(char *line, t_cmd **list)
{
	int		i;

	i = 0;
	if (!check_linesps(line) || non_closed_quotes(line))
		return (free(line), 0);
	if (line[ft_strlen(line) - 1] == '|')
	{
		ft_putstr_fd("minishell: syntax error: unexpected end of file \n", 2);
		free(line);
		return (0);
	}
	while (line[i])
	{
		if (line[i] == '|' && line[i + 1] == '|' && line[i + 2] == '|')
		{
			g_an.exit_status = 258;
			ft_putstr_fd("minishell: syntax error near ", 2);
			ft_putstr_fd(" token `||'\n", 2);
			return (0);
		}
		i++;
	}
	help_get_cmds(line, list);
	free(line);
	return (1);
}
