/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 10:47:38 by lflorrie          #+#    #+#             */
/*   Updated: 2021/07/08 10:47:41 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_info(t_philo_info info)
{
	printf("ph: %i\ndie time: %i\neat time: %i\nsleep time: %i\nmax eat: %i\n",
		info.philos, info.die_time, info.eat_time, info.sleep_time,
		info.max_eat);
}

t_philo	*create_philosophers(t_philo_info *info)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * info->philos);
	i = 0;
	gettimeofday(&info->time_start_sim, NULL);
	while (i < info->philos)
	{
		gettimeofday(&(philos[i].last_time_eat), NULL);
		philos[i].num = i + 1;
		philos[i].info = info;
		philos[i].eat_counter = 0;
		philos[i].pid = fork();
		if (philos[i].pid == -1)
		{
			printf("Error: process not created\n");
			free(philos);
			return (NULL);
		}
		if (philos[i].pid == 0)
			philo_life(&philos[i]);
		usleep(100);
		++i;
	}
	return (philos);
}

int	philo_start(t_philo_info *info)
{
	t_philo	*philos;

	philos = create_philosophers(info);
	if (philos == NULL)
		return (printf("Error: philos == NULL\n") + 1);
	sem_wait(info->dead);
	printf("%ld ms philo %i died\n",
				get_time(info->time_start_sim), philos[0].num);
	free_philos(info, philos);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo_info	*info;

	if (argc == 5 || argc == 6)
	{
		info = parser(argc, argv);
		if (info == NULL)
		{
			printf("Error: parser - failed\n");
			fflush(stdout);
			return (1);
		}
		print_info(*info);
		philo_start(info);
		free_info(info);
	}
	else
	{
		printf("Error: must be 4 or 5 parameters\n");
	}
	return (0);
}
