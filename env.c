/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:32:29 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/16 02:20:30 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char *cle, char *valeur, t_cmd *cmd)
{
	ft_putstr_fd(cle, cmd->fileout);
	ft_putstr_fd("=", cmd->fileout);
	ft_putstr_fd(valeur, cmd->fileout);
	ft_putstr_fd("\n", cmd->fileout);
}

void	ft_env(t_cmd *cmd)
{
	t_environement	*env;
	char			*tmp;

	env = g_an.environement;
	if (cmd->s_substruct->next)
	{
		tmp = cmd->s_substruct->next->data;
		if ((tmp[0] != '>') && (tmp[0] != '<' ))
		{
			message_error("env: ", tmp, ": No such file or directory\n");
			g_an.exit_status = 127;
			return ;
		}
	}
	while (env)
	{
		if (env->valeur)
			print_env(env->cle, env->valeur, cmd);
		env = env->next;
	}
	g_an.exit_status = 0;
}
