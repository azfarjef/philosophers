/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:59:49 by mahmad-j          #+#    #+#             */
/*   Updated: 2022/05/17 11:37:36 by mahmad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	sem_wait(info->sem_write);
	printf("%d %d %s\n", get_time() - info->start_time, philo_num + 1, message);
	if (message[0] != 'd')
		sem_post(info->sem_write);
}

void	close_processes(t_info *info)
{
	int	i;
	int	status;

	i = 0;
	waitpid(-1, &status, 0);
	if (WIFEXITED(status) || WIFSIGNALED(status))
	{
		while (i < info->philo_count)
			kill(info->philo[i++]->philo_pid, SIGKILL);
	}
}
