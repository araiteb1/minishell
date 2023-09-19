/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execchile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 00:01:10 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/19 05:35:43 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_ev(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 4))
			break ;
		i++;
	}
	return (i);
}

char	*ft_get_path(char *cmd, char **env)
{
	int		i;
	char	*path;
	char	*tmp;
	char	**str;

	str = NULL;
	if (cmd && cmd[0] != '/')
	{
		path = ft_substr (env[get_ev(env)], 5, ft_strlen(env[get_ev(env)]));
		str = ft_split (path, ':');
		free (path);
		i = 0;
		while (str[i])
		{
			tmp = str[i];
			path = ft_strjoin(tmp, "/");
			free (tmp);
			tmp = path;
			path = ft_strjoin(tmp, cmd);
			free (tmp);
			if (access (path, F_OK) == 0)
				return (path);
			i++;
		}
	}
	return (cmd);
}

void	exec_chile(char **option,  char **env,t_cmd *list)
{
	char	*path;
	char	*str;

	if (!ft_strcmp(option[0], " "))
	{
		free_list (&list);
		ft_free (option);
		exit (0);
	}
	path = ft_get_path(option[0], env);
	if (execve (path, option, env) == -1)
	{
		if (option && option[0] && option[0][0] == '.' && option[0][1] == '/')
		{
			str = strerror (errno);
			if (!ft_strcmp(str, "Exec format error"))
				message_error("minishell: ", option[0], \
				": Permission denied\n" );
			else
				message_error("minishell: ", option[0], \
				": is a directory\n" );
			g_an.exit_status = 126;
		}
		else
		{
			g_an.exit_status = 127;
			message_error("minishell: ", option[0], \
				" : command not found \n");
		}
		free_list (&list);
		ft_free (option);
		exit (g_an.exit_status);
	}
}
