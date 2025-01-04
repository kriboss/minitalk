/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbossio <kbossio@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:30:54 by kbossio           #+#    #+#             */
/*   Updated: 2025/01/04 01:52:23 by kbossio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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

unsigned char	c = 0;
int				bit_count = 0;

void	get_sig(int signum)
{	
    c = c << 1;
    if (signum == SIGUSR1)
        c = c | 1;
    else if (signum == SIGUSR2)
        c = c | 0;
    bit_count++;
    if (bit_count == 8)
    {
        write(1, &c, 1);
        c = 0;
        bit_count = 0;
    }
}

int	main(void)
{
	pid_t	pid;
	char	*str_pid;
	int	i;
	
	if (signal(SIGUSR1, get_sig) == SIG_ERR) {
        perror("Unable to catch SIGUSR1");
        return (1);
    }
    if (signal(SIGUSR2, get_sig) == SIG_ERR) {
        perror("Unable to catch SIGUSR2");
        return (1);
    }
	i = 0;
	pid = getpid();
	str_pid = ft_itoa(pid);
	write(1, str_pid, sizeof(str_pid));
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
