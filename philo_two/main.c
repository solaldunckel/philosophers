/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 16:10:39 by sdunckel          #+#    #+#             */
/*   Updated: 2020/08/09 15:53:43 by sdunckel         ###   ########.fr       */
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
		if (g_options->total_eat == g_options->total_philo)
		{
			g_options->finish = 1;
			return ;
		}
		usleep(2000);
		sem_wait(philo->eating);
		if (get_time() - philo->last_eat > g_options->time_to_die)
		{
			if (!g_options->finish)
				state_msg(philo, DEAD);
			g_options->finish = 1;
			sem_post(philo->eating);
			return ;
		}
		sem_post(philo->eating);
	}
}

int		start_threads(t_options *opt)
{
	int	i;

	opt->start_time = get_time();
	i = -1;
	while (++i < opt->total_philo)
	{
		opt->philos[i].last_eat = get_time();
		if (pthread_create(&opt->philos[i].thr, NULL, (void*)routine,
			&opt->philos[i]))
			return (0);
		usleep(50);
	}
	i = -1;
	while (++i < opt->total_philo)
	{
		if (pthread_create(&opt->philos[i].monitor, NULL, (void*)monitor,
			&opt->philos[i]))
			return (0);
	}
	i = -1;
	while (++i < opt->total_philo)
		pthread_join(opt->philos[i].monitor, NULL);
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
