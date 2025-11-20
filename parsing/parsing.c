/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemee <mlemee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 19:19:16 by mlemee            #+#    #+#             */
/*   Updated: 2025/11/20 17:33:36 by mlemee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_all_digits(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (0);
	}
	return (1);
}

int	ft_parsing(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (printf("Number of args incorrect\n"), 0);
	i = 0;
	while (++i < argc)
	{
		if (!ft_is_all_digits(argv[i]))
			return (printf("argv[%d] invalid\n", i), 0);
		if (ft_atol(argv[i]) < 1 || ft_atol(argv[i]) > INT_MAX)
			return (printf("argv[%d] invalid\n", i), 0);
	}
	if (ft_atol(argv[1]) > 200)
		return (printf("Too much philos\n"), 0);
	return (1);
}
