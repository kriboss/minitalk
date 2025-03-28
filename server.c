/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:30:54 by kbossio           #+#    #+#             */
/*   Updated: 2025/03/27 11:44:32 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static size_t	count_digits(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*result;
	unsigned int	num;
	size_t			g;

	g = count_digits(n);
	num = n;
	result = (char *)malloc(sizeof(char) * (g + 1));
	if (!result)
		return (NULL);
	result[g--] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		num = -n;
	}
	if (n == 0)
		result[0] = '0';
	while (num > 0)
	{
		result[g--] = (num % 10) + '0';
		num /= 10;
	}
	return (result);
}

void	get_sig(int signum, siginfo_t *info, void *context)
{
	static int	bit = 0;
	static char	c = 0;

	(void)context;
	c <<= 1;
	if (signum == SIGUSR1)
		c |= 1;
	bit++;
	if (bit == 8)
	{
		if (c == 0)
			kill(info->si_pid, SIGUSR2);
		write(1, &c, 1);
		c = 0;
		bit = 0;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;
	char				*str_pid;
	int					i;

	i = 0;
	sa = (struct sigaction){0};
	sa.sa_sigaction = get_sig;
	sa.sa_flags = SA_SIGINFO;
	pid = getpid();
	str_pid = ft_itoa(pid);
	while (str_pid[i])
		write(1, &str_pid[i++], 1);
	write(1, "\n", 1);
	free(str_pid);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
	}
	return (0);
}
