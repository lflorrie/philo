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
		if (pthread_create(&(philos->thread), NULL,
				philo_life, &(philos[i])) != 0)
		{
			printf("Error: thread not created\n");
			free(philos);
			return (NULL);
		}
		usleep(50);
		// pthread_detach(philos[i].thread);
		// pthread_join(philos[i].thread, NULL);
		++i;
	}
	return (philos);
}

void	delete_philosophers(t_philo_info info, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < info.philos)
	{
		++i;
	}
	free(philos);
}

int	philo_start(t_philo_info *info)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = create_philosophers(info);
	if (philos == NULL)
		return (printf("Error: philos == NULL\n") + 1);
	while (info->dead == 0)
	{
		if (i == info->philos)
			i = 0;
		if (check_life_time(&philos[i], philos[i].last_time_eat))
		{
			printf("philo %i dead\n", philos[i].num);
			philos[i].info->dead++;
		}
		++i;
	}
	// delete_philosophers(*info, philos);	
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo_info	info;

	if (argc == 5 || argc == 6)
	{
		info = parser(argc, argv);
		print_info(info);
		philo_start(&info);
	}
	return (0);
}
