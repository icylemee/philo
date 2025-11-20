/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemee <mlemee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 19:20:40 by mlemee            #+#    #+#             */
/*   Updated: 2025/11/20 17:25:03 by mlemee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H 
# define INT_MAX 2147483647

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	long			num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			target_meals;
	long			start_time;

	int				sim_stopped;

	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;

	t_philo			*philos;

}				t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;

	int				meal_count;
	long			last_meal_time;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	t_data			*data;
}				t_philo;

int		ft_parsing(int argc, char **argv);
long	ft_atol(const char *nptr);
void	*ft_routine(void *arg);
long	ft_get_time(void);
void	ft_monitor(t_data *data);
void	ft_print_status(t_philo *philo, char *s);
int		ft_start_simulation(t_data *data);
void	ft_full_cleanup(t_data *data);
int		ft_init_data_node(t_data *data, char **argv, int argc);
int		ft_init_mutex(t_data *data);
void	ft_init_philos(t_data *data);
void	ft_clean_mutex(t_data *data);
void	ft_usleep(long ms, t_data *data);
int		ft_check_sim_flag(t_data *data);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
void	*ft_one_philo(t_philo *philo);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_eat_bis(t_philo *philo);
int		ft_monitor_bis(t_data *data, int i, int *all_full);

#endif