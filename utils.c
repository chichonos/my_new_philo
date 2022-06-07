/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mea <mea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:15:18 by mea               #+#    #+#             */
/*   Updated: 2022/06/06 13:15:58 by mea              ###   ########.fr       */
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

void	print_action(long int time, t_philo *philo, char *msg)
{
	if (philo->table->death == 0)
		printf("%zu ms: Philosopher %d %s\n", time, philo->id, msg);
}

size_t	philo_check_eat(t_table *table)
{
	size_t	i;

	if (table->nb_of_meal_min < 0)
		return (0);
	i = -1;
	while (++i < table->nb_of_philo)
	{
		if (table->philos[i].nb_of_meal < table->nb_of_meal_min)
			return (0);
	}
	return (1);
}

void	philo_check_death(t_table *table)
{
	size_t	i;

	if (table->nb_of_philo == 1)
		print_action(get_time_ms_now(), table->philo, "is dead\n");
	while (table->nb_of_philo > 1)
	{
		i = -1;
		while (++i < table->nb_of_philo)
		{
			if (table->philos[i].eating == 1)
				continue ;
			pthread_mutex_lock(&table->is_diying);
			if (get_time_ms_now() - \
			table->philos[i].last_meal_time >= table->time_to_die)
			{
				print_action(get_time_ms_now(), table->philos + i, "is dead\n");
				table->death = 1;
				return ;
			}
			pthread_mutex_unlock(&table->is_diying);
		}
		if (philo_check_eat(table))
			break ;
	}
	table->death = 1;
}
