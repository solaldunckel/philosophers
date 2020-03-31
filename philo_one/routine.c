/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:22:09 by sdunckel          #+#    #+#             */
/*   Updated: 2020/03/30 10:05:16 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	while (1)
	{
		if (!philo->options->forks_n[philo->left]
			&& !philo->options->forks_n[philo->right])
		{
			philo->options->forks_n[philo->left] = 1;
			philo->options->forks_n[philo->right] = 1;
			pthread_mutex_lock(&philo->options->forks[philo->left]);
			state_msg(philo, "has taken a fork", philo->options->start_time);
			pthread_mutex_lock(&philo->options->forks[philo->right]);
			state_msg(philo, "has taken a fork", philo->options->start_time);
			break ;
		}
	}
}

void	start_eat(t_philo *philo)
{
	philo->eating = 1;
	state_msg(philo, "is eating", philo->options->start_time);
	philo->last_eat = get_time();
	usleep(philo->options->time_to_eat * 1000);
	philo->eating = 0;
	philo->options->forks_n[philo->left] = 0;
	pthread_mutex_unlock(&philo->options->forks[philo->left]);
	philo->options->forks_n[philo->right] = 0;
	pthread_mutex_unlock(&philo->options->forks[philo->right]);
}

void	philo_routine(t_philo *philo)
{
	int		eat_count;

	eat_count = 0;
	while (1)
	{
		take_forks(philo);
		start_eat(philo);
		eat_count++;
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
