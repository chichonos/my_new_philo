/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mea <mea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:15:18 by mea               #+#    #+#             */
/*   Updated: 2022/06/28 09:35:19 by mea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_atoi(const char *str)
{
	int	neg;
	int	i;
	int	num;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}

void	print_action(int time, t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->table->is_writing);
	if (philo->table->death == 0)
		printf("%d %d %s", time, philo->id, msg);
	pthread_mutex_unlock(&philo->table->is_writing);
}

int	meal_checker(t_philo *philo)
{
	int			i;
	int			finish_eating;

	finish_eating = 0;
	if (philo->table->nb_of_meal_min < 0)
		return (1);
	i = -1;
	if (philo->nb_of_meal < philo->table->nb_of_meal_min)
			return (0);
	else if (philo->nb_of_meal >= philo->table->nb_of_meal_min)
		return (1);
	else
		return (0);
}

int	death_checker(t_philo *philo)
{
	if ((actual_time() - philo->last_meal_time) \
	>= philo->table->time_to_die)
	{
		pthread_mutex_lock(&philo->table->is_dying);
		print_action(actual_time(), philo, "died\n");
		philo->table->death = 1;
		pthread_mutex_unlock(&philo->table->is_dying);
		return (1);
	}
	return (0);
}
