/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:22:09 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/24 19:10:48 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->options->forks[philo->pos]);
	state_msg(philo->pos, "has taken a fork", philo->options->start_time);
	if (philo->pos == philo->options->param->philo_num - 1)
		pthread_mutex_lock(&philo->options->forks[philo->pos + 1
			- philo->options->param->philo_num]);
	else
		pthread_mutex_lock(&philo->options->forks[philo->pos + 1]);
	state_msg(philo->pos, "has taken a fork", philo->options->start_time);
}

void	start_eat(t_philo *philo)
{
	philo->last_eat = get_time();
	state_msg(philo->pos, "is eating", philo->options->start_time);
	usleep(philo->options->param->time_to_eat * 1000);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->options->forks[philo->pos]);
	if (philo->pos == philo->options->param->philo_num - 1)
		pthread_mutex_unlock(&philo->options->forks[philo->pos + 1
			- philo->options->param->philo_num]);
	else
		pthread_mutex_unlock(&philo->options->forks[philo->pos + 1]);
}

void	philo_routine(t_philo *philo)
{
	philo->last_eat = get_time();
	while (1)
	{
		take_forks(philo);
		start_eat(philo);
		drop_forks(philo);
		state_msg(philo->pos, "is sleeping", philo->options->start_time);
		usleep(philo->options->param->time_to_sleep * 1000);
		state_msg(philo->pos, "is thinking", philo->options->start_time);
	}
}
