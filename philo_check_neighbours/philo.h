/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:16:50 by mmittelb          #+#    #+#             */
/*   Updated: 2026/02/03 18:07:03 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				numbr_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	long			starttime;
	int				death_flag;
	int				philos_satisfied_flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
	pthread_t		monitor_thread1;
	pthread_t		monitor_thread2;
	t_philo			*all_philos;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				death;
	long			last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	last_meal_time_mutex;
	pthread_mutex_t	meals_eaten_mutex;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

typedef struct s_time
{
	time_t		tv_sec;
	suseconds_t	tv_usec;
}	t_time;

int		dead_or_satisfied(t_data *data);
t_data	*init_data(int argc, char **argv);
t_data	*allocate_data(int argc, char **argv);
void	initialize_mutexes(t_data *data, t_philo *philo);
void	*routine(void *arg);
t_philo	*initialize_philo_variables(t_data *data);
int		take_forks_right_first(t_philo *philo);
int		take_forks_left_first(t_philo *philo);
int		ft_atoi(char *str);
long	get_time_in_ms(void);
void	precise_sleep(long time_in_ms, t_philo *philo);
void	*death_monitor(void *arg);
void	*meals_monitor(void *arg);
int		error_handling(int argc, char **argv);
void	free_all(t_data *data, t_philo *philo);
void	destroy_mutexes(t_data *data, t_philo *philo);
#endif