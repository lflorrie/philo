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

typedef enum e_enum
{
	EATING,
	SLEEPING,
	THINKING,
	FORK
}			t_enum;

typedef struct s_philo_info
{
	int				philos;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				max_eat;
	int				finish_eating;
	int				dead;
	struct timeval	time_start_sim;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_write;
}				t_philo_info;

typedef struct s_philo
{
	pthread_t		thread;
	int				num;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_philo_info	*info;
	int				eat_counter;
	struct timeval	last_time_eat;
}					t_philo;

t_philo_info	*parser(int argc, char **argv);

int				check_life_time(t_philo *philo, struct timeval start);

void			*philo_life(void *args);

void			my_sleep(int time);

long			get_time(struct timeval start);

/* free functions */

void			free_info(t_philo_info *info);

void			free_philos(t_philo_info *info, t_philo *philos);

/* utils */
int				ft_atoi(const char *str);

int				check_life_time(t_philo *philo, struct timeval start);

void			my_sleep(int time);

long			get_time(struct timeval start);
#endif
