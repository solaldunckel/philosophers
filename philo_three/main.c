/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:43:42 by sdunckel          #+#    #+#             */
/*   Updated: 2020/05/07 21:05:43 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		start_threads(t_options *options)
{
	t_philo		*philo;
	int			i;
	time_t		time;

	i = 0;
	time = get_time();
	options->start_time = time;
	while (i < options->philo_num)
	{
		philo = &options->philos[i];
		philo->last_eat = time;
		if (!(philo->pid = fork()))
			philo_routine(philo);
		usleep(100);
		i++;
	}
	return (1);
}

void	destroy_all(t_options *options)
{
	int		i;

	i = 0;
	while (i < options->philo_num)
	{
		sem_close(options->philos[i].eating);
		i++;
	}
	sem_close(options->write);
	sem_close(options->forks);
	free(options->philos);
}

void	monitor(t_philo *philo)
{
	while (!philo->options->finish)
	{
		usleep(5000);
		sem_wait(philo->eating);
		if (get_time() - philo->last_eat > philo->options->time_to_die)
		{
			sem_wait(philo->options->write);
			philo->options->finish = 1;
			state_msg2(philo, "is dead", philo->options->start_time);
		}
		sem_post(philo->eating);
	}
	exit(-1);
}

void	wait_forks(t_options *options)
{
	int		i;
	int		status;

	while (1)
	{
		status = 0;
		if (waitpid(-1, &status, 0) < 0 || ((WIFEXITED(status)
				|| WIFSIGNALED(status)) && status != 0))
		{
			i = 0;
			while (i < options->philo_num)
			{
				kill(options->philos[i].pid, SIGINT);
				i++;
			}
			break ;
		}
	}
}

int		main(int argc, char **argv)
{
	t_options	options;

	ft_bzero(&options, sizeof(t_options));
	if (argc < 5 || argc > 6)
		return (wrong_args("not enough arguments", argv));
	if (!parse_params(&options, argv))
		return (wrong_args("wrong arguments", argv));
	if (!create_philos(&options))
		return (ft_putstr(2, "error : fail creating philos\n"));
	if (!start_threads(&options))
		return (ft_putstr(2, "error : fail creating threads\n"));
	wait_forks(&options);
	destroy_all(&options);
	return (0);
}
