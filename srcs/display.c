/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:52:10 by skhali            #+#    #+#             */
/*   Updated: 2022/09/20 13:58:00 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	ft_size(int n)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = n;
	if (n == 0)
		return (1);
	if (tmp < 0)
		i++;
	while (tmp)
	{
		tmp = tmp / 10;
		i++;
	}
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t size)
{
	char			*d;
	const char		*s;
	unsigned int	i;

	d = dst;
	s = src;
	i = 0;
	while (i < size)
	{
		*d++ = *s++;
		i++;
	}
	return (dst);
}

char	*ft_itoa(int n)
{
	int		tmp;
	char	*c;
	int		size;

	tmp = n;
	size = ft_size(n);
	c = (char *)malloc(sizeof(char) * (size + 1));
	if (!c)
		return (NULL);
	if (tmp == -2147483648)
		return (ft_memcpy(c, "-2147483648", size + 1));
	if (n == 0)
		return (ft_memcpy(c, "0", 2));
	if (n < 0)
	{
		c[0] = '-';
		tmp *= -1;
	}
	c[size--] = '\0';
	while (tmp)
	{
		c[size--] = '0' + (tmp % 10);
		tmp = tmp / 10;
	}
	return (c);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	print_msg(int type, t_philosopher *philo)
{
	char	*time;

	pthread_mutex_lock(&(philo->state->display));
	time = ft_itoa((int)(get_time() - philo->state->start));
	write(1, time, ft_strlen(time));
	write(1, " ", 1);
	free(time);
	time = ft_itoa(philo->num + 1);
	write(1, time, ft_strlen(time));
	free(time);
	if (type == 'f')
		write(1, " has taken a fork.\n", 19);
	else if (type == 'e')
		write(1, " is eating.\n", 12);
	else if (type == 's')
		write(1, " is sleeping.\n", 14);
	else if (type == 't')
		write(1, " is thinking.\n", 14);
	else if (type == 'd')
		write(1, " died.\n", 7);
	pthread_mutex_unlock(&(philo->state->display));
}
