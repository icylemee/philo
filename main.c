/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemee <mlemee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 19:19:22 by mlemee            #+#    #+#             */
/*   Updated: 2025/11/20 17:33:02 by mlemee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	int		i;

	i = -1;
	if (!ft_parsing(argc, argv))
		return (-1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (printf("Error malloc\n"), -1);
	if (!ft_init_data_node(data, argv, argc))
		return (free(data), -1);
	ft_start_simulation(data);
	while (++i < data->num_philos)
		pthread_join(data->philos[i].thread_id, NULL);
	ft_full_cleanup(data);
	return (0);
}

int	ft_init_data_node(t_data *data, char **argv, int argc)
{
	data->num_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		data->target_meals = ft_atol(argv[5]);
	else
		data->target_meals = -1;
	data->start_time = 0;
	data->sim_stopped = 0;
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (printf("Error malloc\n"), 0);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (free(data->philos), printf("Error malloc\n"), 0);
	if (!ft_init_mutex(data))
		return (free(data->philos), free(data->forks),
			printf("Err init mut\n"), 0);
	ft_init_philos(data);
	return (1);
}

void	ft_init_philos(t_data *data)
{
	int	j;

	j = -1;
	while (++j < data->num_philos)
	{
		data->philos[j].id = j + 1 ;
		data->philos[j].meal_count = 0;
		data->philos[j].last_meal_time = 0;
		data->philos[j].data = data;
		data->philos[j].left_fork = &data->forks[j];
		if (j == data->num_philos - 1)
			data->philos[j].right_fork = &data->forks[0];
		else
			data->philos[j].right_fork = &data->forks[j + 1];
	}
}

int	ft_init_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			return (0);
		}
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		i = -1;
		while (++i < data->num_philos)
			pthread_mutex_destroy(&data->forks[i]);
		return (0);
	}
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
	{
		ft_clean_mutex(data);
		return (0);
	}
	return (1);
}

void	ft_clean_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->print_mutex);
}
// ./philo 2 800 200 200 --> check vol fourchette 

// ./philo 1 310 200 200 --> check mort entre 310 et 320

// ./philo 5 800 200 200 --> perosnne doit mourir 

// ./philo 4 310 200 100 --> un doit mourir 

// ./philo 4 410 200 200 --> test tendu, 10ms de battement ,
// personne ne doit crever 
