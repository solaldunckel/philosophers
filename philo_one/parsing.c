/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:18:15 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/25 18:19:40 by sdunckel         ###   ########.fr       */
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
	if (param->philo_num < 1 || param->time_to_die < 1 || param->max_eat < 0
		|| param->time_to_eat < 1 || param->time_to_sleep < 1)
	{
		ft_putstr("wrong arguments\n");
		return (0);
	}
	return (1);
}

int		create_philos(t_options *options, t_param *param)
{
	int		i;

	i = 0;
	options->param = param;
	if (!(options->philos = ft_calloc(param->philo_num
		* sizeof(t_philo))))
		return (0);
	if (!(options->forks = ft_calloc(param->philo_num
		* sizeof(pthread_mutex_t))))
		return (0);
	pthread_mutex_init(&options->write, NULL);
	while (i < param->philo_num)
	{
		memset(&options->philos[i], 0, sizeof(t_philo));
		options->philos[i].pos = i;
		options->philos[i].options = options;
		options->philos[i].right = i;
		if (i == 0)
			options->philos[i].left = param->philo_num - 1;
		else
			options->philos[i].left = i - 1;
		pthread_mutex_init(&options->forks[i], NULL);
		i++;
	}
	return (1);
}
