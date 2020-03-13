/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:43:42 by sdunckel          #+#    #+#             */
/*   Updated: 2020/03/13 12:49:37 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		start_threads(t_options *options)
{
	t_philo		*philo;
	pthread_t	thr;
	int			i;
	time_t		time;

	i = 0;
	time = get_time();
	options->start_time = time;
	while (i < options->philo_num)
	{
		memset(&thr, 0, sizeof(pthread_t));
		philo = &options->philos[i];
		philo->last_eat = time;
		if (pthread_create(&thr, NULL, (void*)philo_routine, philo))
			return (0);
		usleep(10);
		philo->thr = thr;
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
		pthread_detach(options->philos[i].thr);
		pthread_mutex_destroy(&options->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&options->write);
	free(options->forks);
	free(options->philos);
}

void	monitor(t_options *options, int philo_num)
{
	int		i;
	int		finish;

	finish = 0;
	while (!finish)
	{
		i = 0;
		while (i < philo_num)
		{
			if (options->total_eat == philo_num)
			{
				finish = 1;
				break ;
			}
			if (!options->philos[i].eating && get_time()
				- options->philos[i].last_eat > options->time_to_die)
			{
				pthread_mutex_lock(&options->write);
				state_msg2(&options->philos[i], "is dead", options->start_time);
				options->dead = 1;
				finish = 1;
				break ;
			}
			i++;
		}
	}
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
	monitor(&options, options.philo_num);
	destroy_all(&options);
	return (0);
}
