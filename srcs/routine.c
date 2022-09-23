/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:07:13 by skhali            #+#    #+#             */
/*   Updated: 2022/09/23 17:09:32 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	take_forks(t_philosopher *philo, int id1, int id2)
{
	if (philo->num == ((philo->num + 1)
			% philo->state->philo_num))
		return (print_msg('f', philo),
			usleep(philo->state->time_to_die * 1000), 0);
	pthread_mutex_lock(&(philo->state->forks[id1]));
	if (check_death(philo))
	{
		pthread_mutex_unlock(&(philo->state->forks[id1]));
		return (0);
	}
	print_msg('f', philo);
	if (check_death(philo))
	{
		pthread_mutex_unlock(&(philo->state->forks[id1]));
		return (0);
	}
	pthread_mutex_lock(&philo->state->forks[id2]);
	if (check_death(philo))
	{
		pthread_mutex_unlock(&philo->state->forks[id2]);
		pthread_mutex_unlock(&(philo->state->forks[id1]));
		return (0);
	}
	print_msg('f', philo);
	return (1);
}

int	eat(t_philosopher *philo, int id1, int id2)
{
	print_msg('e', philo);
	usleep(1000 * philo->state->time_to_eat);
	if (check_death(philo))
	{
		pthread_mutex_unlock(&philo->state->forks[id2]);
		pthread_mutex_unlock(&(philo->state->forks[id1]));
		return (0);
	}
	pthread_mutex_lock(&philo->mutex);
	philo->last_meal = get_time();
	philo->nb_meals++;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&(philo->state->forks[id1]));
	pthread_mutex_unlock(&(philo->state->forks[id2]));
	if (check_death(philo))
		return (0);
	return (1);
}

void	sleeper(t_philosopher *philo)
{
	print_msg('s', philo);
	usleep(philo->state->time_to_sleep * 1000);
}

void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	*routine(void	*param)
{
	t_philosopher	*philo;
	int				id1;
	int				id2;

	philo = (t_philosopher *) param;
	id1 = philo->num;
	id2 = (philo->num + 1)
		% philo->state->philo_num;
	if (id1 == 0)
		ft_swap(&id1, &id2);
	if (!philo->even)
		usleep(philo->state->time_to_eat * 200);
	while (!check_death(philo))
	{
		if (!take_forks(philo, id1, id2))
			return (NULL);
		if (!eat(philo, id1, id2))
			return (NULL);
		sleeper(philo);
		if (check_death(philo))
			return (NULL);
		print_msg('t', philo);
	}
	return (NULL);
}
