/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:02:31 by mmittelb          #+#    #+#             */
/*   Updated: 2026/02/03 18:06:49 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_or_satisfied(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	if (data->death_flag == 1
		|| data->philos_satisfied_flag == 1)
	{
		pthread_mutex_unlock(&data->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->stop_mutex);
	return (0);
}

long	get_time_in_ms(void)
{
	t_time	time;

	gettimeofday((struct timeval *)&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	precise_sleep(long ms, t_philo *philo)
{
	long	start;

	start = get_time_in_ms();
	while (get_time_in_ms() - start < ms)
	{
		pthread_mutex_lock(&philo->data->stop_mutex);
		if (philo->data->death_flag == 1
			|| philo->data->philos_satisfied_flag == 1)
		{
			pthread_mutex_unlock(&philo->data->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->stop_mutex);
		usleep(100);
	}
}

int	ft_atoi(char *str)
{
	int	i;
	int	result;
	int	neg;

	i = 0;
	result = 0;
	neg = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		neg = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > INT_MAX || result < INT_MIN)
			return (-1);
		result = result * 10 + (str[i++] - 48);
	}
	if (neg == 1)
		result = -result;
	return (result);
}
