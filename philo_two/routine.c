/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:22:09 by sdunckel          #+#    #+#             */
/*   Updated: 2020/06/08 19:19:01 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	real_sleep(int n)
{
	time_t start;

	start = get_time();
	while (1)
	{
		if (get_time() - start >= n)
			break ;
		usleep(10);
	}
}

void	eat(t_philo *philo)
{
	sem_wait(philo->options->picking);
	sem_wait(philo->options->forks);
	state_msg(philo, "has taken a fork", philo->options->start_time);
	sem_wait(philo->options->forks);
	state_msg(philo, "has taken a fork", philo->options->start_time);
	sem_post(philo->options->picking);
	sem_wait(philo->eating);
	state_msg(philo, "is eating", philo->options->start_time);
	philo->last_eat = get_time();
	real_sleep(philo->options->time_to_eat);
	sem_post(philo->eating);
	sem_post(philo->options->forks);
	sem_post(philo->options->forks);
}

void	philo_routine(t_philo *philo)
{
	int		eat_count;

	eat_count = 0;
	philo->last_eat = get_time();
	while (1)
	{
		eat(philo);
		eat_count++;
		if (eat_count == philo->options->max_eat)
		{
			philo->finished = 1;
			philo->options->total_eat++;
			return ;
		}
		state_msg(philo, "is sleeping", philo->options->start_time);
		real_sleep(philo->options->time_to_sleep);
		state_msg(philo, "is thinking", philo->options->start_time);
	}
}
