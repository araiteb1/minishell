/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messaages.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:01:36 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/17 04:19:29 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chedir_error(char *to)
{
	char *tmp;
	if (chdir(to)) 
	{
		tmp = ft_strjoin(to, ": ");
		
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(tmp, 2);
		free(tmp);
		perror("");
		g_an.exit_status = 1;
		return (0);
	}
	return (1);
}

int	cd_not_exist_directory(char *to)
{
	if (!to && errno == ENOENT)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
		ft_putstr_fd("cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		g_an.exit_status = 0;
		return (0);
	}
	return (1);
}

void	error_args_export(char *varr)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(varr, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_an.exit_status = 1;
}

void	message_error(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(s3, 2);
}
