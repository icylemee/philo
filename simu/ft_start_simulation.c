/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_simulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemee <mlemee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:26:35 by mlemee            #+#    #+#             */
/*   Updated: 2025/11/20 15:53:40 by mlemee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_start_simulation(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = ft_get_time();
	while (++i < data->num_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		if (pthread_create(&data->philos[i].thread_id, NULL,
				ft_routine, &data->philos[i]))
			return (printf("Err init threads\n"), -1);
	}
	ft_monitor(data);
	return (1);
}

void	*ft_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_print_status(philo, "has taken a fork");
	ft_usleep(philo->data->time_to_die + 1, philo->data);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
		return (ft_one_philo(philo));
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat, philo->data);
	while (1)
	{
		if (ft_check_sim_flag(philo->data))
			break ;
		ft_eat(philo);
		if (ft_check_sim_flag(philo->data))
			break ;
		ft_sleep(philo);
		if (ft_check_sim_flag(philo->data))
			break ;
		ft_think(philo);
		if (ft_check_sim_flag(philo->data))
			break ;
	}
	return (NULL);
}

void	ft_sleep(t_philo *philo)
{
	ft_print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo->data);
}

void	ft_think(t_philo *philo)
{
	ft_print_status(philo, "is thinking");
	if (philo->data->num_philos % 2 != 0)
		ft_usleep(1, philo->data);
}
