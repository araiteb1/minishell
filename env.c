/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:32:29 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/04 15:54:25 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_cmd *cmd)
{
	t_environement *env;
	char *tmp;

	env = an.environement;
	if(cmd->s_substruct->next)
	{
		tmp = cmd->s_substruct->next->data;
		an.exit_status = 1;
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return ;	
	}

	while (env)
	{
		if (ft_strchr(env->env, '='))
		{
			ft_putstr_fd(env->cle, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(env->valeur, 1);
			ft_putstr_fd("\n", 1);
		}
		env = env->next;
	}
	an.exit_status = 0;
}
