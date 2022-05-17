/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:48:29 by mahmad-j          #+#    #+#             */
/*   Updated: 2022/05/17 11:29:39 by mahmad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_meal(void *args)
{
	t_info	*info;
	int		counter;
	int		i;

	info = (t_info *)args;
	counter = 0;
	while (counter <= info->philo_count)
	{
		i = 0;
		while (i < info->min_eat)
		{
			sem_wait(info->sem_meal);
			i++;
		}
		counter++;
	}
	sem_wait(info->sem_write);
	i = 0;
	while (i < info->philo_count)
		kill(info->philo[i++]->philo_pid, SIGKILL);
	return (NULL);
}

void	*check_thread(void *arg)
{
	t_philo	*p;

	p = ((t_philo *)arg);
	while (1)
	{
		sem_wait(p->sem_eat);
		if (get_time() - p->last_eat_time >= p->info->time_to_die)
		{
			print_state(p->info, p->philo_num, "died");
			exit(1);
		}
		sem_post(p->sem_eat);
		usleep(100);
	}
	return (NULL);
}

void	eat(t_philo *philo)
{
	sem_wait(philo->info->sem_fork);
	print_state(philo->info, philo->philo_num, "has taken a fork");
	sem_wait(philo->info->sem_fork);
	print_state(philo->info, philo->philo_num, "has taken a fork");
	print_state(philo->info, philo->philo_num, "is eating");
	sem_wait(philo->sem_eat);
	sem_post(philo->info->sem_meal);
	philo->last_eat_time = get_time();
	ft_usleep(philo->info->time_to_eat);
	sem_post(philo->sem_eat);
}

void	*routine(t_philo *p)
{
	while (1)
	{
		eat(p);
		sem_post(p->info->sem_fork);
		sem_post(p->info->sem_fork);
		print_state(p->info, p->philo_num, "is sleeping");
		ft_usleep(p->info->time_to_sleep);
		print_state(p->info, p->philo_num, "is thinking");
		usleep(100);
	}
	return (NULL);
}

void	start_philo(t_info *info)
{
	int	i;

	i = 0;
	if (info->min_eat)
		pthread_create(&info->check_meal, NULL, check_meal, (void *)info);
	while (i < info->philo_count)
	{
		info->philo[i]->philo_pid = fork();
		info->philo[i]->last_eat_time = get_time();
		if (info->philo[i]->philo_pid == 0)
		{
			pthread_create(&info->philo[i]->check_thread, NULL, check_thread,
				(void *)info->philo[i]);
			routine(info->philo[i]);
			exit(1);
		}
		i++;
		usleep(100);
	}
	close_processes(info);
}
