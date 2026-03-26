/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 12:02:17 by mmittelb          #+#    #+#             */
/*   Updated: 2025/11/04 12:02:17 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_arg_count(int argc)
{
	if (argc != 5 && argc != 6)
	{
		write(2, "Error: wrong number of arguments\n", 33);
		return (1);
	}
	return (0);
}

static int	check_positive_value(char *arg)
{
	if (ft_atoi(arg) <= 0)
	{
		write(2, "Error: arguments must be positive integers\n", 43);
		return (1);
	}
	return (0);
}

static int	check_is_number(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
		{
			write(2, "Error: arguments must be positive integers\n", 43);
			return (1);
		}
		i++;
	}
	return (0);
}

int	error_handling(int argc, char **argv)
{
	int	i;

	if (check_arg_count(argc))
		return (1);
	i = 1;
	while (i < argc)
	{
		if (check_is_number(argv[i]) || check_positive_value(argv[i]))
			return (1);
		i++;
	}
	return (0);
}
