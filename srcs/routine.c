#include "../include/philosopher.h"

int	take_forks(t_philosopher *philo)
{
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
        pthread_mutex_lock(&philo->state->forks[(philo->num + 1) %
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
        pthread_mutex_lock(&philo->state->forks[(philo->num + 1) %
			philo->state->philo_num]);
        return (0);
	}
	pthread_mutex_lock(&philo->mutex);
	philo->last_meal = get_time();
	++philo->nb_meals;
	pthread_mutex_unlock(&philo->mutex);
    pthread_mutex_unlock(&(philo->state->forks[philo->num]));
	pthread_mutex_unlock(&(philo->state->forks[(philo->num + 1) %
			philo->state->philo_num]));
    if (philo->state->end)
        return (0);
    return (1);
}

void	sleep(t_philosopher *philo)
{
	print_msg('s', philo);
	usleep(philo->state->time_to_sleep);
}

void	*routine(void	*philoo)
{
    t_philosopher *philo;

    philo = (t_philosopher *)philoo;
    if (!philo->even)
        usleep(philo->state->time_to_eat * 1000);

    //Prendre une fourchette
    //Prendre la deuxième fourchette
    if (!philo->state->end)
        take_forks(philo);
    //Commencer à manger
    if (!philo->state->end)
        eat(philo);
    if (!philo->state->end)
        sleep(philo);
    print_msg('t', philo);
    return (NULL);
}