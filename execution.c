/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 04:13:02 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/19 06:15:16 by nait-ali         ###   ########.fr       */
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

int	check_doll(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_size_nam(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c)
		i++;
	return (i);
}

void	get_option(char ***option, t_substruct *tmps)
{
	while (tmps)
	{
		if ((tmps->type != word) && (tmps->type != pip))
			tmps = tmps->next->next;
		if (tmps && (tmps->type == word || tmps->type == pip))
		{
			(*option) = __resize((*option), tmps->data);
			tmps = tmps->next;
		}
	}
}

int	checkrd(t_cmd *tmp, t_substruct *tmps, int **fds)
{
	while (tmps)
	{
		if (tmps->next && tmps->next->type != word)
			tmps = tmps->next;
		if ((tmps && !tmps->prev) || tmps->type != word)
		{
			if (!get_rd(tmp->prev, &tmps, tmp, fds))
				return (0);
		}
		tmps = tmps->next;
	}
	return (1);
}

void	wait_pd(t_varn *var, int size)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < size)
	{
		if ((var->pd[i]) != -1)
			waitpid((var->pd[i]), &status, 0);
		i++;
	}
	signals_in_child_process(status);
}

void	init_var(t_varn *var, t_cmd *list)
{
	var->i = 0;
	var->size = ft_lstsize(list);
	var->fds = (int **)malloc(sizeof(int *) * var->size);
	var->pd = (int *)malloc(sizeof(int) * (var->size));
	ft_creat_pipe(ft_lstsize(list), var->fds);
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
	var = (t_varn *)malloc(sizeof(t_varn));
	init_var(var, list);
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
