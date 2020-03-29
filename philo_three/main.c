/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:43:42 by sdunckel          #+#    #+#             */
/*   Updated: 2020/03/16 17:15:17 by sdunckel         ###   ########.fr       */
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
		if ((philo->pid = create_fork(philo)) < 0)
			return (0);
		i++;
	}
	return (1);
}

void	destroy_all(t_options *options)
{
	sem_unlink(S_FORK);
	sem_unlink(S_WRITE);
	free(options->philos);
}

void	monitor(t_options *options, int philo_num)
{
	int		i;
	int		count;
	int		status;
	int		finished;

	count = 0;
	finished = 0;
	while (!finished)
	{
		i = 0;
		while (i < philo_num)
		{
			status = 0;
			if (waitpid(options->philos[i].pid, &status, 0) < 0)
			{
				if (!WEXITSTATUS(status))
					count++;
			}
			if (count == options->philo_num)
				finished = 1;
			i++;
		}
	}
}

int		main(int argc, char **argv)
{
	t_options	options;

	sem_unlink(S_FORK);
	sem_unlink(S_WRITE);
	ft_bzero(&options, sizeof(t_options));
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
