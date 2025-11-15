/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemee <mlemee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 19:20:40 by mlemee            #+#    #+#             */
/*   Updated: 2025/11/15 20:08:33 by mlemee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H 

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

// On doit déclarer s_philo avant, car t_data y fait référence
typedef struct s_philo	t_philo;

// La structure globale avec les règles
typedef struct s_data
{
	long			num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			target_meals;
	long			start_time;

	int				sim_stopped; // Le fameux flag partagé

	pthread_mutex_t	*forks;     // Tableau de mutex (fourchettes)
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;

	t_philo			*philos;    // Tableau de tous les philosophes

}				t_data;

// La structure pour UN seul philosophe
typedef struct s_philo
{
	int         id;
	pthread_t   thread_id;

	int         meal_count;
	long        last_meal_time; // Pour vérifier la mort

	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;

	t_data      *data; // Pointeur vers la structure partagée

}				t_philo;


int	ft_parsing(int argc, char **argv);
int	ft_atol(const char *nptr);

#endif