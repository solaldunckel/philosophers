/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:54:42 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/24 18:45:22 by sdunckel         ###   ########.fr       */
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

void	state_msg(int philo_pos, char *str, time_t start_time)
{
	char	buf[256];
	int		count;
	time_t	time;

	count = 0;
	time = get_time();
	add_int_to_buf(buf, time - start_time, &count);
	buf[count++] = ' ';
	add_int_to_buf(buf, philo_pos + 1, &count);
	buf[count++] = ' ';
	add_str_to_buf(buf, str, &count);
	buf[count++] = '\n';
	write(1, buf, count);
}

void	ft_putstr(char *str)
{
	int		i;
	char	buf[1024];

	i = 0;
	while (str[i])
	{
		buf[i] = str[i];
		i++;
	}
	write(1, buf, i);
}