/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 04:13:02 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/20 06:34:05 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup(t_cmd *ls, char **option, char **env)
{
	ft_close (ls);
	if (option)
		expand_env_variable(option, env);
	ls->filein = 0;
	ls->fileout = 1;
	if (check_builtins(ls, option, env))
		exit (0);
	exec_chile (option, env, ls);
}

void	init_var(t_varn **var, t_cmd *list)
{
	(*var) = (t_varn *)malloc(sizeof(t_varn));
	if (!*var)
		return ;
	(*var)->i = 0;
	(*var)->size = ft_lstsize(list);
	(*var)->fds = (int **)malloc(sizeof(int *) * ((*var)->size));
	if (!(*var)->fds)
		return ;
	(*var)->pd = (int *)malloc(sizeof(int) * ((*var)->size));
	if (!(*var)->pd)
		return ;
	ft_creat_pipe(ft_lstsize(list), (*var)->fds);
}

void	instrc_chile(t_varn *var, t_cmd *tmp, char **env)
{
	if (var->option)
	{
		var->pd[var->i] = fork();
		if (var->pd[var->i] == -1)
		{
			write (2, "error\n", 7);
			g_an.exit_status = 1;
		}
		if (var->pd[var->i] == 0)
		{
			signal (SIGQUIT, SIG_DFL);
			signal (SIGINT, SIG_DFL);
			dup2 (tmp->filein, 0);
			dup2 (tmp->fileout, 1);
			if (var->fds)
				ft_free_matrix(var->fds, var->size);
			ft_dup (tmp, var->option, env);
		}
		ft_free (var->option);
	}
}

int	one_built(t_varn *var, t_cmd *tmp, char **env)
{
	t_substruct	*tmps;

	var->option = NULL;
	tmps = tmp->s_substruct;
	get_option(&(var->option), tmps);
	tmps = tmp->s_substruct;
	if (!checkrd(tmp, tmps, var->fds) || g_an.flag_herdoc == 1)
	{
		if (var->fds)
			ft_free_matrix(var->fds, var->size);
		free (var->pd);
		ft_free (var->option);
		g_an.exit_status = 1;
		return (0);
	}
	if (!tmp->prev && !tmp->next && check_builtins(tmp, var->option, env))
	{
		if (var->fds)
			ft_free_matrix(var->fds, var->size);
		free (var->pd);
		ft_free (var->option);
		return (0);
	}
	return (1);
}

void	ft_execution(t_cmd *list, char **env)
{
	t_cmd		*tmp;
	t_varn		*var;

	tmp = list;
	init_var(&var, list);
	while (tmp && var->i < ft_lstsize(list))
	{
		if (!one_built(var, tmp, env))
		{
			free (var);
			return ;
		}
		var->pd[var->i] = -1;
		instrc_chile(var, tmp, env);
		ft_close (tmp);
		if (tmp)
			tmp = tmp->next;
		var->i++;
	}
	wait_pd(var, ft_lstsize(list));
	if (var->fds)
		ft_free_matrix(var->fds, ft_lstsize(list));
	free (var->pd);
	free(var);
}
