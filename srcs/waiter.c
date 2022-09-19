#include "../include/philosopher.h"

int			check_meal(t_stat *state)
{
	int i;

	i = -1;
	while (++i < state->philo_num)
	{
		if (state->philos[i]->nb_meals <
		state->number_of_time_each_philosopher_must_eat)
			return (0);
	}
	return (1);
}

void    end_of_sim_bis(t_philosopher *philo)
{
	pthread_mutex_unlock(&(philo->mutex));
    pthread_mutex_lock(&(philo->state->end_protec));
	philo->state->end = 1;
    pthread_mutex_unlock(&(philo->state->end_protec));
}

void end_of_simulation(t_stat *state)
{   int i;

    while (1)
    {
        i = -1;
		while (++i < state->philo_num)
		{
            if ((state->number_of_time_each_philosopher_must_eat > 0) && check_meal(state))
		    {
                end_of_sim_bis(state->philos[i]);
                return ;
		    }
            pthread_mutex_lock(&(state->philos[i]->mutex));
            if ((int)(get_time() - state->philos[i]->last_meal) > state->time_to_die)
			{
                print_msg('d', state->philos[i]);
                end_of_sim_bis(state->philos[i]);
                return ;
            }
			pthread_mutex_unlock(&(state->philos[i]->mutex));
		}
        usleep(5000);
    }
}