/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 00:48:45 by mahmad-j          #+#    #+#             */
/*   Updated: 2022/05/15 16:50:50 by mahmad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	unsigned long	num;
	int				sign;
	int				i;

	num = 0;
	sign = 1;
	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		num = num * 10 + (str[i++] - '0');
	if (num > INT32_MAX || sign == -1)
		return (0);
	return (num * sign);
}

int	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	clear_mem(t_info *info)
{
	int				i;
	t_philo			**philo;

	i = 0;
	philo = info->philo;
	while (i < info->philo_count && philo)
	{
		free(philo[i]);
		philo[i] = NULL;
		i++;
	}
	free(philo);
	philo = NULL;
	i = 0;
	while (i < info->philo_count && info->mutex_fork)
		pthread_mutex_destroy(&info->mutex_fork[i++]);
	free(info->mutex_fork);
	info->mutex_fork = NULL;
	free(info);
	info = NULL;
}
