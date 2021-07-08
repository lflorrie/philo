/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflorrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 10:48:02 by lflorrie          #+#    #+#             */
/*   Updated: 2021/07/08 10:48:05 by lflorrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>

typedef struct s_philo_info
{
	int				philos;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				max_eat;
	int				dead;
	struct timeval	time_start_sim;
	pthread_mutex_t	*forks;
}				t_philo_info;

typedef struct s_philo
{
	pthread_t		thread;
	int				num;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_philo_info	*info;
	struct timeval	last_time_eat;
}					t_philo;

t_philo_info	parser(int argc, char **argv);

int				check_life_time(t_philo *philo, struct timeval start);

void			*philo_life(void *args);

#endif
