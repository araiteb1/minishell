/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:41:59 by araiteb           #+#    #+#             */
/*   Updated: 2023/08/22 22:57:15 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here_doc(char *tmps, char *end)
{
	int		fl;
	char	*str;


	fl = ft_check_fils(tmps, O_CREAT | O_RDWR | O_TRUNC, 0644);
	str = readline("> ");
	while (ft_strncmp(str, end, ft_strlen(str) - 1))
	{
		write(fl, str, ft_strlen(str));
		write(fl, "\n", 1);
		if (str)
			free (str);
		str = readline("> ");
		if (!str)
			break ;
	}
	return (fl);
}
