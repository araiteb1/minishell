/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 04:13:02 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/08 19:00:45 by nait-ali         ###   ########.fr       */
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

	dup2 (ls->filein, 0);
	dup2 (ls->fileout, 1);
	if(ls->filein != 0)
		close (ls->filein);
	if (ls->fileout != 1)
		close (ls->fileout);
	// int i = 0;
	// while (option[i])
	// 	ft_putstr_fd(option[i++], 2);
	ls->filein = 0;
	ls->fileout = 1;
	if (check_builtins(ls) == 1)
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
	char		**option;//execve(path, optin, env);
	int			**fds;//pipe
	pid_t		*pd;//fork();
	int			i;
	tmp = list;
	i = 0;


	fds = (int **)malloc(sizeof(int *) * ft_lstsize(list) - 1);
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
				// printf(" word :%s   \n", tmps->data);
				option = __resize(option, tmps->data);// ls -la
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
				// printf(" dekhlat hna 1 :\n");
				if(!get_rd(&tmps, tmp, fds))
					return ;
			}
			tmps = tmps->next;
		}
		an.flag_signal = 1;
		if (!tmp->prev && !tmp->next && check_builtins(tmp))
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
		if(tmp->filein != 0)
			close (tmp->filein);
		if (tmp->fileout != 1)
			close (tmp->fileout);
		if (tmp)
			tmp = tmp->next;
		i++;
	}
	i = 0;
		int status;
	while (i < ft_lstsize(list))
	{
		waitpid(pd[i], &status, 0);
		i++;
    }
	// if (WIFEXITED(status))
	// 	an.exit_status = status;
	// else if (WIFSIGNALED(status))
	// 	an.exit_status = 128 + status;
	printf("%d\n", an.exit_status);
	if(fds)
		ft_free_matrix(fds, ft_lstsize(list) - 1);
}
 // while(wait(&status) =! -1);