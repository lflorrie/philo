#include "philo.h"

void	print_info(t_philo_info info)
{
	printf("ph: %i\ndie time: %i\neat time: %i\nsleep time: %i\nmax eat: %i\n",
	 info.philos, info.die_time, info.eat_time, info.sleep_time,
	 info.max_eat);
}

void	*func(void *args)
{
	printf("Philo spawned\n");
	if (args == NULL)
		printf("NULL\n");
	else
		printf("%s\n", (char*)args);
	return (0);
}

void	philo_cycle(t_philo_info info)
{
	int	i;
	pthread_t thread;
	int			status_addr;
	i = 0;
	while (i < info.philos)
	{
		if (pthread_create(&thread, NULL, func, "Kek") != 0)
		{
			printf("Error: thread not created\n");
			return ;
		}
		pthread_join(thread, (void **)&status_addr);
		++i;
	}
}

int	main(int argc, char **argv)
{
	t_philo_info info;

	if (argc == 5 || argc == 6)
	{
		info = parser(argc, argv);
		print_info(info);
		philo_cycle(info);
	}
	return (0);
}
