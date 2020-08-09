/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 16:14:27 by sdunckel          #+#    #+#             */
/*   Updated: 2020/08/06 18:32:53 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	add_int_to_buf(char buf[], time_t num, int *count)
{
	int			len;
	time_t		n;
	int			i;

	len = 0;
	n = num;
	if (n != 0)
	{
		while (n)
		{
			n = n / 10;
			len++;
		}
	}
	else
		len++;
	*count += len;
	i = 0;
	while (i < len)
	{
		buf[*count - i - 1] = num % 10 + 48;
		num = num / 10;
		i++;
	}
}

void	add_str_to_buf(char buf[], char *str, int *count)
{
	int		i;

	i = 0;
	while (str[i])
	{
		buf[*count] = str[i];
		(*count)++;
		i++;
	}
}

int		ft_putstr_fd(int fd, char *str)
{
	int		i;
	char	buf[1024];

	i = 0;
	while (str[i])
	{
		buf[i] = str[i];
		i++;
	}
	write(fd, buf, i);
	return (1);
}

void	state_msg(t_philo *philo, char *str)
{
	char	buf[256];
	int		count;
	time_t	time;

	count = 0;
	time = get_time();
	add_int_to_buf(buf, time - g_options->start_time, &count);
	buf[count++] = ' ';
	add_int_to_buf(buf, philo->num + 1, &count);
	buf[count++] = ' ';
	add_str_to_buf(buf, str, &count);
	buf[count++] = '\n';
	pthread_mutex_lock(&g_options->write);
	if (!g_options->finish)
		write(1, buf, count);
	pthread_mutex_unlock(&g_options->write);
}
