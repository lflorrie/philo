#include "philo.h"

void	print_info(t_philo_info info)
{
	printf("ph: %i\ndie time: %i\neat time: %i\nsleep time: %i\nmax eat: %i\n",
	 info.philos, info.die_time, info.eat_time, info.sleep_time,
	 info.max_eat);
}

void	*func(void *args)
{
	printf("Philo spawned ");
	if (args == NULL)
		printf("NULL\n");
	else
		printf("%i\n", *(int*)args);
	return (args);
}

t_philo	*create_philosophers(int n)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * n);
	i = 0;
	while (i < n)
	{
		philos[i].num = i;
		if (pthread_create(&(philos->thread), NULL, func, &philos[i].num) != 0)
		{
			printf("Error: thread not created\n");
			free(philos);
			return (NULL);
		}
		pthread_detach(philos[i].thread);
		// pthread_join(philos[i].thread, NULL);
		++i;
	}
	return (philos);
}

void	delete_philosophers(t_philo_info info,t_philo *philos)
{
	int	i;

	i = 0;
	while (i < info.philos)
	{
		++i;
	}
	free(philos);
}

int	philo_cycle(t_philo_info info)
{
	t_philo *philos;
	int		i;

	i = 0;
	philos = create_philosophers(info.philos);
	if (philos == NULL)
		return (printf("Error: philos == NULL\n") + 1);
	while (i < philos->num)
	{
		// pthread_join(philos[i].thread, NULL);
		++i;
	}
	usleep(100);
	// delete_philosophers(info, philos);	
	return (0);
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
