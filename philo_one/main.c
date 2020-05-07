/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:43:42 by sdunckel          #+#    #+#             */
/*   Updated: 2020/05/08 00:09:07 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		start_threads(t_options *options)
{
	t_philo		*philo;
	int			i;

	i = 0;
	options->start_time = get_time();
	while (i < options->philo_num)
	{
		philo = &options->philos[i];
		philo->last_eat = get_time();
		if (pthread_create(&philo->thr, NULL, (void*)philo_routine, philo))
			return (0);
		pthread_detach(philo->thr);
		usleep(10);
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
		pthread_mutex_destroy(&options->forks[i]);
		i++;
	}
	free(options->forks);
	free(options->forks_n);
	free(options->philos);
	pthread_mutex_destroy(&options->write);
}

void	monitor(t_philo *philo)
{
	while (!philo->options->finish)
	{
		if (philo->options->total_eat == philo->options->philo_num)
			break ;
		if (philo->finished)
			return ;
		usleep(5000);
		pthread_mutex_lock(&philo->eating);
		if (get_time() - philo->last_eat > philo->options->time_to_die
			&& !philo->options->finish)
		{
			philo->options->finish = 1;
			state_msg2(philo, "is dead", philo->options->start_time);
		}
		pthread_mutex_unlock(&philo->eating);
	}
	philo->options->finish = 1;
}

void	start_monitor(t_philo *philo, int philo_num)
{
	int		i;

	i = 0;
	while (i < philo_num)
	{
		if (pthread_create(&philo[i].monitor, NULL, (void*)monitor, &philo[i]))
			return ;
		usleep(10);
		i++;
	}
	i = 0;
	while (i < philo_num)
	{
		pthread_join(philo[i].thr, NULL);
		pthread_join(philo[i].monitor, NULL);
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_options	options;

	memset(&options, 0, sizeof(t_options));
	if (argc < 5 || argc > 6)
		return (wrong_args("not enough arguments", argv));
	if (!parse_params(&options, argv))
		return (wrong_args("wrong arguments", argv));
	if (!create_philos(&options))
		return (ft_putstr(2, "error : fail creating philos\n"));
	if (!start_threads(&options))
		return (ft_putstr(2, "error : fail creating threads\n"));
	start_monitor(options.philos, options.philo_num);
	destroy_all(&options);
	return (0);
}
