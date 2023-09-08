#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*ch;

	ch = (unsigned char *)s;
	while (*ch != (char)c)
	{
		if (*ch == '\0')
		{
			return (NULL);
		}
		ch++;
	}
	return ((char *)ch);
}

int	ft_atoi(const char *str)
{
	long long	res;
	long long	n;
	int			sign;

	res = 0;
	sign = 1;
	// while (*str == 32 || (*str >= 9 && *str <= 13))
	// 	str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		n = res;
		res = res * 10 + (*str - 48);
		if (n != res / 10 && sign == 1)
			return (-1);
		else if (n != res / 10 && sign == -1)
			return (0);
		str++;
	}
	return (res * sign);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s || fd < 0)
		return ((void)0);
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}