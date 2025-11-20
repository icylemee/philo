/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemee <mlemee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:58:25 by mlemee            #+#    #+#             */
/*   Updated: 2025/11/20 17:34:18 by mlemee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_monitor(t_data *data)
{
	int	i;
	int	all_full;

	while (1)
	{
		i = 0;
		all_full = 1;
		while (i < data->num_philos)
		{
			if (ft_monitor_bis(data, i, &all_full) == 0)
				return ;
			i ++;
		}
		if (all_full && data->target_meals != -1)
		{
			pthread_mutex_lock(&data->death_mutex);
			data->sim_stopped = 1;
			pthread_mutex_unlock(&data->death_mutex);
			return ;
		}
		ft_usleep(1, data);
	}
}

int	ft_monitor_bis(t_data *data, int i, int *all_full)
{
	pthread_mutex_lock(&data->death_mutex);
	if (ft_get_time() - data->philos[i].last_meal_time
		> data->time_to_die)
	{
		data->sim_stopped = 1;
		pthread_mutex_lock(&data->print_mutex);
		printf("%ld %d died\n", (ft_get_time() - data->start_time),
			data->philos[i].id);
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&data->death_mutex);
		return (0);
	}
	if (data->target_meals != -1 && data->philos[i].meal_count
		< data->target_meals)
			*all_full = 0;
	pthread_mutex_unlock(&data->death_mutex);
	return (1);
}
