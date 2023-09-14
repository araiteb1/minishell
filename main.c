/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:44:28 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/14 06:38:46 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_gvar an;

int 	check_pipesps(char *line)
{
	int i = 0;
	int size=0;

	while(line[i])
	{
		if(line[i] == '|')
		{
			while(line[i] == ' ')
				i++;
			size++;
		}
		i++;
	}
	return(size);
}
int 	check_linesps(char *line)
{
	int i = 0;
	while(line[i])
	{
		if(line[i] != ' ')
			return(1);
		i++;
	}
	return(0);
}
int	get_cmds(char *line, t_cmd **list)
{
	char	**str;
	t_cmd 	*new;
	int		i;

	i = 0;
	if(!check_linesps(line))
		return(0);
	if(check_pipesps(line) > 1)
	{
		write (2, "minishell: syntax error near unexpected token `|'\n", 51);
		return (0);
	}
	if (line[ft_strlen(line) - 1] == '|')
		line = ft_strjoin(line, " newline");
	while (line[i])
	{
		if (line[i] == '|' && line[i + 1] == '|' && line[i + 2] == '|')
		{
			an.exit_status = 258;
			write (2, "minishell: syntax error near unexpected token `|'\n", 51);
			return (0);
		}
		i++;
	}
	str = ft_split(line, '|');
	if (!str || strcmp(line, "|") == 0
		|| (ft_strtrim(line, " ")[0] == '|' && ft_strlen(line) > 1))
	{
		an.exit_status = 258;
		write (2, "minishell: syntax error near unexpected token `|'\n", 51);
		return (0);
	}
	i = 0;
	while (str[i])
	{
		new = ft_lstnew(ft_strtrim(str[i], " \t"));
		ft_lstadd_back(list, new);
		i++;
	}
	return (1);
}

int	check_builtins(t_cmd *cmd, char **option, char **env)
{
	(void)env;
	if (cmd->s_substruct && !ft_strcmp("pwd", cmd->s_substruct->data))
		return (ft_pwd(cmd), 1);
	if (cmd->s_substruct && !ft_strcmp("echo", cmd->s_substruct->data))
		return (ft_echo(cmd, option), 1);
	if (cmd->s_substruct && !ft_strcmp("env", cmd->s_substruct->data))
		return (ft_env(cmd), 1);
	if (cmd->s_substruct && !ft_strcmp("exit", cmd->s_substruct->data))
		return (ft_exit(cmd), 1);
	if (cmd->s_substruct && !ft_strcmp("unset", cmd->s_substruct->data))
		return (ft_unset(cmd), 1);
	if (cmd->s_substruct && !ft_strcmp("cd", cmd->s_substruct->data))
		return (ft_cd(cmd), 1);
	if (cmd->s_substruct && !ft_strcmp("export", cmd->s_substruct->data))
		return (ft_export(cmd), 1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_cmd	*list;

	line = NULL;
	list = NULL;
	if (ac != 1)
	{
		message_error("minishell: ", av[1], ": No such file or directory\n");
		return (0);
	}
	init_environement(env);
	while (1)
	{
		init_signals();
		line = readline("minishell:$ ");
		if (!line)
			(write(1,"exit\n", 5),an.exit_status = 0, exit(an.exit_status));
		if (line[0] != '\0')
		{
			add_history(line);
			if (get_cmds(line, &list) && syntaxe_error(list))
				ft_execution(list, get_env_values(an.environement));
			if (line)
			{
				free (line);
				line = NULL;
			}
			free_list (&list);
		}
	}
	return (0);
}
