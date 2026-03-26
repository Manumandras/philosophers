/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:01:45 by mmittelb          #+#    #+#             */
/*   Updated: 2026/01/30 15:49:28 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_mutexes(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->numbr_of_philos)
	{
		pthread_mutex_init(&philo[i].last_meal_time_mutex, NULL);
		pthread_mutex_init(&philo[i].meals_eaten_mutex, NULL);
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->stop_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
}

static t_philo	*allocate_philos(t_data *data)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * data->numbr_of_philos);
	if (!philo)
	{
		free(data->forks);
		free(data);
		write(2, "Error: malloc failed\n", 21);
		return (NULL);
	}
	return (philo);
}

t_philo	*initialize_philo_variables(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = allocate_philos(data);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < data->numbr_of_philos)
	{
		philo[i].death = 0;
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].right_fork = &data->forks[i];
		if (data->numbr_of_philos == 1)
			philo[i].left_fork = NULL;
		else
			philo[i].left_fork = &data->forks[(i + 1) % data->numbr_of_philos];
		philo[i].meals_eaten = 0;
		philo[i].last_meal_time = data->starttime;
		i++;
	}
	return (philo);
}

static void	initialize_data_fields(t_data *data, int argc, char **argv)
{
	data->numbr_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->death_flag = 0;
	data->philos_satisfied_flag = 0;
	if (argc == 6)
		data->number_of_meals = ft_atoi(argv[5]);
	else
		data->number_of_meals = -1;
	data->starttime = get_time_in_ms();
}

t_data	*allocate_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		write(2, "Error: malloc failed\n", 21);
		return (NULL);
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	if (!data->forks)
	{
		free(data);
		write(2, "Error: malloc failed\n", 21);
		return (NULL);
	}
	initialize_data_fields(data, argc, argv);
	return (data);
}
