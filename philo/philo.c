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

void	my_sleep(int time)
{
	struct timeval start;
	struct timeval stop;

	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&stop, NULL);
		if ((stop.tv_sec - start.tv_sec) * 1000 + (stop.tv_usec - start.tv_usec) / 1000 >= time)
			return ;
		usleep(100);
	}
}

int	check_life_time(t_philo *philo, struct timeval start)
{
	struct timeval	stop;

	gettimeofday(&stop, NULL);
	if (philo->info->die_time <= (stop.tv_sec - start.tv_sec) * 1000 + (stop.tv_usec - start.tv_usec) / 1000)
	{
		printf("philo->info->die_time = %i\n", philo->info->die_time);
		printf("-----TIME: die time = %i <= %ld time ------\n", philo->info->die_time, (stop.tv_sec - start.tv_sec) * 1000 + (stop.tv_usec - start.tv_usec) / 1000);
		fflush(stdout);
		return (1);
	}
	return (0);
}

void	philo_sleep(t_philo *philo)
{
	struct timeval	stop;

	gettimeofday(&stop, NULL);
	printf("%ld ms %i is sleeping\n", (stop.tv_sec - philo->info->time_start_sim.tv_sec) * 1000 + (stop.tv_usec - philo->info->time_start_sim.tv_usec) / 1000, philo->num);
	fflush(stdout);
	my_sleep(philo->info->sleep_time);
}

void	philo_eat(t_philo *philo)
{
	struct timeval	now;
	
	pthread_mutex_lock(philo->l_fork);
	gettimeofday(&now, NULL);
	printf("%ld ms %i has taken a fork\n", (now.tv_sec - philo->info->time_start_sim.tv_sec) * 1000 + (now.tv_usec - philo->info->time_start_sim.tv_usec) / 1000, philo->num);
	fflush(stdout);
	pthread_mutex_lock(philo->r_fork);
	gettimeofday(&now, NULL);
	printf("%ld ms %i has taken a fork\n", (now.tv_sec - philo->info->time_start_sim.tv_sec) * 1000 + (now.tv_usec - philo->info->time_start_sim.tv_usec) / 1000, philo->num);
	fflush(stdout);
	gettimeofday(&now, NULL);
	printf("%ld ms %i is eating\n", (now.tv_sec - philo->info->time_start_sim.tv_sec) * 1000 + (now.tv_usec - philo->info->time_start_sim.tv_usec) / 1000, philo->num);
	fflush(stdout);

	my_sleep(philo->info->eat_time);
	
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	gettimeofday(&philo->last_time_eat, NULL);
}

void	*philo_life(void *args)
{
	t_philo			*philo;
	struct timeval	now;

	philo = (t_philo *)args;
	philo->l_fork = &philo->info->forks[philo->num - 1];
	if (philo->num == philo->info->philos)
		philo->r_fork = &philo->info->forks[0];
	else
		philo->r_fork = &philo->info->forks[philo->num];
	gettimeofday(&philo->last_time_eat, NULL);
	while (1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		gettimeofday(&now, NULL);
		printf("%ld ms %i is thinking\n", (now.tv_sec - philo->info->time_start_sim.tv_sec) * 1000 + (now.tv_usec - philo->info->time_start_sim.tv_usec) / 1000, philo->num);
		fflush(stdout);
	}
	return (NULL);
}
