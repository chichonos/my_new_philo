/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mea <mea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 15:20:04 by mea               #+#    #+#             */
/*   Updated: 2022/06/14 14:55:09 by mea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	actual_time(void)
{
	int					time;
	struct timeval		current_time;
	static int			start_time;

	if (gettimeofday(&current_time, NULL) == -1)
	{
		printf("Error: gettimeofday\n");
		return (0);
	}
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	if (!start_time)
		start_time = time;
	return (time - start_time);
}

void	ft_sleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}
