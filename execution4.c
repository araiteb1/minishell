/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 04:06:07 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/20 01:20:42 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	help_get_rd3(t_substruct **cmd, t_cmd *ls, int **fds, char *rdprev)
{
	int	is_tr;

	is_tr = 0;
	if ((*cmd)->type == heredoc || \
	((*cmd)->type == rd_input) || rdprev != NULL )
	{
		if (!help_get_rd2(ls, cmd, rdprev, fds))
			return (0);
		is_tr = 1;
	}
	else if (!is_tr && ls && ls->prev)
		ls->filein = fds[ls->i - 1][0];
	return (1);
}

int	get_rd(t_cmd *command, t_substruct **cmd, t_cmd *ls, int **fds)
{
	char	*rdprev;
	int		is_tr;

	rdprev = getlastcmd(command);
	is_tr = 0;
	if (!help_get_rd3(cmd, ls, fds, rdprev))
		return (0);
	is_tr = 0;
	if (((*cmd) && (*cmd)->type == rd_output)
		|| ((*cmd) && (*cmd)->type == rd_output_append))
	{
		help_get_rd(cmd, ls, fds);
		if (ls->fileout == -1)
			return (0);
		is_tr = 1;
		(*cmd) = (*cmd)->next;
	}
	ft_free_str(rdprev);
	if (!is_tr && ls && ls->next)
		ls->fileout = fds[ls->i][1];
	return (1);
}
