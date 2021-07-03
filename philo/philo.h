#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_philo_info
{
	int			philos;
	int			die_time;
	int			eat_time;
	int			sleep_time;
	int			max_eat;
}				t_philo_info;



t_philo_info	parser(int argc, char **argv);

#endif
