/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:49:20 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/19 07:07:02 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_new_var_in_env(char *str, char *var, char c, ssize_t index)
{
	char	*tmp;

	if (c == '=')
		lstadd_back_environement(&g_an.environement, \
		creation_node_in_env(ft_strdup(str), \
		var, ft_substr(str, index + 1, ft_strlen(str) - index)));
	else if (c == '+')
	{
		str = str_sans_plus(str);
		tmp = ft_substr(str, index + 1, ft_strlen(str) - index);
		if (ft_strlen(tmp) == 1)
		{
			free(tmp);
			tmp = strdup("");
		}
		lstadd_back_environement(&g_an.environement, creation_node_in_env(str,
				var, tmp));
	}
	else
	{
		lstadd_back_environement(&g_an.environement, \
				creation_node_in_env(ft_strdup(var), ft_strdup(var), NULL));
		free(var);
	}
}
