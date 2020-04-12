/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:22:09 by sdunckel          #+#    #+#             */
/*   Updated: 2020/04/12 19:09:59 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		create_fork(t_philo *philo)
{
	pid_t		pid;

	pid = fork();
	if (pid == 0)
		philo_routine(philo);
	else if (pid < 0)
		return (pid);
	return (pid);
}

void	eat(t_philo *philo)
{
	sem_wait(philo->options->forks);
	state_msg(philo, "has taken a fork", philo->options->start_time);
	sem_wait(philo->options->forks);
	state_msg(philo, "has taken a fork", philo->options->start_time);
	sem_wait(philo->eating);
	state_msg(philo, "is eating", philo->options->start_time);
	philo->last_eat = get_time();
	usleep(philo->options->time_to_eat * 1000);
	sem_post(philo->eating);
	sem_post(philo->options->forks);
	sem_post(philo->options->forks);
}

void	philo_routine(t_philo *philo)
{
	int			eat_count;

	eat_count = 0;
	if (pthread_create(&philo->monitor, NULL, (void*)monitor, philo))
		return ;
	while (1)
	{
		eat(philo);
		eat_count++;
		if (eat_count == philo->options->max_eat)
			exit(0);
		state_msg(philo, "is sleeping", philo->options->start_time);
		usleep(philo->options->time_to_sleep * 1000);
		state_msg(philo, "is thinking", philo->options->start_time);
	}
}
