/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 02:48:32 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/09 01:46:58 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	herd_rd_in(t_cmd *ls, t_substruct **cmd)
{
	char *new = NULL;
	
	if ((*cmd)->type == heredoc)
	{
		if((*cmd)->next)
			(*cmd) = (*cmd)->next;
		printf("new1  %s\n", (*cmd)->data);
		new = subc_quots((*cmd)->data);
		printf("new  %s\n", new);
		ls->filein = here_doc("tmp", new);
		ls->filein = open("tmp", O_RDONLY, 0644);
	}
	else
	{
		printf("%s\n",(*cmd)->next->data);
		new = subc_quots((*cmd)->next->data);
		if(access(new , F_OK) == -1)
		{
			write(2, "minishell : ",13);
			write(2, new , ft_strlen(new));
			write(2, ": No such file or directory\n", 29);
			an.exit_status = 1;
			return(0);
		}
		else
			ls->filein = open(new, O_RDONLY, 0644);
	}
	return(1);
}

int	get_rd(t_substruct **cmd, t_cmd *ls, int **fds)
{
	char 	*new = NULL;
	if ((*cmd)->type == heredoc || (*cmd)->type == rd_input)
	{
		if(!herd_rd_in(ls, cmd))
			return(0);
		
	}
	else if (ls && ls->prev)
		ls->filein = fds[ls->i - 1][0];
	if (((*cmd) && (*cmd)->type == rd_output)
		|| ((*cmd) && (*cmd)->type == rd_output_append))
	{
		new = subc_quots((*cmd)->next->data);
		if ((*cmd)->type == rd_output)
		{
			ls->fileout = ft_check_fils(new,
					(O_RDWR | O_CREAT | O_TRUNC), 0644);
		}
		else
			ls->fileout = ft_check_fils(new,
					(O_RDWR | O_CREAT | O_APPEND), 0644);
		(*cmd) = (*cmd)->next;
	}
	if (ls && ls->next)
	{
		ls->fileout = fds[ls->i][1];
	}
	return(1);
}

void	ft_close(t_cmd *ls)
{
	close (ls->filein);
	close (ls->fileout);
}

void	ft_free_matrix(int **str, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free (str[i]);
		i++;
	}
	free (str);
}

void	ft_creat_pipe(int size, int **fds)
{
	int	i;

	i = 0;
	while (i < size)
	{
		fds[i] = malloc(sizeof(int) * 2);
		if (pipe(fds[i]) == -1)
		{
			write(2, "error piping\n", 14);
			an.exit_status = 1;
		}
		i++;
	}
}
