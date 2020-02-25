/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:18:15 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/25 20:31:33 by sdunckel         ###   ########.fr       */
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
	options->forks = sem_open(S_FORK, O_CREAT, 0644, param->philo_num);
	while (i < param->philo_num)
	{
		options->philos[i].pos = i;
		options->philos[i].options = options;
		i++;
	}
	options->write = sem_open(S_WRITE, O_CREAT, 0644, 1);
	return (1);
}
