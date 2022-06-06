/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mea <mea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 13:58:39 by mea               #+#    #+#             */
/*   Updated: 2022/06/06 13:16:13 by mea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	start_the_party(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->nb_of_philo)
		init_forks(table, i++);
	i = 0;
	while (i < table->nb_of_philo)
		init_philo(table, i++);
	i = 0;
	while (i < table->nb_of_philo)
		if(init_threads(table, i++))
			return ;	
	return ;
}

int main(int argc, char **argv)
{
	t_table table;

	parsing(argc, argv, &table);
	start_the_party(&table);
	//end_of_the_party(&table);
	return (0);
}

