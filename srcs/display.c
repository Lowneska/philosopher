#include "../include/philosopher.h"

uint64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	print_msg(int type, t_philosopher *philo)
{
	char *time;

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