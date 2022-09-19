#include "../include/philosopher.h"

/*void    end_of_sim_bis(t_stat *state, int i)
{
	pthread_mutex_unlock(&(state->philos[i]->mutex));
    pthread_mutex_lock(&(state->end_protec));
	state->end = 1;
    pthread_mutex_lock(&(state->end_protec));
}
void end_of_simulation(t_stat *state)
{   int i;

    while (1)
    {
        i = -1;
		while (++i < state->philo_num)
		{
            pthread_mutex_lock(&(state->philos[i]->mutex));
            if ((state->number_of_time_each_philosopher_must_eat > 0) && (state->philos[i]->nb_meals >= state->number_of_time_each_philosopher_must_eat))
            {
                print_msg('o', state->philos[i]);
                printf("end : %d et l'autre %d\n",state->philos[i]->nb_meals, state->number_of_time_each_philosopher_must_eat);
                end_of_sim_bis(state, i);
                return ;
            }
			if ((int)(get_time() - state->philos[i]->last_meal) > state->time_to_die)
			{
                print_msg('d', state->philos[i]);
                end_of_sim_bis(state, i);
                return ;
            }
			pthread_mutex_unlock(&(state->philos[i]->mutex));
            usleep(5000);
		}
    }
}*/
int	check_death(t_stat *state, t_philosopher *philo)
{
	if ((int)(get_time() - philo->last_meal) > state->time_to_die)
	{
		pthread_mutex_unlock(&(philo->mutex));
		print_msg('d', philo);
		pthread_mutex_lock(&(state->end_protec));
		state->end = 1;
		pthread_mutex_unlock(&(state->end_protec));
		return (1);
	}
	return (0);
}

int	check_eat(t_stat *state, int all_finished)
{
	if (state->number_of_time_each_philosopher_must_eat > 0 && all_finished)
	{
		pthread_mutex_lock(&(state->end_protec));
		state->end = 1;
		pthread_mutex_unlock(&(state->end_protec));
		return (1);
	}
	return (0);
}

void	life_checker(t_stat	*state)
{
	int		all_finished;
	t_philosopher		*philo;
	int			i;

	while (1)
	{
		all_finished = 1;
		i = -1;
		while (++i < state->philo_num)
		{
			philo = state->philos[i];
			pthread_mutex_lock(&(philo->mutex));
			if (check_death(state, philo))
				return ;
			if (philo->nb_meals < state->number_of_time_each_philosopher_must_eat)
				all_finished = 0;
			pthread_mutex_unlock(&(philo->mutex));
		}
		if (check_eat(state, all_finished))
			return ;
		usleep(5 * 1000);
	}
}
int main(int argc, char **argv)
{
    t_stat *stat;

    stat = malloc(sizeof(t_stat));
    if(!parsing(argc, argv, stat))
        return (0);
    if(!init_mutex(stat))
        return (destroy_mutex(stat), printf("Errors on the mutex init.\n"), 0);
    init_philosophers(stat);
	//start_philosophers(stat);
    //free_philosophers(stat);
    return (1);
}