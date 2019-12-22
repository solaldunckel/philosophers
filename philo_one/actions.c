/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 13:28:16 by sdunckel          #+#    #+#             */
/*   Updated: 2019/12/22 13:23:41 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	death(t_philo *philo)
{
	while (philo->options->total != philo->options->num)
	{
		if (philo->time + philo->options->time_to_die < get_time())
		{
			state_msg(philo, "is dead");
			pthread_mutex_lock(&philo->options->write);
			pthread_mutex_unlock(&philo->options->mutex);
			return ;
		}
	}
	pthread_mutex_lock(&philo->options->write);
	ft_putstr("all philosophers have eat enough :)\n");
	pthread_mutex_unlock(&philo->options->mutex);
}

void 	rules(t_philo *philo)
{
	pthread_t	thr;

	philo->time = get_time();
	if (pthread_create(&thr, NULL, (void*)death, philo))
		return ;
	pthread_detach(thr);
	while (1)
	{
		take_sticks(philo);
		start_eating(philo);
		start_sleep(philo);
		state_msg(philo, "is thinking");
	}
}

void 	take_sticks(t_philo *philo)
{
	pthread_mutex_lock(&philo->options->sticks[philo->left]);
	state_msg(philo, "has taken a fork");
	pthread_mutex_lock(&philo->options->sticks[philo->right]);
	state_msg(philo, "has taken a fork");
}

void 	start_eating(t_philo *philo)
{
	philo->time = get_time();
	state_msg(philo, "is eating");
	usleep(philo->options->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->options->sticks[philo->left]);
	pthread_mutex_unlock(&philo->options->sticks[philo->right]);
	philo->eat_amount++;
	if (philo->eat_amount == philo->options->max_eat)
		philo->options->total++;
}

void 	start_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->sleep);
	state_msg(philo, "is sleeping");
	usleep(philo->options->time_to_sleep * 1000);
	pthread_mutex_unlock(&philo->sleep);
}
