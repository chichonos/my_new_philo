/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mea <mea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 13:58:39 by mea               #+#    #+#             */
/*   Updated: 2022/06/03 15:57:22 by mea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_forks(t_table table, int i)
{
	while (i < table.nb_of_philo)
	{
		pthread_mutex_init(table.forks[i], NULL);
		i++;
	}
}

void	init_philo(t_table table, int i)
{
	t_philo *philo;

	philo = &table.philo[i];
	philo->id = i;
	philo->eating = 0;
	philo->sleeping = 0;
	philo->dead = 0;
	philo->nb_of_meal = 0;
	philo->last_meal_time = 0;
	philo->table = &table;
	if (i - 1 < 0)
		philo->left_fork = table->forks + (table->count - 1);
	else
		philo->left_fork = table->forks + (i - 1);
	philo->right_fork = table->forks + i;
}

void	start_the_party(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->nb_of_philos)
		init_forks(table, i++);
	i = 0;
	while (i < table->nb_of_philos)
		init_philo(table, i++);
	i = 0;
	while (i < table->nb_of_philos)
		init_threads(table, i++);
}

int	check_table(t_table *table)
{
	if (table->nb_of_philosophers < 2 || \
	table->nb_of_philosophers > 7)
		return (printf("Wrong number of philosophers\n"));
	if (table->time_to_die < 0 || table->time_to_die > 100)
		return (printf("Wrong time to die\n"));
	if (table->time_to_eat < 0 || table->time_to_eat > 100)
		return (printf("Wrong time to eat\n"));
	if (table->time_to_sleep < 0 || table->time_to_sleep > 100)
		return (printf("Wrong time to sleep\n"));
	return (0);
}

int main(int argc, char **argv)
{
	t_table table;

	table = parsing(argv);
	if (table != NULL)
	{
		start_the_party(&table);
		end_of_the_party(&table);
	}
	return (0);
}

t_table parsing(int argc, char **argv)
{
	t_table table;
	
	if (argc < 5)
		return (printf("Wrong amount of arguments\n"));
	table->number_of_philosophers = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if(check_table(&table))
		return (NULL);
	table->philo = (t_philo *)malloc(sizeof(t_philo) * table->number_of_philosophers);
	if (table->philo == NULL)
		return (NULL);
	table->forks = malloc(sizeof(pthread_t) * table->number_of_philosophers);
	if (table->forks == NULL)
		return (NULL);
	return (table);
}

