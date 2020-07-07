/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:22:09 by sdunckel          #+#    #+#             */
/*   Updated: 2020/07/07 15:15:10 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	real_sleep(int n)
{
	time_t start;

	start = get_time();
	while ((get_time() - start) < n)
		usleep(100);
}

void	eat(t_philo *philo)
{
	while (1)
	{
		if (!philo->options->forks_n[philo->left]
			&& !philo->options->forks_n[philo->right])
		{
			philo->options->forks_n[philo->left] = 1;
			philo->options->forks_n[philo->right] = 1;
			pthread_mutex_lock(&philo->options->forks[philo->left]);
			pthread_mutex_lock(&philo->options->forks[philo->right]);
			state_msg(philo, "has taken a fork", philo->options->start_time);
			state_msg(philo, "has taken a fork", philo->options->start_time);
			break ;
		}
	}
	pthread_mutex_lock(&philo->eating);
	state_msg(philo, "is eating", philo->options->start_time);
	philo->last_eat = get_time();
	real_sleep(philo->options->time_to_eat);
	pthread_mutex_unlock(&philo->eating);
	pthread_mutex_unlock(&philo->options->forks[philo->left]);
	pthread_mutex_unlock(&philo->options->forks[philo->right]);
	philo->options->forks_n[philo->left] = 0;
	philo->options->forks_n[philo->right] = 0;
}

void	philo_routine(t_philo *philo)
{
	int		eat_count;

	eat_count = 0;
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
