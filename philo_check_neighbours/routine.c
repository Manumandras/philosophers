/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelmittelbach <manuelmittelbach@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:27:05 by mmittelb          #+#    #+#             */
/*   Updated: 2026/03/26 12:39:35 by manuelmitte      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	change_meal_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->meals_eaten_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_eaten_mutex);
}

int	eat(t_philo *philo)
{
	if (dead_or_satisfied(philo->data))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	change_meal_count(philo);
	pthread_mutex_lock(&philo->last_meal_time_mutex);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->last_meal_time_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %i is eating\n",
		get_time_in_ms() - philo->data->starttime, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	precise_sleep(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}

int	go_to_sleep(t_philo *philo)
{
	if (dead_or_satisfied(philo->data))
		return (1);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d is sleeping\n",
		get_time_in_ms() - philo->data->starttime, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	precise_sleep(philo->data->time_to_sleep, philo);
	return (0);
}

int	think(t_philo *philo)
{
	if (dead_or_satisfied(philo->data))
		return (1);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d is thinking\n",
		get_time_in_ms() - philo->data->starttime, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (philo->id % 2 != 0)
		{
			if (take_forks_right_first(philo))
				return (NULL);
		}
		else
		{
			if (take_forks_left_first(philo))
				return (NULL);
		}
		if (eat(philo))
			return (NULL);
		if (go_to_sleep(philo))
			return (NULL);
		if (think(philo))
			return (NULL);
	}
	return (NULL);
}
