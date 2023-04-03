/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierrebizien <pierrebizien@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:53:57 by pbizien           #+#    #+#             */
/*   Updated: 2023/04/03 11:05:06 by pierrebizie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>

# define NB_PHILO 2
# define TIME_TO_DIE 20000
# define TIME_TO_EAT 200
# define TIME_TO_SLEEP 200
# define MIN_EAT 1

typedef struct	s_philo
{
	int				num;
	int				*right_fork;
	pthread_mutex_t	*mutex_right;
	pthread_mutex_t	*mutex_left;
	pthread_mutex_t	*mutex_print;
	int				*left_fork;
	struct s_philo	*next;
	int				*alive;
	struct s_data	*data;
	long int		last_meal;
	
}				t_philo;


typedef struct	s_data
{
	int				*forks;
	pthread_t		*pt;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*mutex_print;
	t_philo			*philos;
	int				*bool_start;
	long		ts;
	int				i;
	
}				t_data;

int	ft_putstr_fd(char *str, int fd);
void	ft_free_list(t_philo *begin);
void	ft_print_is_eating(t_philo *tmp);
void	ft_print_is_sleeping(t_philo *tmp);
void	ft_print_is_thinking(t_philo *tmp);


#endif