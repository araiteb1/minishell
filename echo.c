/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:32:22 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/03 18:32:23 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	check_new_line(char *str)
{
	int i;

	i = 0;

	if (str[i] == '-' && str[i + 1])
	{
		i++;
		while (str[i] == 'n')
			i++;
	}
	if (str[i])
		return (0);
	return (1);
}

void	ft_echo(t_cmd *ls)
{
	int	var;
	t_substruct *cmd;

	var = 0;

	cmd = ls->s_substruct->next;  
    while (cmd && check_new_line(cmd->data))
	{
		var = 1;
       	cmd = cmd->next;
	}
	while (cmd)
	{
		ft_putstr_fd(cmd->data, 1);
		cmd = cmd->next;
		if (cmd)
			write(1, " ", 1);
	}

	if (!var)
		write(1, "\n", 1);
	an.exit_status = 0;
}