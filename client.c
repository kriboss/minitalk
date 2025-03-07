/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:30:50 by kbossio           #+#    #+#             */
/*   Updated: 2025/03/07 11:24:48 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
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

void	send_sig(int pid, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 7;
		while (j >= 0)
		{
			if ((str[i] >> j) & 1)
			{
				if (kill(pid, SIGUSR1) == -1)
					exit (EXIT_FAILURE);
			}
			else
			{
				if (kill(pid, SIGUSR2) == -1)
					exit (EXIT_FAILURE);
			}
			usleep(100);
			j--;
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int	pid;

	if (argc != 3 || ft_atoi(argv[1]) <= 0)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	send_sig(pid, argv[2]);
	return (0);
}
