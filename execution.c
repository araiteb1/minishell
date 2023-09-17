/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 04:13:02 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/17 08:22:34 by araiteb          ###   ########.fr       */
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

void	ft_dup(t_cmd *ls, char **option, char **env, int **fds)
{
	(void)fds;
	ft_close(ls);
	if(option)
		expand_env_variable(option, env);
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
	if (cmd && cmd[0] != '/')
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
	char *str;
	(void)list;
	if(!ft_strcmp(option[0], " "))
	{
		free_list(&list);
		ft_free(option);
		exit(0);
	}
	path = ft_get_path(option[0], env);
	if (execve (path, option, env) == -1)
	{
		if(option && option[0] && option[0][0] == '.' && option[0][1] == '/')
		{
			str = strerror(errno);
			if(!ft_strcmp(str, "Exec format error"))
			{
				ft_putstr_fd("minishell: ",2);
				ft_putstr_fd(option[0],2);
				ft_putstr_fd(": Permission denied\n",2);
			}
			else
			{
				ft_putstr_fd("minishell: ",2);
				ft_putstr_fd(option[0],2);
				ft_putstr_fd(": is a directory\n",2);
			}
			g_an.exit_status = 126;
		}
		else{
			g_an.exit_status = 127;
			write(2,"minishell: ",11);
			ft_putstr_fd(option[0], 2);
			write(2," : command not found \n",23);
		}
		exit (g_an.exit_status);
	}
}
int 	check_doll(char *str, char c)
{
	int i = 0;

	while(str[i])
	{
		if(str[i] == c)
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
         if(ft_strncmp(env[i], str, ft_strlen(str)))
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
    int 	i;
    int 	size = 0;
	char 	*str = NULL;
    char	*ret =  NULL;
	char	*ret1= NULL;
	char	*value = NULL;
	int 	start;
	char	*tmp = NULL;

	i = 0;
	while(line && line[i])
	{
    	start = i;
		size = 0;
		while(line[i] && line[i] != '$')
		{
			size++;
			i++;
		}
		i++;
		if (size > 0)
			ret = ft_substr(line, start, size);
		size = 0;
		start = i;
		while(line[i] && line[i] != '$')
		{
			size++;
			i++;
		}
		ret1 = ft_substr(line, start, size);
		if(!ft_strncmp(ret1, "?",ft_strlen(ret1)))
		{
			ft_free_str(ret1);
			str = ft_itoa(g_an.exit_status);
			return (str);
		}
		if(ret1 && !check_doll(ret1, '$'))
		{
			value = ret_expand_val(ret1, env);
			tmp = str;
			str = ft_strjoin(ret, value);
			free (value);
			value = str;
			str = ft_strjoin(tmp, str);
			free (value);
		}
		ft_free_str(tmp);
		// ft_free_str(value);
		ft_free_str(ret1);
		ft_free_str(ret);
	}
	tmp = ft_strtrim(str," ");
	free (str);
    return(tmp);
}

void expand_env_variable(char **option, char **env)
{
	char *str=NULL;
	int i;
	int j;

	i = 0;

	while (option && option[i])
	{
		str = ft_strdup(option[i]);
		j = 0;
		if (check_doll(str, '$') == 1)
		{
			free(option[i]);
			option[i] = option_expand(str, env);
		}
		ft_free_str(str);
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
			if ((tmps->type != word) && (tmps->type != pip))
				tmps = tmps->next->next;
			if (tmps && (tmps->type == word || tmps->type == pip))
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
		if (!tmp->prev && !tmp->next && check_builtins(tmp, option, env))
			return ;
		pd[i] = -1;
		if(option)
		{
			pd[i] = fork();
			if (pd[i] == -1)
			{
				write (2, "error\n", 7);
				g_an.exit_status = 1;
			}
			if (pd[i] == 0)
			{
				signal(SIGQUIT,SIG_DFL);
				signal(SIGINT,SIG_DFL);
				dup2 (tmp->filein, 0);
				dup2 (tmp->fileout, 1);
				if(fds)
					ft_free_matrix(fds, ft_lstsize(list) - 1);
				ft_dup (tmp, option, env, fds);
			}
			ft_free(option);
		}
		ft_close(tmp);
		if (tmp)
			tmp = tmp->next;
		i++;
	}
	// if(fds)
	// 	ft_free_matrix(fds, ft_lstsize(list) - 1);
	i = 0;
	int status = 0;
	while (i < ft_lstsize(list))
	{
		if(pd[i] != -1)
			waitpid(pd[i], &status, 0);
		i++;
    }
	i = 0;
	while (i < ft_lstsize(list))
	{
		free (fds[i]);
		i++;
    }
	free (fds);
	free(pd);
	signals_in_child_process(status);
}
