/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:18:15 by sdunckel          #+#    #+#             */
/*   Updated: 2020/03/30 11:46:06 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		parse_params(t_options *options, char **argv)
{
	options->philo_num = ft_atoi(argv[1]);
	options->time_to_die = ft_atoi(argv[2]);
	options->time_to_eat = ft_atoi(argv[3]);
	options->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		options->max_eat = ft_atoi(argv[5]);
	else
		options->max_eat = 0;
	if (options->philo_num < 1 || options->time_to_die < 1
		|| options->max_eat < 0 || options->time_to_eat < 1
		|| options->time_to_sleep < 1)
		return (0);
	return (1);
}

int		create_philos(t_options *options)
{
	int		i;

	i = -1;
	if (!(options->philos = ft_calloc(options->philo_num
		* sizeof(t_philo))))
		return (0);
	options->forks = sem_open(S_FORK, O_CREAT, 0644, options->philo_num);
	options->write = sem_open(S_WRITE, O_CREAT, 0644, 1);
	options->dead = sem_open(S_DEAD, O_CREAT, 0644, 1);
	if (!options->forks || !options->write || !options->dead)
		return (0);
	while (++i < options->philo_num)
	{
		ft_bzero(&options->philos[i], sizeof(t_philo));
		options->philos[i].pos = i;
		options->philos[i].options = options;
	}
	return (1);
}
