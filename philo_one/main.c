/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:38:57 by sdunckel          #+#    #+#             */
/*   Updated: 2019/11/28 17:14:52 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		ft_atoi(const char *nptr)
{
	int		atoi;
	int		negative;

	atoi = 0;
	negative = 0;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\v' || *nptr == '\n'
		|| *nptr == '\r' || *nptr == '\f')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			negative = 1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		atoi = atoi * 10 + *nptr - 48;
		nptr++;
	}
	return (negative ? -atoi : atoi);
}

void	parse_philosophers(t_philo *philo, char **argv)
{
	philo->num = ft_atoi(argv[1]);
	philo->ttd = ft_atoi(argv[2]);
	philo->tte = ft_atoi(argv[3]);
	philo->tts = ft_atoi(argv[4]);
	philo->max = ft_atoi(argv[5]);
}

void	rules(t_philo *philo)
{
	printf("%d\n", philo->num);
	pthread_exit(NULL);
}

void	send_philosophers(t_philo *philo)
{
	int			i;
	pthread_t	thr[philo->num];

	i = 0;
	while (i < philo->num)
	{
		pthread_create(&thr[i], NULL, (void*)rules, philo);
		i++;
	}
	i = 0;
	while (i < philo->num)
	{
		pthread_join(thr[i], NULL);
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_philo		philo;

	if (argc != 6)
		return (0);
	parse_philosophers(&philo, argv);
	gettimeofday(&philo.tv, NULL);
	send_philosophers(&philo);

}
