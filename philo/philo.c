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

long get_time(struct timeval start)
{
	struct timeval stop;

	gettimeofday(&stop, NULL);
	unsigned long long start1 = start.tv_sec * 1000 + start.tv_usec / 1000; 
	unsigned long long stop1 = stop.tv_sec * 1000 + stop.tv_usec / 1000; 
	return (stop1 - start1);
}

void	my_sleep(int time)
{
	struct timeval start;

	gettimeofday(&start, NULL);
	while (get_time(start) < time)
		usleep(50);
}

int	check_life_time(t_philo *philo, struct timeval start)
{
	struct timeval	stop;

	gettimeofday(&stop, NULL);
	if (philo->info->die_time <= get_time(start))
		return (1);
	return (0);
}

void	print_state(t_philo *philo, t_enum state)
{
	long long tmp;

	tmp = get_time(philo->info->time_start_sim);
	if (philo->info->dead != 0 || tmp < 0)
		return ;
	pthread_mutex_lock(&philo->info->mutex_write);

	printf("%ld ms %i", get_time(philo->info->time_start_sim), philo->num);
	if (state == THINKING)
		printf(" is thinking\n");
	if (state == SLEEPING)
		printf(" is sleeping\n");
	if (state == EATING)
	{
		printf(" is eating\n");
		philo->eat_counter++;
	}
	if (state == FORK)
		printf(" has taken fork\n");
	fflush(stdout);
	pthread_mutex_unlock(&philo->info->mutex_write);
}

void	philo_sleep(t_philo *philo)
{
	struct timeval	stop;

	gettimeofday(&stop, NULL);
	print_state(philo, SLEEPING);
	my_sleep(philo->info->sleep_time);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_state(philo, FORK);
	pthread_mutex_lock(philo->r_fork);
	print_state(philo, FORK);
	print_state(philo, EATING);
	my_sleep(philo->info->eat_time);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
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
	while (1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		print_state(philo, THINKING);
	}
	return (NULL);
}
