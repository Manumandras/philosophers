/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:01:57 by mmittelb          #+#    #+#             */
/*   Updated: 2026/01/29 11:56:30 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->numbr_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&philo[i].last_meal_time_mutex);
		pthread_mutex_destroy(&philo[i].meals_eaten_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->stop_mutex);
	pthread_mutex_destroy(&data->print_mutex);
}

void	free_all(t_data *data, t_philo *philo)
{
	free (data->forks);
	free (data);
	free (philo);
}
