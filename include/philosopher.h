/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:51:42 by skhali            #+#    #+#             */
/*   Updated: 2022/09/23 17:23:09 by skhali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdint.h>
# include <limits.h>

typedef struct s_stat	t_stat;

typedef struct s_philosopher
{
	int					num;
	int					even;
	uint64_t			last_meal;
	int					nb_meals;
	pthread_t			thread;
	pthread_mutex_t		mutex;
	t_stat				*state;
}						t_philosopher;

typedef struct s_stat
{
	int					philo_num;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_time_each_philosopher_must_eat;
	uint64_t			start;
	int					end;
	pthread_mutex_t		end_protec;
	pthread_mutex_t		display;
	t_philosopher		**philos;
	pthread_mutex_t		*forks;
}						t_stat;

/* Parsing */
int			parsing(int argc, char **argv, t_stat *stat);
void		free_philos(t_stat *state, int i);

/* Initialisation et destruction des mutex*/
int			init_mutex(t_stat *stat);
void		destroy_mutex(t_stat *stat);
void		destroy_mutex_s(t_stat *stat, int i);
void		destroy_forks(t_stat *stat, int i);

/* Initialisation des philosophes et début de la simulation */
int			init_philosophers(t_stat *state);
void		free_philos(t_stat *state, int i);

/* Display des statuts sur le terminal et calcul du temps*/
uint64_t	get_time(void);
void		print_msg(int type, t_philosopher *philo);
void		*routine(void	*philoo);

void		life_checker(t_stat	*state);
int			end_of_simulation(t_stat *state);
int			init_philosophers(t_stat *state);
void		ft_swap(int *a, int *b);

int			check_death(t_philosopher *philo);
int			alloc_philos(t_stat *stat);
#endif