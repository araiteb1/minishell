/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:32:29 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/03 18:32:30 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_cmd *cmd)
{
	t_environement *env;

	env = an.environement;
	if(cmd->s_substruct->next)
	{
		an.exit_status = 1;
		ft_putstr_fd("minishell: env: Too many arguments.\n", 2);
		return ;	
	}

	while (env)
	{
		if (ft_strchr(env->env, '='))
		{
			ft_putstr_fd(env->env, 1);
			ft_putstr_fd("\n", 1);
		}
		env = env->next;
	}
	an.exit_status = 0;
}
