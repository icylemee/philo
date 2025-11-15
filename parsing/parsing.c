/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemee <mlemee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 19:19:16 by mlemee            #+#    #+#             */
/*   Updated: 2025/11/15 20:06:24 by mlemee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_parsing(int argc, char **argv)
{
	int	i;

	if (argc != 5 || argc != 6)
		return (printf("Number of args incorrect\n"), 0);
	i = 0;
	while (++i < argc -1)
	{
		if (atol(argv[i]) < 1)
			return (printf("argv[%d] not strictly positive\n", i), 0);
	}
	if (atol(argv[1]) > 200)
		return (printf("Too much philos\n"), 0);
}

