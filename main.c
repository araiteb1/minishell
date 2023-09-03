/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:44:28 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/03 22:27:02 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_gvar an;

void    print_cmds(t_cmd *ls)
{
    t_cmd *tmp;
    t_substruct *tmps;

    printf("\n---{ Commands }---\n");
    tmp = ls;
    while(tmp)
    {
        printf("line : %s \n",tmp->data);
        tmps = tmp->s_substruct;
        while (tmps)
        {
            printf("|-->cmd :: %s\n", tmps->data);
            printf("|-type :: %d\n", tmps->type);
            tmps = tmps->next;
        }  
        tmp = tmp->next;      
    }
}

int	get_cmds(char *line, t_cmd **list)
{
	char	**str;
	t_cmd 	*new;
	int		i;

	i = 0;
	if (line[ft_strlen(line) - 1] == '|')
		line = ft_strjoin(line, " newline");
	while(line[i])
	{
		if(line[i] == '|' && line[i + 1] == '|' && line[i + 2] == '|')
		{
			an.exit_status = 255;
			write (2, "minishell: syntax error near unexpected token `|'\n", 51);
			return (0);
		}
		i++;
	}
	str = ft_split(line, '|');
	if (!str || strcmp(line, "|") == 0
		|| (ft_strtrim(line, " ")[0] == '|' && ft_strlen(line) > 1))
	{
		an.exit_status = 255;
		write (2, "minishell: syntax error near unexpected token `|'\n", 51);
		return (0);
	}
	i = 0;
	while (str[i])
	{
		new = ft_lstnew(ft_strtrim(str[i], " \t"));
		if(!new)
			return(0);
		ft_lstadd_back(list, new);
		i++;
	}
	return (1);
}

void	my_handler(int signal)
{
	(void) signal;
	ft_putstr_fd("\n",1);
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
}

void init_environement(char **env)
{
	int	i;
	char *cle;
	char *value;

	i = 0;
	an.environement = NULL;
	while (*env)
	{
		i = find_equal(*env, '=');
		cle = ft_substr(*env, 0, i);
		value = ft_substr(*env, i + 1, ft_strlen(*env) - i);
		lstadd_back_environement(&an.environement, creation_node_in_env(ft_strdup(*env),
				cle, value));
		if (an.exit_status)
			return (free_environement());
		env++;
	}
}

int check_builtins(t_cmd *cmd)
{
	if (!ft_strcmp("pwd", cmd->s_substruct->data))
		return (ft_pwd(), 1);
	if (!ft_strcmp("echo", cmd->s_substruct->data))
		return (ft_echo(cmd),1);
	if (!ft_strcmp("env", cmd->s_substruct->data))
		return (ft_env(cmd), 1);
	if (!ft_strcmp("exit", cmd->s_substruct->data))
		return (ft_exit(cmd), 1);
	if (!ft_strcmp("unset", cmd->s_substruct->data))
		return (ft_unset(cmd), 1);
	if (!ft_strcmp("cd", cmd->s_substruct->data))
		return (ft_cd(cmd), 1);
	if (!ft_strcmp("export", cmd->s_substruct->data))
		return (ft_export(cmd),1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_cmd	*list;

	line = NULL;
	list = NULL;
	(void)av;

	if (ac != 1)
	{
		ft_putstr_fd("too many arguments\n", 2);
		ft_putstr_fd("./minishell without arguments\n", 2);
		return (0);
	}

	list = NULL;
	an.exit_status = 0;
	init_environement(env);
	while (1)
	{
		
		line = readline("minishell:$ ");
		if (!line)
		{
			write(1,"exit\n", 5);
			break;
		}
		if (line[0] != '\0')
		{
			add_history(line);
			if (get_cmds(line, &list) && syntaxe_error(list))
			{
					ft_execution(list, env);
			}
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
