/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:02:39 by skhali            #+#    #+#             */
/*   Updated: 2022/09/21 07:10:13 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static int	init_forks(t_stat *stat)
{
	int	i;

	i = 0;
	while (i < stat->philo_num)
	{
		if (pthread_mutex_init(&(stat->forks[i]), NULL) != 0)
		{
			while (i > 0)
			{
				pthread_mutex_destroy(&(stat->forks[i - 1]));
				i--;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

static int	init_philomutex(t_stat *stat)
{
	int	i;

	i = 0;
	while (i < stat->philo_num)
	{
		if (pthread_mutex_init(&(stat->philos[i]->mutex), NULL) != 0)
		{
			while (i > 0)
			{
				pthread_mutex_destroy(&(stat->philos[i - 1]->mutex));
				i--;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

void	destroy_mutex_s(t_stat *stat, int i)
{
	int	r;

	r = i - 1;
	while (r >= 0)
	{
		pthread_mutex_destroy(&(stat->philos[r]->mutex));
		r--;
	}
}

void	destroy_forks(t_stat *stat, int i)
{
	int	r;

	r = i - 1;
	while (r >= 0)
	{
		pthread_mutex_destroy(&(stat->forks[r]));
		r--;
	}
}

void	destroy_mutex(t_stat *stat)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&(stat->display));
	pthread_mutex_destroy(&(stat->end_protec));
	destroy_forks(stat, stat->philo_num);
	free(stat->forks);
	while (i < stat->philo_num)
	{
		pthread_mutex_destroy(&(stat->philos[i]->mutex));
		i++;
	}
}

int	init_mutex(t_stat *stat)
{
	if (pthread_mutex_init(&(stat->display), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(stat->end_protec), NULL) != 0)
		return (pthread_mutex_destroy(&(stat->display)), 0);
	if (!init_forks(stat))
	{
		pthread_mutex_destroy(&(stat->display));
		pthread_mutex_destroy(&(stat->end_protec));
		return (0);
	}
	if (!init_philomutex(stat))
	{
		pthread_mutex_destroy(&(stat->display));
		pthread_mutex_destroy(&(stat->end_protec));
		destroy_forks(stat, stat->philo_num);
		return (0);
	}
	return (1);
}
