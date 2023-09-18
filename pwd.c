/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:32:47 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/18 02:31:00 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int find_pwd_in_env(t_environement *tmp, t_cmd *cmd)
{
    while (tmp)
    {
        if (!ft_strcmp(tmp->cle, "PWD"))
        {
            ft_putstr_fd(tmp->valeur, cmd->fileout);
            ft_putstr_fd("\n", cmd->fileout);
            return 0;
        }
        tmp = tmp->next;
    }
    return (1);
}

void    ft_pwd(t_cmd *cmd)
{
    t_environement    *tmp;

    tmp = g_an.environement;
    if (!find_pwd_in_env(tmp, cmd))
        return ;
    else
    {
        ft_putstr_fd(g_an.pp, cmd->fileout);
        ft_putstr_fd("\n", cmd->fileout);
    }

    g_an.exit_status = 0;
}