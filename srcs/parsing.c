/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:04:42 by skhali            #+#    #+#             */
/*   Updated: 2022/09/22 14:58:42 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static int		ft_atoi(const char *str)
{
	int		sign;
	int		somme;
	
	sign = 1;
	somme = 0;
	while (*str == '\t' || *str == '\n' || *str == '\f' || *str == '\r' ||
		*str == ' ' || *str == '\v')
		str++;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9')
	{
		somme = (somme * 10) + (*str - '0');
		str++;
	}
	return (somme * sign);
}

static long	ft_atol(const char *str)
{
	int	signe;
	long	nbr;

	nbr = 0;
	signe = 1;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (str[1] == '+' || str[1] == '-')
			return (0);
		if (*str++ == '-')
			signe = -1;
	}
	while (*str >= '0' && *str <= '9')
		nbr = (nbr * 10) + (*str++ - '0');
	return (nbr * signe);
}

static int	is_integer(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
	if (ft_atol(str) < INT_MIN || ft_atol(str) > INT_MAX)
		return (0);
	return (1);
}

static int	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (write( 1,"Wrong number of arguments.\n", 27), 0);
	if (!is_integer(argv[1]) || !is_integer(argv[2]) || !is_integer(argv[3])
		|| !is_integer(argv[4]))
		return (write( 1,"Wrong type of arguments or negative number.\n", 44), 0);
	if (ft_atoi(argv[1]) <= 0)
		return (write( 1,"Wrong number of philosophers.\n", 30), 0);
	if (ft_atoi(argv[2]) < 0)
		return (write( 1,"Incorrect time to die.\n", 23), 0);
	if (ft_atoi(argv[3]) < 0)
		return (write( 1,"Incorrect time to eat.\n", 23), 0);
	if (ft_atoi(argv[4]) < 0)
		return (write( 1,"Incorrect time to sleep.\n", 25), 0);
	if (argc == 6)
		if (!is_integer(argv[5]) || (ft_atoi(argv[5]) <= 0))
			return (write( 1,"Wrong n/t of time each philo must eat.\n", 39), 0);
	return (1);
}
void	free_philos(t_stat *state, int i)
{
	int	r;

	r = i - 1;
	while ( r >= 0)
	{
		free(state->philos[r]);
		r--;
	}
	free(state->philos);
	free(state);
}
int	parsing(int argc, char **argv, t_stat *stat)
{
	int	i;

	if (!check_args(argc, argv))
		return (free(stat), 0);
	stat->philo_num = ft_atoi(argv[1]);
	stat->time_to_die = ft_atoi(argv[2]);
	stat->time_to_eat = ft_atoi(argv[3]);
	stat->time_to_sleep = ft_atoi(argv[4]);
	stat->end = 0;
	if (argc == 6)
		stat->number_of_time_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		stat->number_of_time_each_philosopher_must_eat = -1;
	stat->philos = malloc(stat->philo_num * sizeof(t_philosopher *));
	if (!stat->philos)
		return (free(stat), write( 1,"Malloc error on philos array.\n", 30), 0);
	i = -1;
	while (++i < stat->philo_num)
	{
		stat->philos[i] = malloc(sizeof(t_philosopher));
		if (!stat->philos[i])
			return (free_philos(stat, i), 0);
	}
	stat->forks = malloc(stat->philo_num * sizeof(pthread_mutex_t));
	if (!stat->philos)
		return (free_philos(stat, i), write( 1,"Malloc error on forks.\n", 23), 0);
	return (1);
}
