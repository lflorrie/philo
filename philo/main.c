#include "philo.h"

void	print_info(t_philo_info info)
{
	printf("ph: %i\ndie time: %i\neat time: %i\nsleep time: %i\nmax eat: %i\n",
	 info.philos, info.die_time, info.eat_time, info.sleep_time,
	 info.max_eat);
}

int	main(int argc, char **argv)
{
	t_philo_info info;

	if (argc == 5 || argc == 6)
	{
		info = parser(argc, argv);
		print_info(info);
	}
	return (0);
}
