/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:22:09 by sdunckel          #+#    #+#             */
/*   Updated: 2020/03/29 07:24:59 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		create_fork(t_philo *philo)
{
	pid_t		pid;

	pid = fork();
	if (pid == 0)
	{
		philo_routine(philo);
		exit(0);
	}
	else if (pid < 0)
		return (pid);
	return (pid);
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
	sem_post(philo->options->forks);
	sem_post(philo->options->forks);
}

void	monitor_routine(t_philo *philo)
{
	int		i;

	i = 0;
	while (1)
	{
		if (philo->options->max_eat
			&& philo->options->max_eat == philo->eat_count)
			exit(0);
		if (!philo->eating && get_time()
			- philo->last_eat > philo->options->time_to_die)
		{
			sem_wait(philo->options->write);
			state_msg2(philo, "is dead", philo->options->start_time);
			while (i < philo->options->philo_num)
			{
				if (philo->options->philos[i].pid != philo->pid)
					kill(philo->options->philos[i].pid, SIGINT);
				i++;
			}
			destroy_all(philo->options);
			kill(philo->pid, SIGINT);
		}
	}
}

void	philo_routine(t_philo *philo)
{
	int			eat_count;
	pthread_t	thr;

	eat_count = 0;
	if (pthread_create(&thr, NULL, (void*)monitor_routine, philo))
		return ;
	while (1)
	{
		sem_wait(philo->options->forks);
		state_msg(philo, "has taken a fork", philo->options->start_time);
		sem_wait(philo->options->forks);
		state_msg(philo, "has taken a fork", philo->options->start_time);
		if (start_eat(philo))
			philo->eat_count++;
		drop_forks(philo);
		if (philo->options->max_eat
			&& philo->options->max_eat == philo->eat_count)
			break ;
		state_msg(philo, "is sleeping", philo->options->start_time);
		usleep(philo->options->time_to_sleep * 1000);
		state_msg(philo, "is thinking", philo->options->start_time);
	}
	exit(0);
}
