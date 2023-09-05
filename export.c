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
	char	*swap;

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
	t_environement	*keep;

	while (env)
	{
		keep = env;
		env = env->next;
		(free(keep), keep = NULL);
	}
	an.exit_status = 0;
}

static	void	print_environement(void)
{
	t_environement	*env;
	t_environement	*var;
	t_environement	*tmp;

	env = env_copie(an.environement);
	sorting(env);
	tmp = env;
	while (env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->cle, 1);
		if (find_equal(env->env, '=') != -1)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env->valeur, 1);
			ft_putstr_fd("\"", 1);
		}
		
		ft_putstr_fd("\n", 1);
		env = env->next;
	}
	while (tmp)
	{
		var = env;
		tmp = tmp->next;
		free(var);
	}
	an.exit_status = 0;
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


void	export_new_var_in_env(char *str, char *var, char c, ssize_t index)
{
	if (c == '=')
		lstadd_back_environement(&an.environement, creation_node_in_env(ft_strdup(str),
				var, ft_substr(str, index + 1,
					ft_strlen(str) - index)));
	else if (c == '+')
	{
		
		str = str_sans_plus(str);
		lstadd_back_environement(&an.environement, creation_node_in_env(str,
				var, ft_substr(str, index + 1,
					ft_strlen(str) - index)));
	}
	else
		(lstadd_back_environement(&an.environement,
				creation_node_in_env(ft_strdup(var), ft_strdup(var), NULL)),
			free(var));
}

void	add_val_var_env(t_environement *tmp, char *str, int i, char c)
{
	char	*val;
	char	*var;
	char *ch;

	if (c == '+')
	{
		ch = str_sans_plus(str);
		val = ft_substr(ch, i + 1, ft_strlen(str) - i - 1);
		var = ft_strjoin(tmp->valeur, val);
		printf("%s------>>>>>|\n", var);
		(free(tmp->valeur), free(val), free(ch), tmp->valeur = var);
	}
	else
	{
		var = ft_substr(str, i + 1, ft_strlen(str) - i);
		free(tmp->valeur);
		tmp->valeur = var;
	}
	var = ft_strjoin(tmp->cle, "=");
	(free(tmp->env), tmp->env = ft_strjoin(var, tmp->valeur));
	free(tmp->cle);
	free(var);
}

static	int	search_key_in_env(char *var, char *s, int i, char c)
{
	t_environement	*tmp;

	tmp = an.environement;
	while (tmp)
	{
		if (!ft_strcmp(var, tmp->cle))
		{
			if (c)
			{
				add_val_var_env(tmp, s, i, c);
				
			}
			return (tmp->cle = var, 1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	export_variables(char *str, char c)
{
	int	i;
	char	*var;

	i = 0;
	if (c)
	{
		i = find_equal(str, c);
		var = ft_substr(str, 0, i);
	}
	else
		var = ft_strdup(str);
	if(!search_key_in_env(var, str, i, c))
		export_new_var_in_env(str, var, c, i);
	an.exit_status = 0;
}


void ft_export(t_cmd *cmd)
{
	t_substruct *varr;
	char *var;
	int i;

	varr = cmd->s_substruct->next;
    if(!varr)
        print_environement();
	else
	{
			while (varr)
			{
				
				i = 0;
				var = varr->data;
				while ((*var >= 'a' && *var <= 'z') || (*var >= 'A' && *var <= 'Z') || *var == '_')
				{
					i++;
					var++;
				}
				while (((*var >= 'a' && *var <= 'z') || (*var >= 'A' && *var <= 'Z')
					|| (*var >= '0' && *var <= '9') || *var == '_'))
					var++;
				if (!i || (!(*var == '+' && *(var + 1) == '=') && *var != '=' && *var))
					(ft_putstr_fd("-minishell: export: ",2),ft_putstr_fd(varr->data, 2),ft_putstr_fd(" not a valid identifier\n",2),an.exit_status = 1);
					
				export_variables(varr->data, *var);
				varr = varr->next;
			}
	}
}
