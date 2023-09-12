/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 04:13:02 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/12 11:20:59 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_ev(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 4))
			break ;
		i++;
	}
	return (i);
}

void handel_quit_for_child(int sig)
{
	(void) sig;
	// if(!an.flag_signal)
	// 	return ;
	printf("\\Quit: 3\n");
	//an.exit_status = 131; l9itha flbash

}


void	ft_dup(t_cmd *ls, char **option, char **env)
{

	int flag = 0;
	int i = 0;
	dup2 (ls->filein, 0);
	dup2 (ls->fileout, 1);
	ft_close(ls);
	while(option[i])
	{
		printf("option   ==> %s | fileou %d | filein %d\n", option[i], ls->fileout, ls->filein);
		i++;
	}
	if(option)
	{
		flag = expand_env_variable(option, env);
		if(!flag)
			option_cmd_quots(option);
	}
	ls->filein = 0;
	ls->fileout = 1;
	if (check_builtins(ls, option, env))
		exit(0);
	exec_chile (option, env, ls);
}

char	*ft_get_path(char *cmd, char **env)
{
	int		i;
	char	*path;
	char	*tmp;
	char	**str;

	str = NULL;
	if (cmd[0] != '/')
	{
		path = ft_substr (env[get_ev(env)], 5, ft_strlen(env[get_ev(env)]));
		str = ft_split (path, ':');
		free (path);
		i = 0;
		while (str[i])
		{
			tmp = str[i];
			path = ft_strjoin(tmp, "/");
			free (tmp);
			tmp = path;
			path = ft_strjoin(tmp, cmd);
			free (tmp);
			if (access (path, F_OK) == 0)
				return (path);
			i++;
		}
	}
	return (cmd);
}

void	exec_chile(char **option, char **env, t_cmd *list)
{
	char	*path;
	(void)list;
	// int flag = 0;
	path = ft_get_path(option[0], env);
	if (execve (path, option, env) == -1)
	{
		an.exit_status = 127;
		write(2,"minishell: ,",13);
		ft_putstr_fd(option[0], 2);
		write(2," : command not found \n",23);
		exit (EXIT_FAILURE);
	}
}
int 	check_doll(char *str)
{
	int i = 0;

	while(str[i])
	{
		if(str[i] == '$')
			return(1);
		i++;
	}
	return(0);
}

int     ft_size_nam(char *str, char c)
{
    int i = 0;
    while(str[i] != c)
        i++;
    return(i);
}

char    *ret_expand_val(char *str, char **env)
{
    int i = 0;
    char *value;
    
    value = NULL;
    while(env[i])
    {
         if(ft_strncmp(env[i], str, ft_size_nam(env[i],'=')))
             i++;
         else
             break;
    }
    if(env[i])
        value = ft_substr(env[i], ft_size_nam(env[i], '=') + 1,ft_strlen(env[i]));
    return(value);
}

char    *option_expand(char *line, char **env)
{
    int i;
	int j;
    int size = 0;
	char 	*str = NULL;
    char *ret =  NULL;
	char *ret1= NULL;
	char *value = NULL;
	int start;

	i = 0;
	while(line[i])
	{
    	start = i;
		size = 0;
		while(line[i] && line[i] != '$')
		{
			size++;
			i++;
		}
		ret = ft_substr(line, start, size);
		if(ret && !check_doll(ret))
		{
			j=0;
			if (ret[j] == '\'')
			{
				j++;
				ret1 = get_quotes(ret, &j, SQUOTE);
				j++;
			}
			else if (ret[j] == '"')
			{
				j++;
				ret1 = get_quotes(ret, &j, DQUOTES);
				j++;
			}
			else
				ret1 = ft_strdup(ret);
			value = ret_expand_val(ret1, env);
			if(ret1  && value)
			{
				free(ret1);
				ret1 = ft_strdup(value);
			}
			str = ft_strjoin(str, ret1);
		}
		if (line[i] && line[i] == '$')
			i++;
	}
    return(ft_strtrim(str," "));
}

int expand_env_variable(char **option, char **env)
{
	(void)env;
	char *str=NULL;
	int i;
	int j;

	i = 0;

	while (option && option[i])
	{
		str = ft_strdup(option[i]);
		j = 0;
		if (check_doll(str))
		{
			option[i] = option_expand(str, env);
			return(1);
		}
		i++;
	}
	return(0);
}

void 	option_cmd_quots(char **option)
{
	int i = 0;
	char *str = NULL;
	char *new = NULL;
	if(!option)
		return ;
	while(option[i])
	{
		str = ft_strdup(option[i]);
		new = subc_quots(str);
		option[i] = new;
		i++;
	}
}

void	ft_execution(t_cmd *list, char **env)
{
	t_cmd		*tmp; 
	t_substruct	*tmps;
	char		**option;
	int			**fds;
	pid_t		*pd;
	int			i;
	
	tmp = list;
	i = 0;

	fds = (int **)malloc(sizeof(int *) * ft_lstsize(list));
	pd = (int *)malloc(sizeof(int) * (ft_lstsize(list)));
	ft_creat_pipe(ft_lstsize(list), fds);
	while (tmp && i < ft_lstsize(list))
	{
		option = NULL;
		tmps = tmp->s_substruct;
		while (tmps)
		{
			
			if (tmps->type != word)
				tmps = tmps->next->next;
			if (tmps && tmps->type == word)
			{
				option = __resize(option, tmps->data);
				tmps = tmps->next;
			}
		}
		tmps = tmp->s_substruct;
		while (tmps)
		{
			if (tmps->next && tmps->next->type != word)
				tmps = tmps->next;
			if ((tmps && !tmps->prev) || tmps->type != word)
			{
				if(!get_rd(tmp->prev,&tmps, tmp, fds))
					return ;
			}
			tmps = tmps->next;
		}
		an.flag_signal = 1;
		if (!tmp->prev && !tmp->next && check_builtins(tmp, option, env))
			return ;
		signal(SIGINT,SIG_IGN);
		signal(SIGQUIT,handel_quit_for_child);
		pd[i] = fork();
		if (pd[i] == -1)
		{
			write (2, "error\n", 7);
			an.exit_status = 1;
		}
		if (pd[i] == 0)
		{
			signal(SIGINT,SIG_DFL);
			ft_dup (tmp, option, env);
		}
		if(option)
			ft_free(option);
		ft_close(tmp);
		if (tmp)
			tmp = tmp->next;
		i++;
	}
	i = 0;
	while (i < ft_lstsize(list))
	{
		int status;
		waitpid(pd[i], &status, 0);
		i++;
    }
	// if (WIFEXITED(status))
	// 	an.exit_status = status;
	// else if (WIFSIGNALED(status))
	// 	an.exit_status = 128 + status;
	// printf("%d\n", an.exit_status);
	if(fds)
		ft_free_matrix(fds, ft_lstsize(list) - 1);
}
 // while(wait(&status) =! -1);
