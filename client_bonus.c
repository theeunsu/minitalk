/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 00:59:54 by eahn              #+#    #+#             */
/*   Updated: 2024/05/09 14:01:32 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include <signal.h>
#include <stdlib.h>

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

static void	confirm_signal(int signal)
{
	if (signal == SIGUSR1)
		ft_printf("Message Recieved!\n");
	exit(1);
}

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
	send_bit(pid, '\0');
	signal(SIGUSR1, confirm_signal);
	while (1)
		pause();
	return (0);
}

// MacOS uses UTF-8 (unicode first bytes: 110xxxxx, 1110xxxx, 11110xxx)
// Terminal recognizes number of bytes composing the character
// based on format of the first bytes
