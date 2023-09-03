/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:32:33 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/03 20:18:39 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	correct_arg(char *num)
{
	int	i;

	i = 0;
	if (num[i] == '-')
		i++;
	while (num[i])
	{
		if (num[i] >= '0' && num[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}



 void ft_exit(t_cmd *lst)
 {
	if (lst->s_substruct && !lst->s_substruct->next)
	{
		//khass nfree dakchi li khasso itfriya
		an.exit_status = 0;
		exit(0);
	}
	if (n_lstsize(lst->s_substruct) > 2 )
	{

		ft_putstr_fd("minishel: exit: too many arguments\n", 2);
		an.exit_status = 1;
		return ;
	}

	if (n_lstsize(lst->s_substruct) == 2 && !correct_arg(lst->s_substruct->next->data))
	{
		ft_putstr_fd("exit \n", 2);
		ft_putstr_fd("minishell : exit: numeric argument required\n", 2);
		an.exit_status = 255;
		exit (255);
	}
	else
		exit(ft_atoi((lst->s_substruct->next->data)));

 }