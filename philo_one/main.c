/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:43:42 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/25 19:18:13 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		start_threads(t_options *options, t_param *param)
{
	t_philo		*philo;
	pthread_t	thr;
	int			i;
	time_t		time;

	i = 0;
	time = get_time();
	options->start_time = time;
	while (i < param->philo_num)
	{
		philo = &options->philos[i];
		philo->last_eat = time;
		if (pthread_create(&thr, NULL, (void*)philo_routine, philo))
			return (0);
		usleep(10);
		philo->thr = &thr;
		i++;
	}
	return (1);
}

void	destroy_all(t_options *options, t_param *param)
{
	int		i;

	i = 0;
	while (i < param->philo_num)
	{
		pthread_mutex_destroy(&options->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&options->write);
	free(options->forks);
	free(options->philos);
}

void	monitor(t_options *options, t_param *param)
{
	int		i;

	options->finish = 0;
	while (!options->finish)
	{
		i = 0;
		while (i < param->philo_num)
		{
			if (get_time() - options->philos[i].last_eat > param->time_to_die)
			{
				pthread_mutex_lock(&options->write);
				state_msg2(&options->philos[i], "is dead", options->start_time);
				options->finish = 1;
				break ;
			}
			else if (options->total_eat == param->philo_num)
			{
				pthread_mutex_lock(&options->write);
				options->finish = 1;
				break ;
			}
			i++;
		}
	}
}

int		main(int argc, char **argv)
{
	t_param		param;
	t_options	options;

	ft_bzero(&param, sizeof(t_param));
	ft_bzero(&options, sizeof(t_options));
	if (argc < 5 || argc > 6)
	{
		ft_putstr("wrong number of arguments\n");
		return (1);
	}
	if (!parse_params(&param, argv))
		return (1);
	if (!create_philos(&options, &param))
	{
		ft_putstr("fail creating philos\n");
		return (1);
	}
	if (!start_threads(&options, &param))
	{
		ft_putstr("fail creating threads\n");
		return (1);
	}
	monitor(&options, &param);
	destroy_all(&options, &param);
	return (0);
}
