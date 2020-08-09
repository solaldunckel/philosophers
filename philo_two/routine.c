/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:22:50 by sdunckel          #+#    #+#             */
/*   Updated: 2020/08/09 15:47:04 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philo *philo)
{
	sem_wait(g_options->picking);
	sem_wait(g_options->forks);
	state_msg(philo, TAKEN_FORK);
	sem_wait(g_options->forks);
	state_msg(philo, TAKEN_FORK);
	sem_post(g_options->picking);
	philo->last_eat = get_time();
	state_msg(philo, EATING);
	sem_wait(philo->eating);
	if (!g_options->finish)
		ft_sleep(g_options->time_to_eat);
	sem_post(philo->eating);
	sem_post(g_options->forks);
	sem_post(g_options->forks);
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
