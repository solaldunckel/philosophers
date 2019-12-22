/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 13:28:16 by sdunckel          #+#    #+#             */
/*   Updated: 2019/12/22 21:06:03 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	death(t_philo *philo)
{
	while (1)
	{
		if (philo->time + philo->options->time_to_die < get_time())
		{
			state_msg(philo, "is dead");
			pthread_mutex_lock(&philo->options->write);
			pthread_mutex_unlock(&philo->options->mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->mutex);
	}
}

void	eat_count(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (philo->eat_amount == philo->options->max_eat)
		{
			philo->options->total++;
			return ;
		}
		pthread_mutex_unlock(&philo->mutex);
	}
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->options->sticks[philo->pos]);
	state_msg(philo, "has taken a fork");
	if (philo->pos == philo->options->num)
		pthread_mutex_lock(&philo->options->sticks[philo->pos + 1
			- philo->options->num]);
	else
		pthread_mutex_lock(&philo->options->sticks[philo->pos + 1]);
	state_msg(philo, "has taken a fork");
}

void	start_eat(t_philo *philo)
{
	philo->time = get_time();
	state_msg(philo, "is eating");
	usleep(philo->options->time_to_eat * 1000);
	philo->eat_amount++;
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->options->sticks[philo->pos]);
	if (philo->pos == philo->options->num)
		pthread_mutex_unlock(&philo->options->sticks[philo->pos + 1
			- philo->options->num]);
	else
		pthread_mutex_unlock(&philo->options->sticks[philo->pos + 1]);
}

void	start_sleep(t_philo *philo)
{
	state_msg(philo, "is sleeping");
	usleep(philo->options->time_to_sleep * 1000);
}

void 	rules(t_philo *philo)
{
	pthread_t	thr;

	philo->time = get_time();
	if (pthread_create(&thr, NULL, (void*)death, philo))
		return ;
	while (1)
	{
		take_forks(philo);
		start_eat(philo);
		drop_forks(philo);
		start_sleep(philo);
		state_msg(philo, "is thinking");
	}
}
