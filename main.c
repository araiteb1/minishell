/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:44:28 by araiteb           #+#    #+#             */
/*   Updated: 2023/08/22 22:59:30 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			write (2, "minishell: syntax error near unexpected token `|'\n", 51);
			return (0);
		}
		i++;
	}
	str = ft_split(line, '|');
	if (!str || strcmp(line, "|") == 0
		|| (ft_strtrim(line, " ")[0] == '|' && ft_strlen(line) > 1))
	{
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

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_cmd	*list;

	line = NULL;
	list = NULL;
	(void)ac;
	(void)av;

	list = NULL;
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
