/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:32:37 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/03 18:32:37 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	add_val_var_env(t_environement *tmp, char *str, int i, char c)
{
	char	*val;
	char	*var;
	char	*ch;

	if (c == '+')
	{
		ch = str_sans_plus(str);
		val = ft_substr(ch, i + 1, ft_strlen(str) - i - 1);
		var = ft_strjoin(tmp->valeur, val);
		free(tmp->valeur);
		if (val)
			free (val);
		free (ch);
		tmp->valeur = var;
	}
	else
	{
		var = ft_substr(str, i + 1, ft_strlen(str) - i);
		free(tmp->valeur);
		tmp->valeur = var;
	}
	var = ft_strjoin(tmp->cle, "=");
	free(tmp->env);
	tmp->env = ft_strjoin(var, tmp->valeur);
	free(var);
}

static	int	search_key_in_env(char *var, char *s, int i, char c)
{
	t_environement	*tmp;

	tmp = g_an.environement;
	while (tmp)
	{
		if (!ft_strcmp(var, tmp->cle))
		{
			if (c)
			{
				add_val_var_env(tmp, s, i, c);
				free(var);
			}
			else
				free(var);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	export_variables(char *str, char c)
{
	int		i;
	char	*var;

	i = 0;
	if (c)
	{
		i = find_equal_or_plus(str, c);
		var = ft_substr(str, 0, i);
	}
	else
		var = ft_strdup(str);
	if (!search_key_in_env(var, str, i, c))
		export_new_var_in_env(str, var, c, i);
}

void	export(t_substruct *varr, int flag, char *var, char **option)
{
	int		i;

	i = 1;
	while (varr && varr->data[0] != '<' && varr->data[0] != '<')
	{
		flag = 0;
		var = varr->data;
		while ((*var >= 'a' && *var <= 'z') || \
		(*var >= 'A' && *var <= 'Z') || *var == '_')
		{
			flag++;
			var++;
		}
		while (((*var >= 'a' && *var <= 'z') || (*var >= 'A' && *var <= 'Z') \
		|| (*var >= '0' && *var <= '9') || *var == '_'))
			var++;
		if (!flag || (!(*var == '+' && *(var + 1) == '=') \
		&& *var != '=' && *var))
		{
			error_args_export(varr->data);
			g_an.exit_status = 1;
		}
		export_variables(option[i], *var);
		varr = varr->next;
		i++;
	}
}

void	ft_export(t_cmd *cmd, char **option)
{
	t_substruct	*varr;
	int			flag;
	char		*var;

	flag = 0;
	var = NULL;
	varr = cmd->s_substruct->next;
	if (!varr || varr->data[0] == '>' || varr->data[0] == '<')
		print_environement(cmd);
	else
		export(varr, flag, var, option);
	g_an.exit_status = 0;
}
