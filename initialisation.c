/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 03:35:59 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/19 04:47:32 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long	combien_de_cararctere(long i)
{
	long	count;

	count = 0;
	if (i <= 0)
	{
		count ++;
		i = -1 * i;
	}
	while (i > 0)
	{
		count ++;
		i /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	nombre;
	char	*p;
	long	len;

	nombre = n;
	len = combien_de_cararctere(nombre);
	p = (char *)malloc(len + 1);
	if (!p)
		return (0);
	p[len--] = '\0';
	if (nombre < 0)
	{
		nombre *= -1;
		p[0] = '-';
	}
	if (nombre == 0)
		p[0] = 48;
	while (nombre)
	{
		p[len--] = nombre % 10 + '0';
		nombre /= 10;
	}
	return (p);
}

void	ft_shlvl(char *env, char *cle, char *value)
{
	int		nb;
	char	*tmp;

	tmp = NULL;
	nb = 0;
	if (!ft_strcmp("SHLVL", cle))
	{
		nb = ft_atoi(value);
		if (nb < 0)
			nb = 0;
		else if (nb < 999)
			nb++;
		else if (nb > 999)
			nb = 1;
		tmp = ft_itoa(nb);
		if (nb == 999)
			tmp = ft_strdup("");
		free (value);
		value = ft_strdup(tmp);
		free(tmp);
	}
	lstadd_back_environement(&g_an.environement, \
	creation_node_in_env(ft_strdup(env), cle, value));
}

void	init_environement(char **env)
{
	int		i;
	char	*cle;
	char	*value;

	i = 0;
	g_an.environement = NULL;
	while (*env)
	{
		i = find_equal_or_plus(*env, '=');
		cle = ft_substr(*env, 0, i);
		value = ft_substr(*env, i + 1, ft_strlen(*env) - i);
		ft_shlvl(*env, cle, value);
		env++;
	}
	g_an.pp = getcwd(NULL, PATH_MAX);
	rl_catch_signals = 0;
}
