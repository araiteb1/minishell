/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:44:28 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/08 21:31:26 by nait-ali         ###   ########.fr       */
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
	// int st;
	if (an.flag_signal)
	{
		printf("\n");
		return ;
	}
	// if(waitpid(-1,&st, WNOHANG) == 0)
	// 	return ;
	// write(2,"\n",2);
	ft_putstr_fd("\n",1);
	rl_replace_line("", 0);
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
	if (cmd->s_substruct && !ft_strcmp("pwd", cmd->s_substruct->data))
		return (ft_pwd(cmd), 1);
	if (cmd->s_substruct && !ft_strcmp("echo", cmd->s_substruct->data))
		return (ft_echo(cmd),1);
	if (cmd->s_substruct && !ft_strcmp("env", cmd->s_substruct->data))
		return (ft_env(cmd), 1);
	if (cmd->s_substruct && !ft_strcmp("exit", cmd->s_substruct->data))
		return (ft_exit(cmd), 1);
	if (cmd->s_substruct && !ft_strcmp("unset", cmd->s_substruct->data))
		return (ft_unset(cmd), 1);
	if (cmd->s_substruct && !ft_strcmp("cd", cmd->s_substruct->data))
		return (ft_cd(cmd), 1);
	if (cmd->s_substruct && !ft_strcmp("export", cmd->s_substruct->data))
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
			if (nb< 999)
            	nb++;
			else if(nb < 0)
				nb = 0;
			else if(nb == 999)
			{
				value="";
				printf("%s---->:\n", value);
				 lstadd_back_environement(&an.environement, creation_node_in_env(ft_strdup(*env),
                                                                       cle, value));
											break;
		
			}
			else 
				nb = 1;
            tmp = ft_itoa(nb);
            free(value);
			if(nb != 999)
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
		an.exit_status = 1;
        exit(1);
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
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(av[1],2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (0);
	}

	an.exit_status = 0;
	init_environement(env);
	getcwd(an.pwd, PATH_MAX);
	rl_catch_signals = 0;
	list = NULL;
	while (1)
	{
		
	an.flag_signal = 0;
	an.flag_herdoc = 0;
		
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, my_handler);
		line = readline("minishell:$ ");
		if (!line)
		{
			write(1,"exit\n", 5);
			// an.exit_status = an.exit_status;
			an.exit_status = 127;
			exit(an.exit_status);
		}
	
		if (line[0] != '\0')
		{
			add_history(line);
		
			if (get_cmds(line, &list) && syntaxe_error(list))
			{
					ft_execution(list, get_env_values(an.environement));
			}
			if (line)
			{
				free (line);
				line = NULL;
			}
			free_list (&list);
		// if(an.flag_herdoc)
		// {

		// 	break ;

		// }
		}

	}
	return (0);
}
