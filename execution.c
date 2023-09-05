/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 04:13:02 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/04 00:14:15 by nait-ali         ###   ########.fr       */
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


void	ft_dup(t_cmd *ls, char **option, char **env)
{
	dup2 (ls->filein, 0);
	dup2 (ls->fileout, 1);
	if(ls->filein != 0)
		close (ls->filein);
	if (ls->fileout != 1)
		close (ls->fileout);
	// if (check_builtins(ls) == 1)
	// 	exit(0);
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
	path = ft_get_path(option[0], env);
	if (execve (path, option, env) == -1)
	{
		an.exit_status = 127;
		printf("minishell: ,%s : command not found \n", option[0]);
		exit (EXIT_FAILURE);
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
				if(!get_rd(&tmps, tmp, fds))
					return ;
			}
			tmps = tmps->next;
		}
		pd[i] = fork();
		if (pd[i] == -1)
		{
			write (2, "error\n", 7);
			an.exit_status = 1;
		}
		if (pd[i] == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);	
			signal(SIGTSTP, SIG_DFL);
			ft_dup (tmp, option, env);
		}
		if(option)
			ft_free(option);
		if(tmp->filein != 0)
			close (tmp->filein);
		if (tmp->fileout != 1)
			close (tmp->fileout);
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
	if(fds)
		ft_free_matrix(fds, ft_lstsize(list) - 1);
}
 // while(wait(&status) =! -1);