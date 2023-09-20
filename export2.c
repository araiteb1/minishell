/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 03:35:16 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/18 03:02:34 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_environement	*env_copie(t_environement	*env)
{
	t_environement	*tmp;

	tmp = NULL;
	while (env)
	{
		lstadd_back_environement(&tmp, creation_node_in_env
			(env->env, env->cle, env->valeur));
		env = env->next;
	}
	return (tmp);
}

static	void	sorting(t_environement *env)
{
	t_environement	*tmp;
	char			*swap;

	while (env)
	{
		tmp = env->next;
		while (tmp)
		{
			if (ft_strcmp(env->cle, tmp->cle) > 0)
			{
				swap = env->cle;
				env->cle = tmp->cle;
				tmp->cle = swap;
				swap = env->env;
				env->env = tmp->env;
				tmp->env = swap;
				swap = env->valeur;
				env->valeur = tmp->valeur;
				tmp->valeur = swap;
			}
			tmp = tmp->next;
		}
		env = env->next;
	}
}

void	free_env_copie(t_environement *env)
{
	t_environement	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp);
		tmp = NULL;
	}
	g_an.exit_status = 0;
}

void	print_environement(t_cmd *ls)
{
	t_environement	*env;
	t_environement	*tmp;

	env = env_copie(g_an.environement);
	sorting(env);
	tmp = env;
	while (env)
	{
		ft_putstr_fd("declare -x ", ls->fileout);
		ft_putstr_fd(env->cle, ls->fileout);
		if (find_equal_or_plus(env->env, '=') != -1)
		{
			ft_putstr_fd("=\"", ls->fileout);
			ft_putstr_fd(env->valeur, ls->fileout);
			ft_putstr_fd("\"", ls->fileout);
		}
		ft_putstr_fd("\n", ls->fileout);
		env = env->next;
	}
	free_env_copie(tmp);
	g_an.exit_status = 0;
}

char	*str_sans_plus(char *str)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(ft_strlen(str));
	if (!res)
		return (perror(""), NULL);
	while (*str)
	{
		if (*str == '+')
			str++;
		res[i++] = *str++;
	}
	res[i] = '\0';
	return (res);
}
