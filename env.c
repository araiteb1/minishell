/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:32:29 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/09 03:53:58 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_cmd *cmd)
{
	t_environement *env;
	char *tmp;

	env = an.environement;
	if (cmd->s_substruct->next)
	{
		// if((cmd->s_substruct->next->data[0] != '>') && (cmd->s_substruct->next->data[0] != '<' ))
		// {
			tmp = cmd->s_substruct->next->data;
			an.exit_status = 1;
			ft_putstr_fd("env: ", 2);
			ft_putstr_fd(tmp, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			an.exit_status=127;
			return ;
		// }
			
	}
	while (env)
	{
		if (ft_strchr(env->env, '='))
		{
			ft_putstr_fd(env->cle, cmd->fileout);
			ft_putstr_fd("=", cmd->fileout);
			ft_putstr_fd(env->valeur, cmd->fileout);
			ft_putstr_fd("\n", cmd->fileout);
		}
		env = env->next;
	}
	an.exit_status = 0;
}
