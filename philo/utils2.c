/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:59:49 by mahmad-j          #+#    #+#             */
/*   Updated: 2022/05/17 05:01:07 by mahmad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int time_ms)
{
	int	start_time;

	start_time = 0;
	start_time = get_time();
	while ((get_time() - start_time) < time_ms)
		usleep(time_ms / 10);
}

void	print_state(t_info *info, int philo_num, char *message)
{
	pthread_mutex_lock(&info->mutex_write);
	if (info->finish != 0)
		printf("%d %d %s\n", get_time() - info->start_time, philo_num + 1,
			message);
	pthread_mutex_unlock(&info->mutex_write);
}

void	join_thread(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_count)
	{
		pthread_join(info->philo[i]->philo_thread, NULL);
		pthread_join(info->philo[i]->check_thread, NULL);
		i++;
	}
	clear_mem(info);
}
