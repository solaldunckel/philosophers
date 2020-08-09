/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 16:10:39 by sdunckel          #+#    #+#             */
/*   Updated: 2020/08/08 16:03:50 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		clear_all(t_options *opt)
{
	int i;

	i = 0;
	while (i < opt->total_philo)
	{
		sem_close(opt->philos[i].eating);
		i++;
	}
	sem_close(opt->write);
	sem_close(opt->picking);
	sem_close(opt->forks);
	free(opt->philos);
	return (0);
}

void	monitor(t_philo *philo)
{
	while (!g_options->finish)
	{
		sem_wait(philo->eating);
		if (get_time() - philo->last_eat > g_options->time_to_die)
		{
			sem_wait(g_options->write);
			if (!g_options->finish)
				state_msg2(philo, DEAD);
			g_options->finish = 1;
			sem_post(philo->eating);
			break ;
		}
		sem_post(philo->eating);
		usleep(1000);
	}
	exit(-1);
}

int		start_threads(t_options *opt)
{
	int	i;
	int status;

	opt->start_time = get_time();
	i = -1;
	while (++i < opt->total_philo)
	{
		opt->philos[i].last_eat = get_time();
		if (!(opt->philos[i].pid = fork()))
			routine(&opt->philos[i]);
		usleep(100);
	}
	while (1)
	{
		status = 0;
		if (waitpid(-1, &status, 0) < 0 || ((WIFEXITED(status)
				|| WIFSIGNALED(status)) && status != 0))
		{
			i = -1;
			while (++i < opt->total_philo)
				kill(opt->philos[i].pid, SIGINT);
			break ;
		}
	}
	return (1);
}

int		main(int argc, char **argv)
{
	t_options	options;

	g_options = &options;
	memset(&options, 0, sizeof(t_options));
	if (argc < 5 || argc > 6 || !init_params(argv, argc, &options))
		return (ft_putstr_fd(2, "parsing error\n"));
	if (!init_philos(&options))
		return (ft_putstr_fd(2, "fail allocating memory\n"));
	if (!start_threads(&options))
		return (ft_putstr_fd(2, "fail starting threads\n"));
	return (clear_all(&options));
}
