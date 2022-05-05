/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 00:31:52 by mahmad-j          #+#    #+#             */
/*   Updated: 2022/05/05 18:29:44 by mahmad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**init_philo(t_info *info)
{
	t_philo	**philo;
	int		i;

	philo = (t_philo **)malloc(sizeof(t_philo *) * info->philo_count);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < info->philo_count)
	{
		philo[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!philo[i])
			return (NULL);
		if (pthread_mutex_init(&philo[i]->mutex_eat, NULL))
			return (NULL);
		philo[i]->philo_num = i;
		philo[i]->info = info;
		philo[i]->is_eating = 0;
		philo[i]->eat_count = 0;
		philo[i]->left_fork = i;
		philo[i]->right_fork = (i + 1) % info->philo_count;
		i++;
	}
	return (philo);
}

pthread_mutex_t	*init_fork(t_info *info)
{
	pthread_mutex_t	*mutex_fork;
	int				i;
	
	i = 0;
	mutex_fork = malloc(sizeof(pthread_mutex_t) * info->philo_count);
	if (!mutex_fork)
		return (NULL);
	while (i < info->philo_count)
	{
		pthread_mutex_init(&mutex_fork[i], NULL);
		i++;
	}
	return (mutex_fork);
}

t_info	*init_info(int ac, char **av)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->philo_count = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	info->min_eat = 0;
	if (ac == 6)
		info->min_eat = ft_atoi(av[5]);
	pthread_mutex_init(&info->mutex_write, NULL);
	info->start_time = get_time();
	info->mutex_fork = init_fork(info);
	info->philo = init_philo(info);
	if (!info->philo || !info->mutex_fork)
	{
		clear_mem(info);
		return (NULL);
	}
	return (info);
}

int	valid_args(int ac, char **av)
{
	int	i;
	
	i = 1;
	if (ac < 5 || ac > 6)
	{
		printf("Error: Invalid argument number\n");
		return (0);
	}
	while (i < ac)
	{
		if (av[i][0] == '-' || is_number(av[i]) != 1 || !ft_atoi(av[i]))
		{
			printf("Error: Invalid argument(s)\n");
			return (0);
		}
		i++;
	}
	return (1);
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
	pthread_mutex_unlock(&info->mutex_write);
	clear_mem(info);
	printf("--Clear Mem\n");
}

int	main(int ac, char **av)
{
	t_info	*info;

	if (!valid_args(ac, av))
		return (1);
	info = init_info(ac, av);
	if (!info)
		return (1);
	info->finish = 1;
	info->start_time = get_time();
	start_philo(info);
	while (info->finish)
		continue;
	join_thread(info);
	return (0);
}