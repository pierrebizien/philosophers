/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:53:57 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/30 15:11:07 by pbizien          ###   ########.fr       */
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
# define TIME_TO_EAT 20000
# define TIME_TO_SLEEP 20000
# define MIN_EAT 1

typedef struct	s_philo
{
	int				num;
	int				*right_fork;
	int				*left_fork;
	struct s_philo	*next;
	int				*alive;
	
}				t_philo;


typedef struct	s_data
{
	int				*forks;
	pthread_t		*pt;
	pthread_mutex_t	*mutex;
	t_philo			*philos;
	
}				t_data;

int	ft_putstr_fd(char *str, int fd);
void	ft_free_list(t_philo *begin);

#endif