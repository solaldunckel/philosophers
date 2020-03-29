/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:22:09 by sdunckel          #+#    #+#             */
/*   Updated: 2020/03/29 07:23:09 by sdunckel         ###   ########.fr       */
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

int		start_eat(t_philo *philo)
{
	philo->eating = 1;
	state_msg(philo, "is eating", philo->options->start_time);
	philo->last_eat = get_time();
	usleep(philo->options->time_to_eat * 1000);
	philo->eating = 0;
	return (1);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->options->forks[philo->left]);
	pthread_mutex_unlock(&philo->options->forks[philo->right]);
}

void	philo_routine(t_philo *philo)
{
	int		eat_count;

	eat_count = 0;
	while (1)
	{
		take_forks(philo);
		if (start_eat(philo))
			eat_count++;
		drop_forks(philo);
		if (eat_count == philo->options->max_eat)
		{
			philo->options->total_eat++;
			return ;
		}
		state_msg(philo, "is sleeping", philo->options->start_time);
		usleep(philo->options->time_to_sleep * 1000);
		state_msg(philo, "is thinking", philo->options->start_time);
	}
}
