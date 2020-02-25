/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:22:09 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/25 20:31:03 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->options->forks);
	state_msg(philo, "has taken a fork", philo->options->start_time);
	sem_wait(philo->options->forks);
	state_msg(philo, "has taken a fork", philo->options->start_time);
}

void	start_eat(t_philo *philo)
{
	state_msg(philo, "is eating", philo->options->start_time);
	philo->last_eat = get_time();
	usleep(philo->options->param->time_to_eat * 1000);
	philo->eat_count++;
	if (philo->options->param->max_eat
		&& philo->eat_count <= philo->options->param->max_eat)
	{
		philo->options->total_eat++;
	}
}

void	drop_forks(t_philo *philo)
{
	sem_post(philo->options->forks);
	sem_post(philo->options->forks);
}

void	philo_routine(t_philo *philo)
{
	while (1)
	{
		take_forks(philo);
		start_eat(philo);
		drop_forks(philo);
		state_msg(philo, "is sleeping", philo->options->start_time);
		usleep(philo->options->param->time_to_sleep * 1000);
		state_msg(philo, "is thinking", philo->options->start_time);
	}
}
