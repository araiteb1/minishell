/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 02:48:32 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/18 22:59:14 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	help_herd_rd_in(t_substruct **cmd, t_cmd *ls)
{
	char	*new;

	if ((*cmd)->next)
		(*cmd) = (*cmd)->next;
	new = subc_quots((*cmd)->data);
	ls->filein = here_doc("tmp", new);
	ls->filein = open("tmp", O_RDONLY, 0644);
	free(new);
}

int	herd_rd_in(t_cmd *ls, t_substruct **cmd, char *rdprev)
{
	char	*new;

	if ((*cmd)->type == heredoc)
		help_herd_rd_in(cmd, ls);
	else
	{
		if (rdprev)
			new = ft_strdup(rdprev);
		else
			new = subc_quots((*cmd)->next->data);
		if (access(new, F_OK) == -1)
			return (message_error("minishell : ", new, \
			": No such file or directory\n"), g_an.exit_status = 1, 0);
		else
		{
			ls->filein = open(new, O_RDONLY, 0644);
			if (ls->filein == -1)
				return (perror("open"), 0);
		}
		ft_free_str(new);
	}
	return (1);
}

char	*getlastcmd(t_cmd *cmd)
{
	t_cmd		*cm;
	t_substruct	*subs;

	cm = cmd;
	if (cm)
	{
		subs = cm->s_substruct;
		while (subs->next)
			subs = subs->next;
		if (subs->prev && (subs->prev->type == rd_output || \
		(subs->prev->prev && subs->prev->type == rd_output \
		&& subs->prev->prev->type == rd_output)))
			return (subs->data);
	}
	return (NULL);
}

void	help_get_rd(t_substruct **cmd, char *new, t_cmd *ls, int **fds)
{
	close(fds[ls->i][1]);
	new = subc_quots((*cmd)->next->data);
	if ((*cmd)->type == rd_output)
	{
		ls->fileout = ft_check_fils(new,
				(O_RDWR | O_CREAT | O_TRUNC), 0644);
	}
	else
		ls->fileout = ft_check_fils(new,
				(O_RDWR | O_CREAT | O_APPEND), 0644);
}

int	help_get_rd2(t_cmd *ls, t_substruct **cmd, char *rdprev, int **fds)
{
	if (ls->i > 0 && fds[ls->i - 1][0])
		close(fds[ls->i - 1][0]);
	if (!herd_rd_in(ls, cmd, rdprev) || g_an.flag_herdoc == 1)
		return (g_an.exit_status = 1, 0);
	return (1);
}
