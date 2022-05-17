/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 05:06:38 by mahmad-j          #+#    #+#             */
/*   Updated: 2022/05/17 11:37:42 by mahmad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdint.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_philo
{
	pid_t			philo_pid;
	pthread_t		check_thread;
	sem_t			*sem_eat;
	int				philo_num;
	int				last_eat_time;
	struct s_info	*info;
}				t_philo;

typedef struct s_info
{
	pthread_t		check_meal;
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_eat;
	int				start_time;
	sem_t			*sem_write;
	sem_t			*sem_fork;
	sem_t			*sem_meal;
	t_philo			**philo;
}				t_info;

int				valid_args(int ac, char **av);
t_info			*init_info(int ac, char **av);
int				sems_init(t_info *info);
t_philo			**init_philo(t_info *info);
void			start_philo(t_info *info);
void			*routine(t_philo *p);
void			eat(t_philo *philo);
void			*check_thread(void *arg);
void			*check_meal(void *args);

int				is_number(char *str);
int				ft_isdigit(char c);
int				ft_atoi(char *str);
int				get_time(void);
void			clear_mem(t_info *info);
void			ft_usleep(int time_ms);
void			print_state(t_info *info, int philo_num, char *message);
void			close_processes(t_info *info);

#endif