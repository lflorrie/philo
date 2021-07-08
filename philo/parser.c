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

t_philo_info	parser(int argc, char **argv)
{
	t_philo_info	info;
	int				i;

	info.philos = atoi(argv[1]); // ft_atoi
	info.die_time = atoi(argv[2]); // ft_atoi
	info.eat_time = atoi(argv[3]); // ft_atoi
	info.sleep_time = atoi(argv[4]); // ft_atoi
	if (argc == 6)
		info.max_eat = atoi(argv[5]); // ft_atoi
	else
		info.max_eat = 0;
	info.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info.philos);
	i = 0;
	while (i < info.philos)
	{
		pthread_mutex_init(&info.forks[i], NULL);
		++i;
	}
	info.dead = 0;
	return (info);
}
