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

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->is_writing);
	print_action(convert_time_in_ms_from_start(philo->table), philo, "is thinking\n");
	pthread_mutex_unlock(&philo->table->is_writing);
}

void	sleeping(t_philo *philo)
{
	philo->sleeping = 1;
	pthread_mutex_lock(&philo->table->is_writing);
	print_action(convert_time_in_ms_from_start(philo->table), philo, "is sleeping\n");
	pthread_mutex_unlock(&philo->table->is_writing);
	ft_sleep(philo->table->time_to_sleep);
	philo->sleeping = 0;
}

void	eating(t_philo	*philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->table->is_writing);
	print_action(convert_time_in_ms_from_start(philo->table), philo, "has taken a fork\n");
	pthread_mutex_unlock(&philo->table->is_writing);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->table->is_writing);
	print_action(convert_time_in_ms_from_start(philo->table), philo, "has taken a fork\n");
	pthread_mutex_unlock(&philo->table->is_writing);
	philo->eating = 1;
	philo->nb_of_meal++;
	ft_sleep(philo->table->time_to_eat);
	pthread_mutex_lock(&philo->table->is_writing);
	print_action(convert_time_in_ms_from_start(philo->table), philo, "is eating\n");
	pthread_mutex_unlock(&philo->table->is_writing);
	philo->last_meal_time = convert_time_in_ms_from_start(philo->table);
	philo->eating = 0;
	pthread_mutex_unlock(philo->left_fork);
	printf("Fork %d released\n", philo->id);
	pthread_mutex_unlock(philo->right_fork);
	printf("Fork %d released\n", philo->id + 1);
}

void	*dinner_time(void *data)
{
	t_philo	philo;
	int		i;
	
	philo = *(t_philo*)data;
	i = 0;
	if (philo.id % 2 == 0)
		ft_sleep(10);
	while (1)
	{
		eating(&philo);
		sleeping(&philo);
		thinking(&philo);
	}
	return (NULL);
}
