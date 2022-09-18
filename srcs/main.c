#include "../include/philosopher.h"

int main(int argc, char **argv)
{
    t_stat *stat;
    stat = malloc(sizeof(t_stat));
    if(!parsing(argc, argv, stat))
        return (0);
    if(!init_mutex(stat))
        return (destroy_mutex(stat), printf("Errors on the mutex init.\n"), 0);
    init_philosophers(stat);
    free_philosophers(stat);
    return (1);
}