/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlemee <mlemee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:05:20 by mlemee            #+#    #+#             */
/*   Updated: 2025/11/15 20:06:02 by mlemee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atol(const char *nptr)
{
	int		i;
	int		neg;
	long	result;

	i = 0;
	result = 0;
	neg = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			neg = -1;
		i ++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result *= 10;
		result += (nptr[i] - '0');
		i ++;
	}
	if (neg == -1)
		result = (long int)result * neg;
	return (result);
}

// int main(int argc, char *argv[])
// {
// 	if (argc == 2)
// 	{
// 		printf("ma fonction : %d\n", ft_atoi(argv[1]));
// 		printf("VRAIE fonction : %d\n", atoi(argv[1]));
// 	}
// }
