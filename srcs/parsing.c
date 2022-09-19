#include "../include/philosopher.h"

static int is_integer(char *str)
{
    while(*str)
    {
        if (*str < '0' || *str > '9')
            return (0);
        str++;
    }
    return (1);
}

static int check_args(int argc, char **argv)
{
    if (argc < 5 || argc > 6)
        return(printf("Wrong number of arguments.\n"), 0);
    if (!is_integer(argv[1]) || !is_integer(argv[2]) || !is_integer(argv[3])
        || !is_integer(argv[4]))
        return(printf("Wrong type of arguments or negative number.\n"), 0);
    if (atol(argv[1]) <= 0)
        return(printf("Wrong number of philosophers.\n"), 0);
    if (atol(argv[2]) < 0)
        return(printf("Incorrect time to die.\n"), 0);
    if (atol(argv[3]) < 0)
        return(printf("Incorrect time to eat.\n"), 0);
    if (atol(argv[4]) < 0)
        return(printf("Incorrect time to sleep.\n"), 0);
    if (argc == 6)
        if (!is_integer(argv[5]) || (atol(argv[5]) < 0))
            return(printf("Wrong number/type of time each philosopher must eat.\n"), 0);
    return (1);
}


int    parsing(int argc, char **argv, t_stat *stat)
{
    if (!check_args(argc, argv))
        exit(1);
    stat->philo_num = atoi(argv[1]);
    stat->time_to_die = atoi(argv[2]);
    stat->time_to_eat = atoi(argv[3]);
    stat->time_to_sleep = atoi(argv[4]);
    stat->end = 0;
    if (argc == 6)
        stat->number_of_time_each_philosopher_must_eat = atoi(argv[5]);
    else
        stat->number_of_time_each_philosopher_must_eat = -1;
    stat->philos = malloc(stat->philo_num * sizeof(t_philosopher*));
    if (!stat->philos)
        return (printf("Malloc error on philos array.\n"), 0);
    int i = -1;
    while ( ++i < stat->philo_num)
         stat->philos[i] = malloc(sizeof(t_philosopher));
    stat->forks = malloc(stat->philo_num * sizeof(pthread_mutex_t));
    if (!stat->philos)
        return (free(stat->philos), free(stat), printf("Malloc error on forks.\n"), 0);
    return (1);
}