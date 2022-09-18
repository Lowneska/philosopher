#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdint.h>

typedef struct			s_stat t_stat;

typedef struct			s_philosopher
{
	int					num;
	int					even;
	uint64_t 			last_meal;
	int					nb_meals;
	pthread_t			thread;
	pthread_mutex_t		mutex;
	t_stat				*state;
}						t_philosopher;

typedef struct			s_stat
{
	int 				philo_num;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_time_each_philosopher_must_eat;
	uint64_t			start;
	int					end;
	pthread_mutex_t		end_protec;
	pthread_mutex_t		display;
	t_philosopher		*philos;
	pthread_mutex_t		*forks;
}						t_stat;



/* Parsing */
int    		parsing(int argc, char **argv, t_stat *stat);

/* Initialisation et destruction des mutex*/
int			init_mutex(t_stat *stat);
void   	 	destroy_mutex(t_stat *stat);

/* Initialisation des philosophes et début de la simulation */
int 		init_philosophers(t_stat *state);
void		free_philosophers(t_stat *state);

/* Display des statuts sur le terminal et calcul du temps*/
uint64_t	get_time(void);
void		print_msg(int type, t_philosopher *philo);
void		*routine(void	*philoo);

#endif