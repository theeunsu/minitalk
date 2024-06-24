/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:51:41 by eahn              #+#    #+#             */
/*   Updated: 2024/05/09 00:59:38 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include <signal.h>

int	ft_atoi(const char *str)
{
	int	minus;
	int	result;

	minus = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		minus *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	result = result * minus;
	if (result > 2147483647)
		return (-1);
	else if (result < -2147483648)
		return (0);
	return (result);
}

// send char in octet to server
// usleep(100): a delay of 100 microseconds btw each signal trasmission
// if not, signals could be sent too fast, causing data loss by server
static void	send_bit(pid_t pid, char octet)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((octet & (1 << i)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		usleep(100);
	}
}

int	main(int ac, char **av)
{
	pid_t	pid;
	int		i;

	i = 0;
	if (ac != 3)
	{
		ft_printf("Error: too many arguments!\n");
		ft_printf("Use double quotes to send your messages.\n");
		ft_printf("Example: ./client 1234 \"Hello, World!\" \n");
		return (0);
	}
	pid = ft_atoi(av[1]);
	while (av[2][i])
	{
		send_bit(pid, av[2][i]);
		i++;
	}
	send_bit(pid, '\n');
	return (0);
}
