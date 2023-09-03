/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:32:47 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/03 21:35:35 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_pwd()
{
	char	table[PATH_MAX];

	
	if (!getcwd(table, PATH_MAX))
	{
		perror("minishell: pwd: ");
		an.exit_status = 1;
		return ;
	}
	write(1, &table, ft_strlen(table));
	write(1, "\n", 1);
	an.exit_status = 0;
}