/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:33:06 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/09 04:20:47 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_environement	*creation_node_in_env(char *env, char *key, char *val)
{
	t_environement	*node;
	// char *tmp;

	node = malloc(sizeof(t_environement));
	if (!node)
		return(perror(""), NULL);
	// tmp = ft_strjoin(key,"=");
	node->env = env;
	node->cle = key;
	node->valeur = val;
	node->next = NULL;
	return (node);
}

// void	lstadd_back_environement(t_environement **list, t_environement *new)
// {
// 	t_environement	*node;
// 	int flag = 0;
// 	if (!list || !new)
// 		return ;
// 	node = *list;
// 	if (node)
// 	{
// 		while (node->next)
// 		{
// 			printf(" 1111 cle ===> %s\n", node->cle);
// 			if (strcmp(node->cle, "SHLVL") == 0)
// 			{
// 				printf(" 2222 cle ===> %s\n", node->cle);
// 				flag = 1;
// 				// printf("level: %s\n", current->valeur);
// 				int shlval = atoi(node->valeur);
// 				shlval++;
// 				printf("int -->[%d]\n", shlval);
// 				// char *new_shlvl = ft_itoa(shlval);
// 				free(node->valeur);
// 				node->valeur = ft_itoa(shlval);
// 				printf("valu -->[%s]\n", node->valeur);
// 				// printf("SHLVL incremented to %s\n", current->valeur); // Ajoutez ceci pour le débogage
// 					break;
// 			}
// 			if(flag == 0)
// 				node = node->next;

// 			node->next = new;
// 		}
// 	}
// 	else
// 		*list = new;
// }


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
