#include "philo.h"
#include <time.h>
#include <sys/time.h>
void	print_info(t_philo_info info)
{
	printf("ph: %i\ndie time: %i\neat time: %i\nsleep time: %i\nmax eat: %i\n",
	 info.philos, info.die_time, info.eat_time, info.sleep_time,
	 info.max_eat);
}

int	check_life_time(t_philo *philo, struct timeval start)
{
	struct timeval stop;
	
	gettimeofday(&stop, NULL);
	if (philo->info->die_time <= (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)
	{
		printf("philo->info->die_time = %i\n", philo->info->die_time);
		printf("-----TIME: die time = %i <= %ld time ------\n", philo->info->die_time, (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
		return (1);
	}
	return (0);
}

void	*func(void *args)
{
	struct timeval start;
	t_philo		*philo;

	philo = (t_philo *)args;
	gettimeofday(&start, NULL);
	printf("Philo spawned ");
	if (args == NULL)
		printf("NULL\n");
	else
		printf("%i\n", philo->num);
	while (1)
	{
		if (check_life_time(philo, start))
		{
			printf("philo %i dead\n", philo->num);
			return (NULL);
		}
	}
	return (args);
}

t_philo	*create_philosophers(t_philo_info *info)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * info->philos);
	i = 0;
	while (i < info->philos)
	{
		philos[i].num = i;
		philos[i].info = info;
		if (pthread_create(&(philos->thread), NULL, func, &philos[i]) != 0)
		{
			printf("Error: thread not created\n");
			free(philos);
			return (NULL);
		}
		// pthread_detach(philos[i].thread);
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

int	philo_cycle(t_philo_info *info)
{
	t_philo *philos;
	int		i;

	i = 0;
	philos = create_philosophers(info);
	// while (1){}
	if (philos == NULL)
		return (printf("Error: philos == NULL\n") + 1);
	while (i < philos->num)
	{
		// pthread_join(philos[i].thread, NULL);
		++i;
	}
	// usleep(1000000000);
	while (1){}
	// delete_philosophers(*info, philos);	
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo_info info;

	if (argc == 5 || argc == 6)
	{
		info = parser(argc, argv);
		print_info(info);
		philo_cycle(&info);
	}
	return (0);
}
