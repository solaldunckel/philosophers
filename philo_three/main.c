/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:43:42 by sdunckel          #+#    #+#             */
/*   Updated: 2020/03/30 16:54:11 by sdunckel         ###   ########.fr       */
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
		usleep(10);
		i++;
	}
	return (1);
}

void	destroy_all(t_options *options)
{
	sem_unlink(S_FORK);
	sem_unlink(S_WRITE);
	sem_unlink(S_DEAD);
	free(options->philos);
}

void	monitor(t_philo *philo)
{
	while (!philo->options->finish)
	{
		if (!philo->eating && get_time()
			- philo->last_eat > philo->options->time_to_die
			&& !philo->options->finish)
		{
			sem_wait(philo->options->dead);
			philo->options->finish = 1;
			state_msg2(philo, "is dead", philo->options->start_time);
			sem_wait(philo->options->write);
			break ;
		}
		usleep(10000);
		if (philo->options->finish)
			return ;
	}
	exit(0);
}

int		wait_forks(t_options *options)
{
	int		i;
	int		status;

	while (1)
	{
		status = 0;
		if (waitpid(-1, &status, 0) < 0 || WIFEXITED(status))
		{
			i = -1;
			while (++i < options->philo_num)
				kill(options->philos[i].pid, SIGINT);
			exit(WEXITSTATUS(status));
		}
	}
}

int		main(int argc, char **argv)
{
	t_options	options;
	int			i;

	sem_unlink(S_FORK);
	sem_unlink(S_WRITE);
	sem_unlink(S_DEAD);
	ft_bzero(&options, sizeof(t_options));
	if (argc < 5 || argc > 6)
		return (ft_putstr("wrong number of arguments\n"));
	if (!parse_params(&options, argv))
		return (ft_putstr("wrong arguments\n"));
	if (!create_philos(&options))
		return (ft_putstr("fail creating philos\n"));
	if (!start_threads(&options))
		return (ft_putstr("fail creating threads\n"));
	wait_forks(&options);
	destroy_all(&options);
	return (0);
}
