/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelmittelbach <manuelmittelbach@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:02:15 by mmittelb          #+#    #+#             */
/*   Updated: 2026/03/26 12:39:35 by manuelmitte      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_fork(t_philo *philo, int left_fork)
{
	if (left_fork == 1)
		pthread_mutex_lock(philo->left_fork);
	else
		pthread_mutex_lock(philo->right_fork);
	if (dead_or_satisfied(philo->data))
	{
		if (left_fork == 1)
			pthread_mutex_unlock(philo->left_fork);
		else
			pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %i has taken a fork\n",
		get_time_in_ms() - philo->data->starttime, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (0);
}

static int	can_eat(t_philo *philo, t_philo *left, t_philo *right)
{
	int	my_meals;
	int	left_meals;
	int	right_meals;

	pthread_mutex_lock(&left->meals_eaten_mutex);
	left_meals = left->meals_eaten;
	pthread_mutex_unlock(&left->meals_eaten_mutex);
	pthread_mutex_lock(&right->meals_eaten_mutex);
	right_meals = right->meals_eaten;
	pthread_mutex_unlock(&right->meals_eaten_mutex);
	pthread_mutex_lock(&philo->meals_eaten_mutex);
	my_meals = philo->meals_eaten;
	pthread_mutex_unlock(&philo->meals_eaten_mutex);
	if (left_meals >= my_meals && right_meals >= my_meals)
		return (1);
	return (0);
}

int	may_i(t_philo *philo)
{
	int		i;
	int		left;
	int		right;
	t_philo	*left_p;
	t_philo	*right_p;

	i = philo->id - 1;
	left = (i - 1 + philo->data->numbr_of_philos) % \
	philo->data->numbr_of_philos;
	right = (i + 1) % philo->data->numbr_of_philos;
	left_p = &philo->data->all_philos[left];
	right_p = &philo->data->all_philos[right];
	while (1)
	{
		if (can_eat(philo, left_p, right_p))
			return (0);
		if (dead_or_satisfied(philo->data))
			return (1);
		usleep(500);
	}
}

int	take_forks_right_first(t_philo *philo)
{
	if (philo->data->numbr_of_philos % 2 == 1 
		&& philo->data->numbr_of_philos != 1)
	{
		if (may_i(philo))
			return (1);
	}
	if (take_fork(philo, 0))
		return (1);
	if (philo->left_fork == NULL)
	{
		pthread_mutex_unlock(philo->right_fork);
		precise_sleep(philo->data->time_to_die, philo);
		return (1);
	}
	if (take_fork(philo, 1))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	return (0);
}

int	take_forks_left_first(t_philo *philo)
{
	if (philo->data->numbr_of_philos % 2 == 1)
	{
		if (may_i(philo))
			return (1);
	}
	if (take_fork(philo, 1))
		return (1);
	if (take_fork(philo, 0))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}
