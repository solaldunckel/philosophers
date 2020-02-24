/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:43:42 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/24 19:19:19 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		parse_params(t_param *param, char **argv)
{
	param->philo_num = ft_atoi(argv[1]);
	param->time_to_die = ft_atoi(argv[2]);
	param->time_to_eat = ft_atoi(argv[3]);
	param->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		param->max_eat = ft_atoi(argv[5]);
	else
		param->max_eat = 0;
	if (param->philo_num < 1 || param->time_to_die < 1 || param->max_eat < 1
		|| param->time_to_eat < 1 || param->time_to_sleep < 1)
		return (0);
	return (1);
}

int		create_philos(t_options *options, t_param *param)
{
	int		i;

	i = 0;
	options->param = param;
	if (!(options->philos = ft_calloc(param->philo_num * sizeof(t_philo))))
		return (0);
	if (!(options->forks = ft_calloc(param->philo_num * sizeof(pthread_mutex_t))))
		return (0);
	while (i < param->philo_num)
	{
		options->philos[i].pos = i;
		options->philos[i].options = options;
		pthread_mutex_init(&options->forks[i], NULL);
		i++;
	}
	return (1);
}

int		create_philos_thr(t_philo *philo)
{
	pthread_t thr;

	if (pthread_create(&thr, NULL, (void*)philo_routine, philo))
		return (0);
	philo->thr = &thr;
	return (1);
}

int		start_threads(t_options *options, t_param *param)
{
	int			i;

	i = 0;
	options->start_time = get_time();
	while (i < param->philo_num)
	{
		if (!(create_philos_thr(&options->philos[i])))
			return (0);
		usleep(10);
		i++;
	}
	return (1);
}

void	monitor(t_options *options, t_param *param)
{
	int		i;
	int		dead;

	dead = 0;
	i = 0;
	while (!dead)
	{
		i = 0;
		while (i < param->philo_num)
		{
			//pthread_detach(*options->philos[i].thr);
			if (options->philos[i].last_eat + param->time_to_die < get_time())
			{
				state_msg(i, "is dead", options->start_time);
				dead = 1;
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

	ft_bzero(&param, sizeof(param));
	ft_bzero(&options, sizeof(options));
	if (argc < 5 || argc > 6)
	{
		ft_putstr("wrong number of arguments\n");
		return (1);
	}
	if (!parse_params(&param, argv))
	{
		ft_putstr("wrong arguments\n");
		return (1);
	}
	if (!create_philos(&options, &param))
	{
		ft_putstr("fail creating philos\n");
		return (1);
	}
	if (!start_threads(&options, &param))
	{
		ft_putstr("fail starting philos\n");
		return (1);
	}
	monitor(&options, &param);
	return (0);
}
