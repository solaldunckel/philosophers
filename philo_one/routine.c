/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:22:50 by sdunckel          #+#    #+#             */
/*   Updated: 2020/08/07 04:01:12 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philo *philo)
{
	int right;
	int left;

	right = philo->num;
	left = (philo->num + 1) % g_options->total_philo;
	pthread_mutex_lock(&g_options->forks[right]);
	state_msg(philo, TAKEN_FORK);
	pthread_mutex_lock(&g_options->forks[left]);
	state_msg(philo, TAKEN_FORK);
	pthread_mutex_lock(&philo->eating);
	philo->last_eat = get_time();
	state_msg(philo, EATING);
	if (!g_options->finish)
		ft_sleep(g_options->time_to_eat);
	pthread_mutex_unlock(&philo->eating);
	pthread_mutex_unlock(&g_options->forks[right]);
	pthread_mutex_unlock(&g_options->forks[left]);
}

void	routine(t_philo *philo)
{
	int		eat_count;

	eat_count = 0;
	philo->last_eat = get_time();
	while (!g_options->finish)
	{
		eat(philo);
		if (g_options->finish)
			return ;
		if (++eat_count == g_options->max_eat)
		{
			g_options->total_eat++;
			return ;
		}
		state_msg(philo, SLEEPING);
		ft_sleep(g_options->time_to_sleep);
		state_msg(philo, THINKING);
	}
}
