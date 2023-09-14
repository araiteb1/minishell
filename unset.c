/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:33:00 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/14 03:05:26 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	supprimer_var_env(t_environement *node, int var)
{
	t_environement	*tmp;

	if (!var)
	{
		tmp = an.environement;
		an.environement = an.environement->next;
	}
	else
	{
		tmp = node->next;
		node->next = node->next->next;
	}
	free(tmp->env);
	free(tmp->cle);
	free(tmp->valeur);
	free(tmp); 
}

int	valid_args(char *var)
{
	int	flag;

	flag = 0;
	while ((*var >= 'a' && *var <= 'z') || \
	(*var >= 'A' && *var <= 'Z') || *var == '_')
	{
		var++;
		flag++;
	}
	while (((*var >= 'a' && *var <= 'z') || (*var >= 'A' && *var <= 'Z') \
	|| (*var >= '0' && *var <= '9') || *var == '_'))
		var++;
	if (!flag || (!(*var == '+' && *(var + 1) == '=') && *var != '=' && *var))
		return (1);
	return (0);
}

int	find_equal_or_plus(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	help_unset(char *tmp)
{
	t_environement	*var;
	t_environement	*save;
	int				i;

	var = an.environement;
	i = 0;
	while (var)
	{
		if (!ft_strcmp(tmp, var->cle))
		{
			supprimer_var_env(save, i);
			break ;
		}
		save = var;
		var = var->next;
		i++;
	}
}

void	ft_unset(t_cmd *cmd)
{
	t_substruct		*tmp;

	tmp = cmd->s_substruct->next;
	while (tmp)
	{
		if (valid_args(tmp->data))
		{
			message_error("minishell: unset: `", tmp->data, \
			"': not a valid identifier\n");
			an.exit_status = 1;
		}
		if (!valid_args(tmp->data))
		{
			help_unset(tmp->data);
		}
		tmp = tmp->next;
	}
}
