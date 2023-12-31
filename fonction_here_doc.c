/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:41:59 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/17 22:55:48 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_herdoc(int sig)
{
	(void)sig;
	g_an.flag_herdoc = 1;
	close (0);
}

int	here_doc(char *tmps, char *end)
{
	int		fl;
	char	*str;
	int		fd;

	fd = dup(0);
	signal (SIGINT, sigint_herdoc);
	fl = ft_check_fils(tmps, O_CREAT | O_RDWR | O_TRUNC, 0644);
	str = readline("> ");
	if(!ft_strcmp(end, " "))
		write(fl, str, ft_strlen(str));
	while (str && ft_strcmp(str, end))
	{
		write(fl, str, ft_strlen(str));
		write(fl, "\n", 1);
		if (str)
			free (str);
		str = readline("> ");
		if (!str)
		{
			ft_free_str(str);
			break ;
		}
	}
	free (str);
	if (g_an.flag_herdoc == 1)
		dup2 (fd, 0);
	close (fd);
	return (fl);
}
