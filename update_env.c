/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:33:06 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/03 18:41:07 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_environement	*creation_node_in_env(char *env, char *key, char *val)
{
	t_environement	*node;

	node = malloc(sizeof(t_environement));
	if (!node)
		return(perror(""), NULL);
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

	env = an.environement;
    var = env;
	while (env)
	{
		free(env->cle);
		free(env->valeur);
		free(env->env);
		var = env;
		env = env->next;
		free(var); 
        // var = NULL;
	}
	an.environement = NULL;
}
