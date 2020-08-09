/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 16:12:30 by sdunckel          #+#    #+#             */
/*   Updated: 2020/08/09 15:52:45 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(int n)
{
	time_t start;

	start = get_time();
	while ((get_time() - start) < n)
		usleep(200);
}

time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

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

void	*ft_calloc(size_t size)
{
	void	*mem;

	if (!(mem = malloc(size)))
		return (NULL);
	memset(mem, 0, size);
	return (mem);
}
