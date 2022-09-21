/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:08:45 by skhali            #+#    #+#             */
/*   Updated: 2022/09/21 06:55:16 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

uint64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

int	main(int argc, char **argv)
{
	t_stat	*stat;

	stat = malloc(sizeof(t_stat));
	if (!parsing(argc, argv, stat))
		return (0);
	if (!init_mutex(stat))
		return (free_philos(stat, stat->philo_num),
			write( 1, "Errors on the mutex init.\n", 27), 0);
	init_philosophers(stat);
	return (1);
}
