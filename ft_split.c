/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 10:42:54 by araiteb           #+#    #+#             */
/*   Updated: 2023/07/31 08:26:08 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*----split------*/
static int	ft_num_case(const char *s, char c)
{
	int	num;

	num = 0;
	while (*s)
	{
		while (*s && (*s == c))
			s++;
		if (!(*s))
			return (num);
		while (*s && (*s != c))
			s++;
		num++;
	}
	return (num);
}

static char	*ft_alloc_case(const char *s, char c, int *j)
{
	char	*cases;
	int		i;
	int		len;

	while (s[*j] && s[*j] == c)
		(*j)++;
	len = 0;
	while (s[*j] && s[(*j) + len] && s[(*j) + len] != c)
		len++;
	cases = malloc((len + 1) * sizeof(char));
	if (!cases)
		return (NULL);
	i = 0;
	while (s[*j] && s[*j] != c)
	{
		cases[i] = s[*j];
		(*j)++;
		i++;
	}
	cases[i] = '\0';
	return (cases);
}

char	**ft_split(const char *s, char c)
{
	int		n;
	int		i;
	int		j;
	char	**str;

	if (!s)
		return (NULL);
	n = ft_num_case(s, c);
	str = (char **)malloc((n + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < n)
	{
		str[i] = ft_alloc_case(s, c, &j);
		if (!str[i])
		{
			ft_free(str);
			return (NULL);
		}
		i++;
	}
	str[i] = NULL;
	return (str);
}
