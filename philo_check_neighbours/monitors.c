/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelmittelbach <manuelmittelbach@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:01:31 by mmittelb          #+#    #+#             */
/*   Updated: 2026/03/26 12:39:35 by manuelmitte      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_philo_dead(t_philo *philo, int i)
{
	long		current_time;
	long		last_meal_time;

	pthread_mutex_lock(&philo[i].last_meal_time_mutex);
	current_time = get_time_in_ms();
	last_meal_time = philo[i].last_meal_time;
	pthread_mutex_unlock(&philo[i].last_meal_time_mutex);
	if (current_time - last_meal_time >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d died\n",
			current_time - philo->data->starttime, philo[i].id);
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_lock(&philo->data->stop_mutex);
		philo->data->death_flag = 1;
		pthread_mutex_unlock(&philo->data->stop_mutex);
		return (1);
	}
	return (0);
}

void	*death_monitor(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (1)
	{
		if (dead_or_satisfied(philo->data))
			return (NULL);
		i = 0;
		while (i < philo->data->numbr_of_philos)
		{
			if (is_philo_dead(philo, i))
				return (NULL);
			i++;
		}
		usleep(500);
	}
	return (NULL);
}

static int	had_enough(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->data->number_of_meals == -1)
		return (0);
	while (i < philo->data->numbr_of_philos)
	{
		pthread_mutex_lock(&philo[i].meals_eaten_mutex);
		if (philo[i].meals_eaten < philo->data->number_of_meals)
		{
			pthread_mutex_unlock(&philo[i].meals_eaten_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo[i].meals_eaten_mutex);
		i++;
	}
	return (1);
}

void	*meals_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (dead_or_satisfied(philo->data))
			return (NULL);
		if (had_enough(philo) == 1)
		{
			pthread_mutex_lock(&philo->data->stop_mutex);
			philo->data->philos_satisfied_flag = 1;
			pthread_mutex_unlock(&philo->data->stop_mutex);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}
