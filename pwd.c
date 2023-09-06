/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:32:47 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/04 00:16:33 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_pwd()
{
	t_environement *tmp;

	tmp = an.environement;
	while(tmp)
	{
		if(!ft_strcmp(tmp->cle,"PWD"))
		{

			ft_putstr_fd(tmp->valeur, 1);
			ft_putstr_fd("\n", 1);
			return ;
		}
		tmp = tmp->next;
	}
	an.exit_status = 0;
}