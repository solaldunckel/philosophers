/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:38:57 by sdunckel          #+#    #+#             */
/*   Updated: 2019/12/21 16:14:28 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void 	create_philos(t_options *options)
{
	int		i;

	i = 0;
	while (i < options->num)
	{
		options->philos[i].pos = i;
		options->philos[i].time = 0;
		options->philos[i].eat_amount = 0;
		options->philos[i].left = i;
		options->philos[i].right = i + 1;
		options->philos[i].options = options;
		pthread_mutex_init(&options->sticks[i], NULL);
		i++;
		if (i == options->num)
			options->philos[i - 1].right -= options->num;
	}
}

int		parse_options(t_options *options, int argc, char **argv)
{
	options->num = ft_atoi(argv[1]);
	options->time_to_die = ft_atoi(argv[2]);
	options->time_to_eat = ft_atoi(argv[3]);
	options->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		options->max_eat = ft_atoi(argv[5]);
	else
		options->max_eat = 0;
	if (!(options->philos = malloc(sizeof(t_philo) * options->num)))
		return (0);
	if (!(options->sticks = malloc(sizeof(pthread_mutex_t) * options->num)))
		return (0);
	pthread_mutex_init(&options->mutex, NULL);
	pthread_mutex_init(&options->write, NULL);
	pthread_mutex_lock(&options->mutex);
	create_philos(options);
	return (1);
}

void	death(t_philo *philo)
{
	while (1)
	{
		if (philo->time + philo->options->time_to_die < get_time())
		{
			state_msg(philo, "is dead");
			pthread_mutex_unlock(&philo->options->mutex);
			return ;
		}
	}
}

void	eat_count(t_philo *philo)
{
	while (philo->eat_amount < philo->options->max_eat)
		;
	state_msg(philo, "has finished.");
	return ;
}

void 	rules(t_philo *philo)
{
	pthread_t	thr;

	philo->time = get_time();
	if (pthread_create(&thr, NULL, (void*)death, philo))
		return ;
	pthread_mutex_init(&philo->sleep, NULL);
	while (1)
	{
		take_sticks(philo);
		start_eating(philo);
		drop_sticks(philo);
		start_sleep(philo);
		state_msg(philo, "is thinking");
	}
}

int		start_multithread(t_options *options)
{
	int			i;
	pthread_t	thr[options->num];

	i = 0;
	options->start = get_time();
	while (i < options->num)
	{
		if (pthread_create(&thr[i], NULL, (void*)rules, &options->philos[i]))
			return (0);
		i++;
	}
	return (1);
}

void	destroy_mutex(t_options *options)
{
	int		i;

	i = 0;
	pthread_mutex_destroy(&options->write);
	pthread_mutex_destroy(&options->mutex);
	while (i < options->num)
	{
		pthread_mutex_destroy(&options->sticks[i]);
		pthread_mutex_destroy(&options->philos[i].sleep);
		i++;
	}
	free(options->sticks);
	free(options->philos);
}

int		main(int argc, char **argv)
{
	t_options	options;

	if (argc < 5 || argc > 6)
		return (1);
	if (!(parse_options(&options, argc, argv)))
		return (1);
	if (!(start_multithread(&options)))
		return (1);
	pthread_mutex_lock(&options.mutex);
	pthread_mutex_unlock(&options.mutex);
	destroy_mutex(&options);
	return (0);
}
