/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:32:47 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/07 20:13:59 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_pwd(t_cmd *cmd)
{
	t_environement *tmp;

	tmp = an.environement;
	while(tmp)
	{
		if(!ft_strcmp(tmp->cle,"PWD"))
		{

			ft_putstr_fd(tmp->valeur, cmd->fileout);
			ft_putstr_fd("\n", cmd->fileout);
			return ;
		}
		tmp = tmp->next;
	}
	an.exit_status = 0;
}