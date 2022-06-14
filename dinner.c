/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mea <mea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:12:41 by mea               #+#    #+#             */
/*   Updated: 2022/06/14 15:12:38 by mea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	thinking(t_philo *philo)
{
	if (philo->table->death == 0 && philo->table->stop == 0)
	{
		print_action(actual_time(), philo, "is thinking\n");
		death_checker(philo->table);
	}
}

void	sleeping(t_philo *philo)
{
	if (philo->table->death == 0 && philo->table->stop == 0)
	{
		philo->sleeping = 1;
		print_action(actual_time(), philo, "is sleeping\n");
		ft_sleep(philo->table->time_to_sleep);
		philo->sleeping = 0;
		death_checker(philo->table);
	}
}

void	eating(t_philo	*philo)
{
	if (philo->table->death == 0 && philo->table->stop == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(actual_time(), philo, "has taken a fork\n");
		if (philo->table->death == 1)
		{
			pthread_mutex_unlock(philo->left_fork);
			return ;
		}
		pthread_mutex_lock(philo->right_fork);
		print_action(actual_time(), philo, "has taken a fork\n");
		if (philo->table->death == 1)
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return ;
		}
		//philo->eating = 1;
		print_action(actual_time(), philo, "is eating\n");
		ft_sleep(philo->table->time_to_eat);
		philo->last_meal_time = actual_time();
		philo->nb_of_meal++;
		//philo->eating = 0;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		death_checker(philo->table);
	}
}

void	*dinner_time(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_sleep(10);
	while (philo->table->death == 0 && philo->table->stop == 0)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
