/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:41:10 by mmittelb          #+#    #+#             */
/*   Updated: 2026/01/30 15:49:28 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philo_pocesses(t_philo *philo, t_data *data)
{
	int			i;
	int			j;

	i = 0;
	while (i < data->numbr_of_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
		{
			write(2, "Error: failed to create thread\n", 31);
			pthread_mutex_lock(&philo->data->stop_mutex);
			philo->data->death_flag = 1;
			pthread_mutex_unlock(&philo->data->stop_mutex);
			j = 0;
			while (j < i)
				pthread_join(philo[i].thread, NULL);
			pthread_join(data->monitor_thread1, NULL);
			pthread_join(data->monitor_thread2, NULL);
			return (1);
		}
		i++;
	}
	return (0);
}

int	create_threads(t_philo *philo, t_data *data)
{
	int		i;

	if (pthread_create(&data->monitor_thread1, NULL, meals_monitor, philo) != 0)
	{
		write(2, "Error: failed to create thread\n", 31);
		return (1);
	}
	if (pthread_create(&data->monitor_thread2, NULL, death_monitor, philo) != 0)
	{
		write(2, "Error: failed to create thread\n", 31);
		pthread_mutex_lock(&philo->data->stop_mutex);
		philo->data->death_flag = 1;
		pthread_mutex_unlock(&philo->data->stop_mutex);
		pthread_join(data->monitor_thread1, NULL);
		return (1);
	}
	if (create_philo_pocesses(philo, data) != 0)
		return (1);
	i = 0;
	while (i < data->numbr_of_philos)
		pthread_join(philo[i++].thread, NULL);
	pthread_join(data->monitor_thread1, NULL);
	pthread_join(data->monitor_thread2, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo		*philos;
	t_data		*data;

	if (error_handling(argc, argv))
		return (1);
	data = allocate_data(argc, argv);
	if (data == NULL)
		return (1);
	philos = initialize_philo_variables(data);
	if (philos == NULL)
		return (free(data->forks), free(data), 1);
	data->all_philos = philos;
	initialize_mutexes(data, philos);
	if (create_threads(philos, data))
	{
		destroy_mutexes(data, philos);
		free_all(data, philos);
		return (1);
	}
	destroy_mutexes(data, philos);
	free_all(data, philos);
	return (0);
}
