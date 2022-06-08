/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mea <mea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:12:41 by mea               #+#    #+#             */
/*   Updated: 2022/06/08 14:13:41 by mea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	thinking(t_philo *philo)
{
	print_action(convert_time_in_ms_from_start(philo->table), philo, "is thinking\n");
}

void	sleeping(t_philo *philo)
{
	philo->sleeping = 1;
	print_action(convert_time_in_ms_from_start(philo->table), philo, "is sleeping\n");
	ft_sleep(philo->table->time_to_sleep);
	philo->sleeping = 0;
}

void	eating(t_philo	*philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(convert_time_in_ms_from_start(philo->table), philo, "has taken a fork\n");
	pthread_mutex_lock(philo->right_fork);
	print_action(convert_time_in_ms_from_start(philo->table), philo, "has taken a fork\n");
	philo->eating = 1;
	print_action(convert_time_in_ms_from_start(philo->table), philo, "is eating\n");
	ft_sleep(philo->table->time_to_eat);
	philo->last_meal_time = convert_time_in_ms_from_start(philo->table);
	philo->nb_of_meal++;
	philo->eating = 0;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*dinner_time(void *data)
{
	t_philo	*philo;
	
	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_sleep(10);
	while (!philo->table->death)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
