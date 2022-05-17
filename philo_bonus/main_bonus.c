/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 00:31:52 by mahmad-j          #+#    #+#             */
/*   Updated: 2022/05/17 11:22:27 by mahmad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		philo[i]->philo_num = i;
		philo[i]->info = info;
		sem_unlink("mealcounter");
		philo[i]->sem_eat = sem_open("mealcounter", O_CREAT, 0644, 1);
		if (philo[i]->sem_eat == SEM_FAILED)
			return (NULL);
		i++;
	}
	return (philo);
}

int	sems_init(t_info *info)
{
	sem_unlink("forking");
	info->sem_fork = sem_open("forking", O_CREAT, 0644, info->philo_count);
	if (info->sem_fork == SEM_FAILED)
		return (1);
	sem_unlink("writing");
	info->sem_write = sem_open("writing", O_CREAT, 0644, 1);
	if (info->sem_write == SEM_FAILED)
		return (1);
	sem_unlink("eating");
	info->sem_meal = sem_open("eating", O_CREAT, 0644, 1);
	if (info->sem_meal == SEM_FAILED)
		return (1);
	return (0);
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
	info->start_time = get_time();
	info->philo = init_philo(info);
	if (!info->philo || sems_init(info))
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

int	main(int ac, char **av)
{
	t_info	*info;

	if (!valid_args(ac, av))
		return (1);
	info = init_info(ac, av);
	if (!info)
		return (1);
	info->start_time = get_time();
	start_philo(info);
	return (0);
}
