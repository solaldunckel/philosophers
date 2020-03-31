/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:43:42 by sdunckel          #+#    #+#             */
/*   Updated: 2020/03/30 16:09:50 by sdunckel         ###   ########.fr       */
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
	pthread_mutex_destroy(&options->dead);
}

void	monitor(t_philo *philo)
{
	while (!philo->options->finish)
	{
		if (philo->options->total_eat == philo->options->philo_num)
		{
			philo->options->finish = 1;
			break ;
		}
		if (!philo->eating && get_time()
			- philo->last_eat > philo->options->time_to_die
			&& !philo->options->finish)
		{
			philo->options->finish = 1;
			state_msg2(philo, "is dead", philo->options->start_time);
			pthread_mutex_lock(&philo->options->write);
			break ;
		}
		usleep(5000);
		if (philo->options->finish)
			return ;
	}
	pthread_mutex_unlock(&philo->options->dead);
}

void	start_monitor(t_options *options, t_philo *philo, int philo_num)
{
	int			i;

	i = 0;
	pthread_mutex_lock(&options->dead);
	while (i < philo_num)
	{
		if (pthread_create(&philo[i].monitor, NULL, (void*)monitor, &philo[i]))
			return ;
		pthread_detach(philo[i].monitor);
		usleep(10);
		i++;
	}
	return ;
}

int		main(int argc, char **argv)
{
	t_options	options;

	memset(&options, 0, sizeof(t_options));
	if (argc < 5 || argc > 6)
		return (ft_putstr("wrong number of arguments\n"));
	if (!parse_params(&options, argv))
		return (ft_putstr("wrong arguments\n"));
	if (!create_philos(&options))
		return (ft_putstr("fail creating philos\n"));
	if (!start_threads(&options))
		return (ft_putstr("fail creating threads\n"));
	start_monitor(&options, options.philos, options.philo_num);
	pthread_mutex_lock(&options.dead);
	destroy_all(&options);
	return (0);
}
