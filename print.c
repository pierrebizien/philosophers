/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:32:13 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/30 18:53:02 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_is_eating(t_philo *tmp)
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	
	pthread_mutex_lock(tmp->mutex_print);
	printf("\e[32;1m%ld %d has taken a fork\e[0m\n", ((tv.tv_usec / 1000) + (tv.tv_sec * 1000) - tmp->data->ts) ,tmp->num);
	printf("\e[34;49;1m%ld %d is eating \e[0m\n", ((tv.tv_usec / 1000) + (tv.tv_sec * 1000) - tmp->data->ts), tmp->num);
	pthread_mutex_unlock(tmp->mutex_print);
}

void	ft_print_is_sleeping(t_philo *tmp)
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	pthread_mutex_lock(tmp->mutex_print);
	printf("\e[36;49;1m%ld %d is sleeping \e[0m\n", ((tv.tv_usec / 1000) + (tv.tv_sec * 1000) - tmp->data->ts), tmp->num);
	pthread_mutex_unlock(tmp->mutex_print);
	
}

void	ft_print_is_thinking(t_philo *tmp)
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	pthread_mutex_lock(tmp->mutex_print);
	// fprintf(stderr, "timestamp vaut %d usec %ld\n", tmp->data->ts, (tv.tv_sec * 1000 )+( tv.tv_usec / 1000));
	printf("\e\e[31;49;1m%ld %d is thinking\e[0m\n", ((tv.tv_usec / 1000) + (tv.tv_sec * 1000) - tmp->data->ts), tmp->num);
	pthread_mutex_unlock(tmp->mutex_print);
	
}