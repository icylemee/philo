/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemee <mlemee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:53:25 by mlemee            #+#    #+#             */
/*   Updated: 2025/11/20 17:34:02 by mlemee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		ft_print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		ft_print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		ft_print_status(philo, "has taken a fork");
	}
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->sim_stopped)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	ft_eat_bis(philo);
}

void	ft_eat_bis(t_philo *philo)
{
	philo->last_meal_time = ft_get_time();
	philo->meal_count++;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d is eating\n", philo->last_meal_time
		- philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_unlock(&philo->data->death_mutex);
	ft_usleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_print_status(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->sim_stopped)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d %s\n", (ft_get_time() - philo->data->start_time),
		philo->id, s);
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_unlock(&philo->data->death_mutex);
}

void	ft_usleep(long ms, t_data *data)
{
	long	start_time;

	start_time = ft_get_time();
	while (ft_get_time() - start_time < ms)
	{
		if (ft_check_sim_flag(data))
			return ;
		usleep(1000);
	}
}

int	ft_check_sim_flag(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	if (data->sim_stopped)
		return (pthread_mutex_unlock(&data->death_mutex), 1);
	return (pthread_mutex_unlock(&data->death_mutex), 0);
}
