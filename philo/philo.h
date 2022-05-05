/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahmad-j <mahmad-j@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 00:32:22 by mahmad-j          #+#    #+#             */
/*   Updated: 2022/05/02 13:24:52 by mahmad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdint.h>
# include <sys/time.h>

typedef struct	s_philo
{
	pthread_t		philo_thread;
	pthread_t		check_thread;
	pthread_mutex_t	mutex_eat;
	int				philo_num;
	int				last_eat_time;
	int				eat_count;
	int				left_fork;
	int				right_fork;
	int				is_eating;
	struct s_info	*info;
}				t_philo;

typedef struct s_info
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_eat;
	int				start_time;
	int				finish;
	pthread_mutex_t	mutex_write;
	pthread_mutex_t	*mutex_fork;
	t_philo			**philo;	
}				t_info;

int				valid_args(int ac, char **av);
t_info			*init_info(int ac, char **av);
pthread_mutex_t	*init_fork(t_info *info);
t_philo			**init_philo(t_info *info);
void			start_philo(t_info *info);
void			*routine(void *arg);
void			eat(t_philo *philo);
void			*check(void *arg);
void			check_min_eat(t_philo *p);

int				is_number(char *str);
int				ft_isdigit(char c);
int				ft_atoi(char *str);
int				get_time(void);
void			clear_mem(t_info *info);
void			ft_usleep(int	time_ms);
void			print_state(t_info *info, int philo_num, char *message);

#endif