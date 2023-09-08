/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:34:27 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/06 23:32:38 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*---check_file-----*/
int	ft_check_fils(char *name_fd, int mode, int permession)
{
	int	fl;

	fl = 0;
	if (access(name_fd, F_OK) == -1 || access(name_fd, R_OK) == -1
		|| access(name_fd, W_OK) == -1)
	{
		if (mode == (O_RDWR | O_CREAT | O_TRUNC)
			|| mode == (O_RDWR | O_CREAT | O_APPEND))
		{
			if (permession)
			{
				fl = open(name_fd, mode, permession);
				if (fl == -1)
				{
					an.exit_status = 1;
					perror("open");
				}
			}
		}
	}
	else
	{
		fl = open(name_fd, mode);
		if (fl == -1)
		{
			an.exit_status = 1;
			perror("open");		
		}
	}
	return (fl);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*dst;
	unsigned char	*sr;

	i = 0;
	dst = (unsigned char *)s1;
	sr = (unsigned char *)s2;
	while (((dst[i] != '\0') || (sr[i] != '\0')) && i < n)
	{
		if (dst[i] < sr[i])
			return (-1);
		else if (dst[i] > sr[i])
			return (1);
		i++;
	}
	return (0);
}
