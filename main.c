/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemee <mlemee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 19:19:22 by mlemee            #+#    #+#             */
/*   Updated: 2025/11/15 22:00:47 by mlemee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philo;

	if (!ft_parsing(argc, argv))
		return (-1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (printf("Error malloc\n"), -1);
	ft_init_data_node(data, argv);
}

void	*ft_init_data_node(t_data *data, char **argv)
{
	data->num_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (atol(argv[5]))
		data->target_meals = ft_atol(argv[5]);
	data->start_time = 0;
	data->sim_stopped = 0;
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (free(data), printf("Error malloc\n"), NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (free(data->philos), free(data), printf("Error malloc\n"), NULL);
	ft_init_mutex(data);
}

void	*ft_init_mutex(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (ft_clean_data(data, i), printf("Err whil init mtx\n"), NULL);
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (ft_clean_data(data, i), printf("Err while init mutex\n"), NULL);
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
		return (ft_clean_data(data, i), printf("Err while init mutex\n"), NULL);
	while (++j < data->num_philos)
	{
		data->philos[i].id = j + 1 ;
		data->philos[i].meal_count = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].data = data;
		//initialiser la suite.
	}
}


