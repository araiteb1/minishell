/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 00:24:01 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/14 03:48:28 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_handler(int sig)
{
	(void)sig;
	if (waitpid(0, NULL, WNOHANG))
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		an.exit_status = 1;
	}
}

void	init_signals(void)
{
	an.flag_herdoc = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, my_handler);
}

void	signals_in_child_process(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("\\Quit: 3\n", 1);
		if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", 1);
		if (an.flag_herdoc == 0)
			return ;
		an.exit_status = WTERMSIG(status) + 128;
	}
	else 
		an.exit_status = WEXITSTATUS(status);
}
