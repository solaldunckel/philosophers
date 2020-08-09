/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 18:21:04 by sdunckel          #+#    #+#             */
/*   Updated: 2020/08/06 18:26:57 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		only_digit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int		init_params(char **argv, int argc, t_options *opt)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (!only_digit(argv[i]))
			return (PARSE_ERROR);
		i++;
	}
	if ((opt->total_philo = ft_atoi(argv[1])) < 1)
		return (PARSE_ERROR);
	if ((opt->time_to_die = ft_atoi(argv[2])) < 1)
		return (PARSE_ERROR);
	if ((opt->time_to_eat = ft_atoi(argv[3])) < 1)
		return (PARSE_ERROR);
	if ((opt->time_to_sleep = ft_atoi(argv[4])) < 1)
		return (PARSE_ERROR);
	if (argv[5])
		if ((opt->max_eat = ft_atoi(argv[5])) < 1)
			return (PARSE_ERROR);
	return (1);
}

int		init_philos(t_options *opt)
{
	int		i;

	i = 0;
	if (!(opt->philos = ft_calloc(sizeof(t_philo) * opt->total_philo)))
		return (0);
	if (!(opt->forks = ft_calloc(sizeof(pthread_mutex_t) * opt->total_philo)))
		return (0);
	pthread_mutex_init(&opt->write, NULL);
	pthread_mutex_init(&opt->picking, NULL);
	while (i < opt->total_philo)
	{
		pthread_mutex_init(&opt->forks[i], NULL);
		pthread_mutex_init(&opt->philos[i].eating, NULL);
		opt->philos[i].num = i;
		i++;
	}
	return (1);
}
