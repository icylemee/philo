/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemee <mlemee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 21:41:54 by mlemee            #+#    #+#             */
/*   Updated: 2025/11/15 21:55:00 by mlemee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clean_data(t_data *data, int i)
{
	while (i-- > 0)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
	if (data->print_mutex)
		free(data->print_mutex);
	if (data->death_mutex)
		free(data->death_mutex);
}