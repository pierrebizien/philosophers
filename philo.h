/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:53:57 by pbizien           #+#    #+#             */
/*   Updated: 2023/04/05 15:23:15 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>

# define NB_PHILO 2
# define TIME_TO_DIE 402
# define TIME_TO_EAT 200
// # define TIME_TO_THINK 195
# define TIME_TO_SLEEP 200
# define MAX_EAT 2147483647

typedef struct	s_philo
{
	int				num;
	int				*right_fork;
	pthread_mutex_t	*mutex_right;
	pthread_mutex_t	*mutex_left;
	pthread_mutex_t	*mutex_print;
	pthread_mutex_t	*mutex_last_meal;
	int				*left_fork;
	long long		start_time;
	int				count_eat;
	struct s_philo	*next;
	int				*alive;
	struct s_data	*data;
	
	long long		last_meal;
	
}				t_philo;


typedef struct	s_data
{
	int				*forks;
	int				dead;
	pthread_t		*pt;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*mutex_print;
	pthread_mutex_t	*mutex_dead;
	t_philo			*philos;
	int				*bool_start;
	long long		ts;
	int				i;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_eat;
	int				nb_philo;
	
}				t_data;

int	ft_putstr_fd(char *str, int fd);
void	ft_free_list(t_philo *begin);
int	ft_print_is_eating(t_philo *tmp);
int	ft_print_is_sleeping(t_philo *tmp);
int	ft_print_is_thinking_odd(t_philo *tmp);
int	ft_print_is_thinking_even(t_philo *tmp);
long long ft_get_time();
long long ft_get_time_micro();
void	ft_usleep(long long micro, long long start);
int ft_parsing(t_data *data, int ac, char **av);
int	ft_strlen(char *str);
int	ft_atoi(char *str);




#endif
