/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 03:11:01 by sdunckel          #+#    #+#             */
/*   Updated: 2019/12/21 13:27:52 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

time_t	get_time()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void 	state_msg(t_philo *philo, char *str)
{
	time_t	time;

	time = get_time();
	pthread_mutex_lock(&philo->options->write);
	ft_putnbr(time - philo->options->start);
	write(1, " ", 1);
	ft_putnbr(philo->pos + 1);
	write(1, " ", 1);
	ft_putstr(str);
	write(1, "\n", 1);
	pthread_mutex_unlock(&philo->options->write);
}
