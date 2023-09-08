/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:33:00 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/08 16:32:33 by nait-ali         ###   ########.fr       */
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
	// tmp = NULL;
}

int	valid_args(char *var)
{
	int	l;

	l = 0;
	while ((*var >= 'a' && *var <= 'z') || (*var >= 'A' && *var <= 'Z') || *var == '_')
	{
		var++;
		l++;
	}
	while (((*var >= 'a' && *var <= 'z') || (*var >= 'A' && *var <= 'Z')
		|| (*var >= '0' && *var <= '9') || *var == '_'))
		var++;
	if (!l || (!(*var == '+' && *(var + 1) == '=') && *var != '=' && *var))
		return (1);
		//khassni nprinti lmessage d'erreur
	return (0);
}

int	find_equal(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == c)
			return (i);
		s++;
		i++;
	}
	return (-1);
}

void	ft_unset(t_cmd *cmd)
{
	t_environement	*var;
	t_environement	*save;
	t_substruct *tmp;
	int		i;

	tmp = cmd->s_substruct->next;
	while (tmp)
	{
		if(valid_args(tmp->data))
		{
			ft_putstr_fd("minishell: unset: `", cmd->fileout);
			// printf("%s------->\n :", cmd->data);
			ft_putstr_fd(tmp->data,cmd->fileout);
			ft_putstr_fd("': not a valid identifier\n", cmd->fileout);
			an.exit_status = 1;
			return ;
		}
		if (!valid_args(tmp->data))
		{
			an.exit_status = 0;
			var = an.environement;
			i = 0;
			while (var)
			{
				if (!ft_strcmp(tmp->data, var->cle))
				{
					supprimer_var_env(save, i);
						break; 
				}
				save = var;
				var = var->next;
				i++;
			}
		}
		tmp = tmp->next;
	}
}