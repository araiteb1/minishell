/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:41:59 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/19 03:03:46 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_herdoc(int sig)
{
	(void)sig;
	g_an.flag_herdoc = 1;
	close (0);
}

int	help(char *tmps)
{
	int	fl;

	signal (SIGINT, sigint_herdoc);
	fl = ft_check_fils(tmps, O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (fl);
}

void	help2(char *str, int fl)
{
	write(fl, str, ft_strlen(str));
	write(fl, "\n", 1);
}

void	help3(char *str, int fd)
{
	free (str);
	if (g_an.flag_herdoc == 1)
		dup2 (fd, 0);
}

int	here_doc(char *tmps, char *end)
{
	int		fl;
	char	*str;
	int		fd;

	fd = dup(0);
	fl = help(tmps);
	str = readline("> ");
	if (!ft_strcmp(end, " "))
		write(fl, str, ft_strlen(str));
	while (str && ft_strcmp(str, end))
	{
		help2(str, fl);
		if (str)
			free (str);
		str = readline("> ");
		if (!str)
		{
			ft_free_str(str);
			break ;
		}
	}
	help3(str, fd);
	close (fd);
	return (fl);
}
