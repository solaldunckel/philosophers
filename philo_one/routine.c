/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:22:09 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/25 19:18:39 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	if (philo->pos % 2 == 0)
	{
		pthread_mutex_lock(&philo->options->forks[philo->right]);
		state_msg(philo, "has taken a fork", philo->options->start_time);
		pthread_mutex_lock(&philo->options->forks[philo->left]);
		state_msg(philo, "has taken a fork", philo->options->start_time);
	}
	else
	{
		pthread_mutex_lock(&philo->options->forks[philo->left]);
		state_msg(philo, "has taken a fork", philo->options->start_time);
		pthread_mutex_lock(&philo->options->forks[philo->right]);
		state_msg(philo, "has taken a fork", philo->options->start_time);
	}
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
	pthread_mutex_unlock(&philo->options->forks[philo->left]);
	pthread_mutex_unlock(&philo->options->forks[philo->right]);
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
