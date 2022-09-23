/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:08:45 by skhali            #+#    #+#             */
/*   Updated: 2022/09/23 17:22:56 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

uint64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
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

void	free_philos(t_stat *state, int i)
{
	int	r;

	r = i - 1;
	while (r >= 0)
	{
		free(state->philos[r]);
		r--;
	}
	free(state->philos);
	free(state);
}

int	alloc_philos(t_stat *stat)
{
	int	i;

	stat->philos = malloc(stat->philo_num * sizeof(t_philosopher *));
	if (!stat->philos)
		return (free(stat), write(1, "Malloc error on philos array.\n", 30), 0);
	i = -1;
	while (++i < stat->philo_num)
	{
		stat->philos[i] = malloc(sizeof(t_philosopher));
		if (!stat->philos[i])
			return (free_philos(stat, i), 0);
	}
	stat->forks = malloc(stat->philo_num * sizeof(pthread_mutex_t));
	if (!stat->philos)
		return (free_philos(stat, i), write(1, "Malloc error on forks.\n", 23)
			, 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_stat	*stat;

	stat = malloc(sizeof(t_stat));
	if (!parsing(argc, argv, stat))
		return (0);
	if (!alloc_philos(stat))
		return (0);
	if (!init_mutex(stat))
		return (free_philos(stat, stat->philo_num),
			write(1, "Errors on the mutex init.\n", 27), 0);
	init_philosophers(stat);
	return (1);
}
