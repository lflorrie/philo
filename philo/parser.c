#include "philo.h"

t_philo_info	parser(int argc, char **argv)
{
	t_philo_info	info;

	info.philos = atoi(argv[1]); // ft_atoi
	info.die_time = atoi(argv[2]); // ft_atoi
	info.eat_time = atoi(argv[3]); // ft_atoi
	info.sleep_time = atoi(argv[4]); // ft_atoi
	if (argc == 6)
		info.max_eat = atoi(argv[5]); // ft_atoi
	else
		info.max_eat = 0;
	return (info);
}