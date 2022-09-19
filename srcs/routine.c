#include "../include/philosopher.h"


int	take_forks(t_philosopher *philo)
{
    if (philo->num == ((philo->num + 1) %
			philo->state->philo_num))
	{
		print_msg('f', philo);
		usleep(philo->state->time_to_die * 1000);
		return (0);
	}
	pthread_mutex_lock(&(philo->state->forks[philo->num]));
	print_msg('f', philo);
	if (philo->state->end)
	{
		pthread_mutex_unlock(&(philo->state->forks[philo->num]));
		return (0);
	}
	pthread_mutex_lock(&philo->state->forks[(philo->num + 1) %
			philo->state->philo_num]);
	if (philo->state->end)
	{
		pthread_mutex_unlock(&(philo->state->forks[philo->num]));
        pthread_mutex_unlock(&philo->state->forks[(philo->num + 1) %
			philo->state->philo_num]);
        return (0);
	}
	print_msg('f', philo);
    return (1);
}

int	eat(t_philosopher *philo)
{
    print_msg('e', philo);
    usleep(1000 * philo->state->time_to_eat);
    if (philo->state->end)
	{
		pthread_mutex_unlock(&(philo->state->forks[philo->num]));
        pthread_mutex_unlock(&philo->state->forks[(philo->num + 1) %
			philo->state->philo_num]);
        return (0);
	}
	pthread_mutex_lock(&philo->mutex);
	philo->last_meal = get_time();
	philo->nb_meals++;
	pthread_mutex_unlock(&philo->mutex);
    pthread_mutex_unlock(&(philo->state->forks[philo->num]));
	pthread_mutex_unlock(&(philo->state->forks[(philo->num + 1) %
			philo->state->philo_num]));
    if (philo->state->end)
        return (0);
    return (1);
}
void	sleeper(t_philosopher *philo)
{
	print_msg('s', philo);
	usleep(philo->state->time_to_sleep * 1000);
}
/*int philo_start_eat(t_philosopher *philo, int fork1, int fork2)
{
	if (fork1 == fork2)
	{
		print_msg('f', philo);
		usleep(philo->state->time_to_die * 1000);
		return (1);
	}
	pthread_mutex_lock(&(philo->state->forks[fork1]));
    print_msg('f', philo);
	if (philo->state->end)
	{
		pthread_mutex_unlock(&(philo->state->forks[fork1]));
		return (1);
	}
	pthread_mutex_lock(&(philo->state->forks[fork2]));
	if (philo->state->end)
	{
		pthread_mutex_unlock(&(philo->state->forks[fork2]));
		pthread_mutex_unlock(&(philo->state->forks[fork1]));
		return (1);
	}
	print_msg('f', philo);
	return (0);
}
int	philo_eat(t_philosopher *philo, int fork1, int fork2)
{
    print_msg('e', philo);
	usleep(philo->state->time_to_eat * 1000);
	if (philo->state->end)
	{
		pthread_mutex_unlock(&(philo->state->forks[fork2]));
		pthread_mutex_unlock(&(philo->state->forks[fork1]));
		return (1);
	}
	pthread_mutex_lock(&(philo->mutex));
	philo->last_meal = get_time();
	(philo->nb_meals)++;
	pthread_mutex_unlock(&(philo->mutex));
	pthread_mutex_unlock(&(philo->state->forks[fork1]));
	pthread_mutex_unlock(&(philo->state->forks[fork2]));
	if (philo->state->end)
		return (1);
	return (0);
}*/
/*void	*routine(void	*philoo)
{
    t_philosopher *philo;

    philo = (t_philosopher *)philoo;
    if (!philo->even)
        usleep(philo->state->time_to_eat * 1000);
    while (!philo->state->end)
    {
        //take_forks(philo);
        if (!take_forks(philo))
            return (NULL);
        //eat(philo);
        if (!eat(philo))
            return (NULL);
        if (philo_start_eat(philo, philo->num, (philo->num + 1) %
			philo->state->philo_num))
			return (NULL);
		if (philo_eat(philo, philo->num, (philo->num + 1) %
			philo->state->philo_num))
			return (NULL);
        sleeper(philo);
        if (philo->state->end)
            return (NULL);
        print_msg('t', philo);
    }
    return (NULL);
}*/

/*void	choose_forks(t_philosopher *philo, int *fork1, int *fork2)
{
	int	tmp_fork;

	*fork1 = philo->num;
	*fork2 = philo->num - 1;
	if (*fork2 < 0)
		*fork2 = philo->state->philo_num - 1;
	if (*fork1 < *fork2)
	{
		tmp_fork = *fork1;
		*fork1 = *fork2;
		*fork2 = tmp_fork;
	}
}*/

void	*routine(void	*param)
{
	t_philosopher	*philo;

	philo = (t_philosopher *) param;
	if (!philo->even)
		usleep(philo->state->time_to_eat * 1000);
	while (!philo->state->end)
	{
		if (!take_forks(philo))
			return (NULL);
        if (!eat(philo))
			return (NULL);
        sleeper(philo);
		if (philo->state->end)
			return (NULL);
		print_msg('t', philo);
	}
	return (NULL);
}