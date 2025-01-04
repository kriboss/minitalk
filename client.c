/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:30:50 by kbossio           #+#    #+#             */
/*   Updated: 2025/01/04 00:40:10 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_atoi(const char *str)
{
	unsigned int	i;
	int				num;
	int				segno;
	int				cont;

	num = 0;
	segno = 1;
	i = 0;
	cont = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (++cont > 1)
			return (0);
		if (str[i] == '-')
			segno = -segno;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * segno);
}

int	send_sig(int pid, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while(j < 8)
		{
			if ((str[i] >> j) & 1)
			{
				if(kill(pid, SIGUSR1) == -1)
				{
					write(1, "Error", 5);
					return (1);
				}
			}
			else
			{
				if(kill(pid, SIGUSR2) == -1)
				{
					write(1, "Error", 5);
					return (1);
				}
			}
			usleep(100000);
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int	pid;
	sigset_t	signal;
	char str[] = "ciao";

	/*
	sigemptyset(&signal);
	sigaddset(&signal, SIGUSR1);
	*/
	printf("pid: %s", argv[1]);
	pid = ft_atoi(argv[1]);
	send_sig(pid, str);
	write(1, "ciao", 4);
	return (0);
}