/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eahn <eahn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:25:47 by eahn              #+#    #+#             */
/*   Updated: 2024/05/09 01:10:44 by eahn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include <signal.h>
#include <stdlib.h>

// extended signal handler should accept three arguments below
// info->si_pid can be used to identify PID of client process
static void	signal_handler(int signal, siginfo_t *info, void *ptr)
{
	static int	i;
	static char	c;

	(void)ptr;
	if (signal == SIGUSR1)
		c |= (1 << i);
	i++;
	if (i == 8)
	{
		if (c != '\0')
			ft_printf("%c", c);
		else
		{
			usleep(300);
			kill(info->si_pid, SIGUSR1);
		}
		i = 0;
		c = 0;
	}
}

// sigaction offers more control and advanced capabilities
int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: %d\n", getpid());
	ft_printf("Waiting for a message...\n");
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
// sa.sa_flags = SA_SIGINFO: the signal handler is extended one
// sigaction(SIGUSR1, &sa, NULL): register user defined signals

// int sigaction(int signum,
// const struct sigaction *act,struct sigaction *oldact);
// signum: 발생한 시그널 번호
// act: 시그널 발생 시 처리해주기 위한 설정 값들이 존재하는 sigaction 구조체
// oldact: 이전에 등록되었던 sigaction 구조체 (필요하지 않다면 NULL or 0)
