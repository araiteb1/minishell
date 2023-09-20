/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:32:33 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/17 03:49:31 by araiteb          ###   ########.fr       */
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

void	normal_exit(void)
{
	ft_putstr_fd("exit\n", 2);
	free_environement();
	g_an.exit_status = 0;
	exit(0);
}

void	ft_exit(t_cmd *lst)
{
	if (lst->s_substruct && !lst->s_substruct->next)
		normal_exit();
	else if (!correct_arg(lst->s_substruct->next->data))
	{
		free_environement();
		message_error("exit \n", "minishell : exit: ", \
		lst->s_substruct->next->data);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_an.exit_status = 255;
		exit (255);
	}
	else if (n_lstsize(lst->s_substruct) > 2)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishel: exit: too many arguments\n", 2);
		g_an.exit_status = 1;
		return ;
	}
	else
	{
		free_environement();
		ft_putstr_fd("exit\n", 2);
		exit(ft_atoi((lst->s_substruct->next->data)));
	}
}
