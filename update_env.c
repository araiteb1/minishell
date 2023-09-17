/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:33:06 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/16 23:42:51 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_environement	*creation_node_in_env(char *env, char *key, char *val)
{
	t_environement	*node;

	node = malloc(sizeof(t_environement));
	if (!node)
		return (perror(""), NULL);
	node->env = env;
	node->cle = key;
	node->valeur = val;
	node->next = NULL;
	return (node);
}

void	lstadd_back_environement(t_environement **list, t_environement *new)
{
	t_environement	*node;

	if (!list || !new)
		return ;
	node = *list;
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new;
	}
	else
		*list = new;
}

void	free_environement(void)
{
	t_environement	*env;
	t_environement	*var;

	env = g_an.environement;
	var = env;
	while (env)
	{
		free(env->cle);
		free(env->valeur);
		free(env->env);
		var = env;
		env = env->next;
		free(var); 
	}
	g_an.environement = NULL;
}

char	**get_env_values(t_environement *env_list)
{
	int					count;
	t_environement		*current;
	char				**env_values;
	int					i;
	char 				*tmp;

	current = env_list;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	env_values = (char **)malloc((count + 1) * sizeof(char *));
	if (!env_values)
		return (perror(""), g_an.exit_status = 1, NULL);
	current = env_list;
	i = 0;
	while (current)
	{
		tmp = ft_strjoin(current->cle, "=");
		env_values[i] = ft_strjoin(tmp, \
		current->valeur);
		free(tmp);
		i++;
		current = current->next;
	}
	return (env_values[i] = NULL, env_values);
}
