/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:44:28 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/07 01:28:12 by araiteb          ###   ########.fr       */
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

int	get_cmds(char *line, t_cmd **list, char **env)
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
		new = ft_lstnew(ft_strtrim(str[i], " \t"), env);
		if(!new)
			return(0);
		ft_lstadd_back(list, new);
		i++;
	}
	return (1);
}

void	my_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	ft_putstr_fd("\n",1);
	rl_on_new_line();
	rl_redisplay();
	an.exit_status = 1;
}


static long	combien_de_cararctere(long i)
{
	long	count;

	count = 0;
	if (i <= 0)
	{
		count ++;
		i = -1 * i;
	}
	while (i > 0)
	{
		count ++;
		i /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	nombre;
	char	*p;
	long	len;

	nombre = n;
	len = combien_de_cararctere(nombre);
	p = (char *)malloc(len + 1);
	if (!p)
		return (0);
	p[len--] = '\0';
	if (nombre < 0)
	{
		nombre *= -1;
		p[0] = '-';
	}
	if (nombre == 0)
		p[0] = 48;
	while (nombre)
	{
		p[len--] = nombre % 10 + '0';
		nombre /= 10;
	}
	return (p);
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

void init_environement(char **env)
{
    int i;
    char *cle;
    char *value;
    int nb;

    char *tmp;

    i = 0;
    an.environement = NULL;
    tmp = NULL;
    while (*env)
    {
        i = find_equal(*env, '=');
        cle = ft_substr(*env, 0, i);
        value = ft_substr(*env, i + 1, ft_strlen(*env) - i);
        if (!ft_strcmp("SHLVL", cle))
        {
            nb = ft_atoi(value);
            // free(value);
            nb++;
            
            tmp = ft_itoa(nb);
            free(value);
            value = ft_strdup(tmp);
        }
        lstadd_back_environement(&an.environement, creation_node_in_env(ft_strdup(*env),
                                                                       cle, value));
        env++;
    }

}


char **get_env_values(t_environement *env_list)
{
    int count = 0;
    t_environement *current = env_list;
	char *tmp;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    char **env_values = (char **)malloc((count + 1) * sizeof(char *));
    if (env_values == NULL)
    {
        perror("Erreur lors de l'allocation de mémoire");
        exit(EXIT_FAILURE);
    }
    current = env_list;
    int i = 0;
    while (current != NULL)
    {
        tmp = ft_strjoin(current->cle, "=");
		env_values[i] = ft_strjoin(tmp,current->valeur);
        i++;
        current = current->next;
    }
    env_values[i] = NULL;

    return env_values;
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
	getcwd(an.pwd, PATH_MAX);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, my_handler);
	while (1)

	{
		rl_catch_signals = 0;
		
		line = readline("minishell:$ ");
		if (!line)
		{
			write(1,"exit\n", 5);
			break;
		}
		if (line[0] != '\0')
		{
			add_history(line);
			if (get_cmds(line, &list, env) && syntaxe_error(list))
			{
				ft_execution(list, get_env_values(an.environement));
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
