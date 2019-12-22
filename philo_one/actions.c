/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 13:28:16 by sdunckel          #+#    #+#             */
/*   Updated: 2019/12/21 16:01:31 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void 	take_sticks(t_philo *philo)
{
	pthread_mutex_lock(&philo->options->sticks[philo->left]);
	pthread_mutex_lock(&philo->options->sticks[philo->right]);
	state_msg(philo, "has taken a fork");
}

void 	drop_sticks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->options->sticks[philo->left]);
	pthread_mutex_unlock(&philo->options->sticks[philo->right]);
}

void 	start_eating(t_philo *philo)
{
	philo->time = get_time();
	state_msg(philo, "is eating");
	philo->eat_amount++;
	usleep(philo->options->time_to_eat * 1000);
}

void 	start_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->sleep);
	state_msg(philo, "is sleeping");
	usleep(philo->options->time_to_sleep * 1000);
	pthread_mutex_unlock(&philo->sleep);
}
