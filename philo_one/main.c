/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:38:57 by sdunckel          #+#    #+#             */
/*   Updated: 2020/02/14 18:47:44 by tomsize          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		start_multithread(t_options *options)
{
	int			i;
	pthread_t	thr;

	i = 0;
	options->start = get_time();
	while (i < options->num)
	{
		if (pthread_create(&thr, NULL, (void*)rules, &options->philos[i]))
			return (0);
		usleep(100);
		i++;
	}
	pthread_mutex_lock(&options->mutex);
	pthread_mutex_lock(&options->mutex);
	pthread_mutex_unlock(&options->mutex);
	return (1);
}

void 	create_philos(t_options *options)
{
	int		i;

	i = 0;
	while (i < options->num)
	{
		options->philos[i].pos = i;
		options->philos[i].time = 0;
		options->philos[i].eat_amount = 0;
		options->philos[i].options = options;
		pthread_mutex_init(&options->philos[i].mutex, NULL);
		pthread_mutex_init(&options->sticks[i], NULL);
		i++;
	}
}

int		parse_options(t_options *options, int argc, char **argv)
{
	options->num = ft_atoi(argv[1]);
	options->time_to_die = ft_atoi(argv[2]);
	options->time_to_eat = ft_atoi(argv[3]);
	options->time_to_sleep = ft_atoi(argv[4]);
	options->total = 0;
	if (argc == 6)
		options->max_eat = ft_atoi(argv[5]);
	else
		options->max_eat = 0;
	if (!(options->sticks = calloc(1, sizeof(pthread_mutex_t*) * options->num)))
		return (0);
	if (!(options->philos = calloc(1, sizeof(t_philo*) * options->num)))
		return (0);
	printf("num : %d / ttd : %d / tte : %d / tts : %d / max : %d\n", options->num, options->time_to_die, options->time_to_eat, options->time_to_sleep, options->max_eat);
	create_philos(options);
	pthread_mutex_init(&options->mutex, NULL);
	pthread_mutex_init(&options->write, NULL);
	return (1);
}

int		main(int argc, char **argv)
{
	t_options	options;

	memset(&options, 0, sizeof(options));
	if (argc < 5 || argc > 6)
		return (1);
	if (!(parse_options(&options, argc, argv)))
		return (1);
	if (!(start_multithread(&options)))
		return (1);
	destroy_mutex(&options);
	return (0);
}
