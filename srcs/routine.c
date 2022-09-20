/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:07:13 by skhali            #+#    #+#             */
/*   Updated: 2022/09/20 14:08:29 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	take_forks(t_philosopher *philo)
{
	if (philo->num == ((philo->num + 1)
			% philo->state->philo_num))
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
	pthread_mutex_lock(&philo->state->forks[(philo->num + 1)
		% philo->state->philo_num]);
	if (philo->state->end)
	{
		pthread_mutex_unlock(&(philo->state->forks[philo->num]));
		pthread_mutex_unlock(&philo->state->forks[(philo->num + 1)
			% philo->state->philo_num]);
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
		pthread_mutex_unlock(&philo->state->forks[(philo->num + 1)
			% philo->state->philo_num]);
		return (0);
	}
	pthread_mutex_lock(&philo->mutex);
	philo->last_meal = get_time();
	philo->nb_meals++;
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&(philo->state->forks[philo->num]));
	pthread_mutex_unlock(&(philo->state->forks[(philo->num + 1)
			% philo->state->philo_num]));
	if (philo->state->end)
		return (0);
	return (1);
}

void	sleeper(t_philosopher *philo)
{
	print_msg('s', philo);
	usleep(philo->state->time_to_sleep * 1000);
}

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
