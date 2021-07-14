/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <lflorries@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 12:46:21 by lflorrie          #+#    #+#             */
/*   Updated: 2021/07/13 12:46:22 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long long		res;
	long long		sign;

	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		++str;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		++str;
	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		if ((res > 2147483647 && sign == 1))
			return (-1);
		if (res > 2147483648 && sign == -1)
			return (0);
		++str;
	}
	return (res * sign);
}

long	get_time(struct timeval start)
{
	struct timeval		stop;
	unsigned long long	stop1;
	unsigned long long	start1;

	gettimeofday(&stop, NULL);
	start1 = start.tv_sec * 1000 + start.tv_usec / 1000;
	stop1 = stop.tv_sec * 1000 + stop.tv_usec / 1000;
	return (stop1 - start1);
}

void	my_sleep(int time)
{
	struct timeval	start;

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
