/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:41:59 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/12 11:26:45 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_herdoc(int sig)
{
	(void)sig;
	an.flag_herdoc = 1;
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
	while (str && ft_strncmp(str, end, ft_strlen(str) - 1))
	{
		write(fl, str, ft_strlen(str));
		write(fl, "\n", 1);
		if (str)
			free (str);
		str = readline("> ");
		if (!str)
			break ;
	}
	if (an.flag_herdoc == 1)
		dup2 (fd, 0);
	close (fd);
	return (fl);
}
