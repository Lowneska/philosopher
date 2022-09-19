#include "../include/philosopher.h"

void init_philo(t_philosopher* philo, int i, t_stat *state)
{
    philo->num = i;
    if ((i % 2) == 0)
       philo->even = 1;
    else
        philo->even = 0;
    philo->last_meal = state->start;
    philo->nb_meals = 0;
    philo->state = state;
}

int init_philosophers(t_stat *state)
{
    int i;

    i = -1;
    state->start = get_time();
    while ( ++i < state->philo_num)
    {
        init_philo((state->philos[i]), i, state);
        if (pthread_mutex_init(&(state->philos[i]->mutex), NULL))
			return (0); //supp tous les philos alloués
        if (pthread_create(&(state->philos[i]->thread), NULL, &routine, state->philos[i]))
		    return (0); //supprimer les philos alloués et les threads crees
    }
    life_checker(state);

	i = -1;
	while (++i < state->philo_num)
		pthread_join(state->philos[i]->thread, NULL);
    //end_of_simulation(state);
    return (1);
}

void		free_philosophers(t_stat *state)
{
	int i;

	i = -1;
	while (++i < state->philo_num)
	{
		pthread_mutex_destroy(&state->forks[i]);
		pthread_mutex_destroy(&state->philos[i]->mutex);
	}
	pthread_mutex_destroy(&state->end_protec);
    pthread_mutex_destroy(&state->display);
}
