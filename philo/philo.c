/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 10:48:29 by mahmad-j          #+#    #+#             */
/*   Updated: 2022/05/13 21:22:18 by mahmad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_min_eat(t_philo *p)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&p->mutex_eat);
	while (i < p->info->philo_count)
	{
		if (p->info->philo[i]->eat_count >= p->info->min_eat)
		{
			if (i == p->info->philo_count - 1)
			{
				pthread_mutex_lock(&p->info->mutex_write);
				p->info->finish = 0;
				pthread_mutex_unlock(&p->info->mutex_write);
			}
			i++;
		}
		else
			break ;
	}
	pthread_mutex_unlock(&p->mutex_eat);
}

void	*check(void *arg)
{
	t_philo	*p;

	p = ((t_philo *)arg);
	while (p->info->finish)
	{
		if (!p->is_eating && get_time() - p->last_eat_time
			>= p->info->time_to_die)
		{
			pthread_mutex_lock(&p->mutex_eat);
			print_state(p->info, p->philo_num, "died");
			p->info->finish = 0;
			pthread_mutex_unlock(&p->mutex_eat);
		}
		if (p->info->min_eat && p->eat_count >= p->info->min_eat)
			check_min_eat(p);
		usleep(100);
	}
	return (NULL);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->mutex_fork[philo->right_fork]);
	print_state(philo->info, philo->philo_num, "has taken a fork");
	pthread_mutex_lock(&philo->mutex_eat);
	philo->last_eat_time = get_time();
	philo->is_eating = 1;
	print_state(philo->info, philo->philo_num, "is eating");
	ft_usleep(philo->info->time_to_eat);
	philo->is_eating = 0;
	philo->eat_count++;
	pthread_mutex_unlock(&philo->mutex_eat);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = ((t_philo *)arg);
	while (p->info->finish)
	{
		pthread_mutex_lock(&p->info->mutex_fork[p->left_fork]);
		print_state(p->info, p->philo_num, "has taken a fork");
		if (p->left_fork == p->right_fork)
			break ;
		eat(p);
		pthread_mutex_unlock(&p->info->mutex_fork[p->left_fork]);
		pthread_mutex_unlock(&p->info->mutex_fork[p->right_fork]);
		print_state(p->info, p->philo_num, "is sleeping");
		ft_usleep(p->info->time_to_sleep);
		print_state(p->info, p->philo_num, "is thinking");
	}
	return (NULL);
}

void	start_philo(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_count)
	{
		info->philo[i]->last_eat_time = get_time();
		pthread_create(&info->philo[i]->philo_thread, NULL, routine,
			(void *)info->philo[i]);
		i++;
		usleep(100);
	}
	i = 0;
	while (i < info->philo_count)
	{
		pthread_create(&info->philo[i]->check_thread, NULL, check,
			(void *)info->philo[i]);
		i++;
		usleep(100);
	}
}
