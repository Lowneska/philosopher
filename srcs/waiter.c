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
int	check_death(t_philosopher *philo)
{
	int i;
	pthread_mutex_lock(&(philo->state->end_protec));
	i = philo->state->end;
    pthread_mutex_unlock(&(philo->state->end_protec));
	return (i);
}
void    end_of_sim_bis(t_philosopher *philo)
{
	pthread_mutex_unlock(&(philo->mutex));
    pthread_mutex_lock(&(philo->state->end_protec));
	philo->state->end = 1;
    pthread_mutex_unlock(&(philo->state->end_protec));
}

void    end_of_sim_bis2(t_stat *state)
{
    pthread_mutex_lock(&(state->end_protec));
	state->end = 1;
    pthread_mutex_unlock(&(state->end_protec));
}
void end_of_simulation(t_stat *state)
{   int i;
	int end;

	end = 1;
    while (1)
    {
        i = -1;
		while (++i < state->philo_num)
		{
			pthread_mutex_lock(&(state->philos[i]->mutex));
			if ((state->number_of_time_each_philosopher_must_eat > 0) && (state->philos[i]->nb_meals >= state->number_of_time_each_philosopher_must_eat))
				end++;
            if ((int)(get_time() - state->philos[i]->last_meal) > state->time_to_die)
			{
                end_of_sim_bis(state->philos[i]);
				usleep(5000);
				print_msg('d', state->philos[i]);
                return ;
            }
			pthread_mutex_unlock(&(state->philos[i]->mutex));
		}
		if ((state->number_of_time_each_philosopher_must_eat > 0) && (end == state->philo_num))
	    {
            end_of_sim_bis2(state);
            return ;
		}
    }
}