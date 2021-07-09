/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 10:48:37 by lflorrie          #+#    #+#             */
/*   Updated: 2021/07/08 10:48:37 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_life_time(t_philo *philo, struct timeval start)
{
	struct timeval	stop;

	gettimeofday(&stop, NULL);
	if (philo->info->die_time <= (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)
	{
		printf("philo->info->die_time = %i\n", philo->info->die_time);
		printf("-----TIME: die time = %i <= %ld time ------\n", philo->info->die_time, (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
		return (1);
	}
	return (0);
}

void	philo_sleep(t_philo *philo)
{
	struct timeval	start;
	struct timeval	stop;

	gettimeofday(&start, NULL);
	gettimeofday(&stop, NULL);
	printf("%ld ms %i is sleeping\n", (stop.tv_sec - philo->info->time_start_sim.tv_sec) * 1000000 + stop.tv_usec - philo->info->time_start_sim.tv_usec, philo->num);
	usleep(philo->info->sleep_time * 1000);
}

void	philo_eat(t_philo *philo)
{
	// printf("%i ----- r_fork unlock result =  %i\n", philo->num, pthread_mutex_unlock(philo->r_fork));
	// usleep(3000000);
	printf("%i ----- l_fork lock result =  %i\n", philo->num, pthread_mutex_lock(philo->l_fork));
	printf("%i ----- r_fork lock result =  %i\n", philo->num, pthread_mutex_lock(philo->r_fork));
	// usleep(3000000);
	printf("OK\n");
	printf("%i ----- r_fork unlock result =  %i\n", philo->num, pthread_mutex_unlock(philo->r_fork));
	// usleep(3000000);
	printf("%i ----- l_fork unlock result =  %i\n", philo->num, pthread_mutex_unlock(philo->l_fork));
	gettimeofday(&philo->last_time_eat, NULL);
}

void	*philo_life(void *args)
{
	t_philo			*philo;
	philo = (t_philo *)args;
	philo->l_fork = &philo->info->forks[philo->num - 1];
	if (philo->num == philo->info->philos)
		philo->r_fork = &philo->info->forks[0];
	else
		philo->r_fork = &philo->info->forks[philo->num];
	gettimeofday(&philo->last_time_eat, NULL);
	printf("%ld ms %i is spawned\n", (philo->info->time_start_sim.tv_sec) * 1000000 + philo->info->time_start_sim.tv_usec, philo->num);
	while (1)
	{
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}
