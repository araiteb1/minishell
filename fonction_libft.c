/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_libft.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:45:15 by araiteb           #+#    #+#             */
/*   Updated: 2023/08/03 08:43:28 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*-------strlen-----*/
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*-----mmecpy------*/
void	*ft_memcpy(const void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if (dst || src)
	{
		d = (unsigned char *)dst;
		s = (unsigned char *)src;
		i = 0;
		if (d == s || n == 0)
			return (d);
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
		return (d);
	}
	return (NULL);
}

/*---join----*/
char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	l1;
	size_t	l2;

	if (!s1 || !s2)
		return (NULL);
	l2 = ft_strlen(s2);
	l1 = ft_strlen(s1);
	new = (char *)malloc((l1 + l2 + 1) * sizeof(char));
	if (!new)
		return (0);
	ft_memcpy(new, s1, l1);
	ft_memcpy((new + l1), s2, l2);
	new[l1 + l2] = '\0';
	return (new);
}

/*-------strdup-------*/
char	*ft_strdup(const char *s)
{
	char	*tp;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(s);
	tp = (char *)malloc((len + 1) * sizeof(char));
	if (!tp)
		return (NULL);
	while (*s)
		tp[i++] = *s++;
	tp[i] = '\0';
	return (tp);
}

/*--substr----*/
char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	lens;

	if (!s)
		return (NULL);
	lens = ft_strlen(s);
	if (start >= lens || len == 0)
		return (ft_strdup(" "));
	if ((start + len) >= lens)
	{
		new = (char *)malloc(((lens - start) + 1) * sizeof(char));
		if (!new)
			return (0);
		ft_memcpy(new, (s + start), lens - start + 1);
		new[lens - start] = '\0';
		return (new);
	}
	new = (char *)malloc((len + 1) * sizeof(char));
	if (!new)
		return (0);
	ft_memcpy(new, (s + start), len);
	new[len] = '\0';
	return (new);
}
