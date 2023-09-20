/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:40:46 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/20 06:02:37 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ret_expand_val(char *str, char **env)
{
	int		i;
	char	*value;

	value = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, ft_size_nam(env[i], '=')))
			i++;
		else
			break ;
	}
	if (env[i])
		value = ft_substr(env[i], \
				(ft_size_nam(env[i], '=') + 1), ft_strlen(env[i]));
	return (value);
}

void	get_sizexp(char *line, int *i, t_expand *exp)
{
	exp->size = 0;
	while (line[*i] && line[*i] != '$')
	{
		exp->size++;
		(*i)++;
	}
}

char	*check_valu_exp(t_expand *exp, char **env)
{
	char	*tmp;

	tmp = NULL;
	exp->value = NULL;
	exp->str = NULL;
	if (!ft_strncmp(exp->ret1, "?", ft_strlen(exp->ret1)))
	{
		exp->str = ft_itoa(g_an.exit_status);
		return (exp->str);
	}
	if (exp->ret1 && !check_doll(exp->ret1, '$'))
	{
		exp->value = ret_expand_val(exp->ret1, env);
		tmp = exp->str;
		exp->str = ft_strjoin(exp->ret, exp->value);
		ft_free_str(exp->value);
		exp->value = exp->str;
		exp->str = ft_strjoin(tmp, exp->value);
		ft_free_str (exp->value);
		ft_free_str(tmp);
	}
	return (exp->str);
}

char	*option_expand(char *line, char **env)
{
	int			i;
	t_expand	*exp;
	char		*tmp;

	i = 0;
	exp = (t_expand *)malloc(sizeof(t_expand));
	if (!exp)
		return (NULL);
	tmp = NULL;
	while (line && line[i])
	{
		exp->ret = NULL;
		exp->ret1 = NULL;
		exp->start = i;
		get_sizexp(line, &i, exp);
		i++;
		if (exp->size > 0)
			exp->ret = ft_substr(line, exp->start, exp->size);
		exp->start = i;
		get_sizexp(line, &i, exp);
		exp->ret1 = ft_substr(line, exp->start, exp->size);
		exp->str = check_valu_exp(exp, env);
		ft_free_str(exp->ret);
		ft_free_str(exp->ret1);
	}
	tmp = ft_strtrim(exp->str, " ");
	ft_free_str (exp->str);
	free(exp);
	return (tmp);
}

void	expand_env_variable(char **option, char **env)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	while (option && option[i])
	{
		str = ft_strdup(option[i]);
		if (check_doll(str, '$') == 1)
		{
			ft_free_str (option[i]);
			option[i] = option_expand(str, env);
		}
		ft_free_str(str);
		i++;
	}
}
