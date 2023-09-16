/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:32:47 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/16 02:20:30 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_cmd *cmd)
{
	t_environement	*tmp;
	char			*var;

	tmp = g_an.environement;
	var = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->cle, "PWD"))
		{
			printf("pwd val :%s \n", tmp->valeur);
			ft_putstr_fd(tmp->valeur, cmd->fileout);
			ft_putstr_fd("\n", cmd->fileout);
			return ;
		}
		tmp = tmp->next;
	}
	ft_putstr_fd(getcwd(var, PATH_MAX), cmd->fileout);
	ft_putstr_fd("\n", cmd->fileout);
	g_an.exit_status = 0;
}
