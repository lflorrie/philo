/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 10:47:50 by lflorrie          #+#    #+#             */
/*   Updated: 2021/07/08 10:47:51 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo_info	*free_forks(t_philo_info *info, int i)
{
	while (i > 0)
	{
		--i;
		pthread_mutex_destroy(&info->forks[i]);
	}
	free(info->forks);
	return (NULL);
}

t_philo_info	*init_mutexes(t_philo_info *info)
{
	int	i;

	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* info->philos);
	if (info->forks == NULL)
		return (NULL);
	i = 0;
	while (i < info->philos)
	{
		if (pthread_mutex_init(&info->forks[i], NULL) != 0)
			return (free_forks(info, i));
		++i;
	}
	if (pthread_mutex_init(&info->mutex_write, NULL) != 0)
	{
		free(info->forks);
		return (NULL);
	}
	info->dead = 0;
	info->finish_eating = 0;
	return (info);
}

t_philo_info	*parser(int argc, char **argv)
{
	t_philo_info	*info;

	info = (t_philo_info *)malloc(sizeof(t_philo_info));
	if (info == NULL)
		return (NULL);
	info->philos = ft_atoi(argv[1]);
	info->die_time = ft_atoi(argv[2]);
	info->eat_time = ft_atoi(argv[3]);
	info->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		info->max_eat = ft_atoi(argv[5]);
	else
		info->max_eat = -1;
	if (info->philos < 1 || info->die_time < 1 || info->eat_time < 1
		|| info->sleep_time < 1 || (info->max_eat < 1 && argc == 6))
	{
		free(info);
		return (NULL);
	}
	if (init_mutexes(info) == NULL)
	{
		free(info);
		return (NULL);
	}
	return (info);
}

void	free_info(t_philo_info info)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&info.mutex_write);
	if (info.forks)
	{
		while (i < info.philos)
		{
			pthread_mutex_destroy(&info.forks[i]);
			++i;
		}
		free(info.forks);
	}
}

void	free_philos(t_philo_info *info, t_philo *philos)
{
	int	i;

	i = 0;
	pthread_mutex_unlock(&info->mutex_write);
	while (i < info->philos)
	{
		pthread_join(philos[i].thread, NULL);
		++i;
	}
	free(philos);
}
