/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mea <mea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:12:41 by mea               #+#    #+#             */
/*   Updated: 2022/06/06 15:23:45 by mea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_sleep(long int time)
{
	usleep(time);
}

void	print_action(long int time, int philo_id, char *msg)
{
	printf("%zu ms: Philosopher %d %s\n", time, philo_id, msg);
}

void	sleeping(t_philo *philo)
{
	philo->sleeping = 1;
	ft_sleep(philo->table->time_to_sleep);
	philo->sleeping = 0;
}

void	eating(t_philo	*philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->table->is_writing);
	print_action(get_actual_time(), philo->id, "has taken a fork\n");
	pthread_mutex_unlock(&philo->table->is_writing);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->table->is_writing);
	print_action(get_actual_time(), philo->id, "has taken a fork\n");
	pthread_mutex_unlock(&philo->table->is_writing);
	philo->eating = 1;
	philo->nb_of_meal++;
	ft_sleep(philo->table->time_to_eat);
	pthread_mutex_lock(&philo->table->is_writing);
	print_action(get_actual_time(), philo->id, "is eating\n");
	pthread_mutex_unlock(&philo->table->is_writing);
	philo->last_meal_time = get_time();
	philo->eating = 0;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*dinner_time(void *data)
{
	t_philo	philo;
	int		i;
	
	philo = *(t_philo*)data;
	i = 0;
	while (philo.dead != 1)
	{
		eating(&philo);
		sleeping(&philo);
		thinking(&philo);
	}
	return (NULL);
}
