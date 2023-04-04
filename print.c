/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:32:13 by pbizien           #+#    #+#             */
/*   Updated: 2023/04/04 15:31:08 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long ft_get_time()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_time_eating(t_philo *tmp, long val)
{
	int	gap;

	gap = 25;
	while (ft_get_time() - tmp->last_meal < val)
	{
		usleep(gap);
	}
}

void	ft_time_sleeping(long val, long long time_start)
{
	int	gap;

	gap = 25;
	while (ft_get_time() - time_start < val)
	{
		usleep(gap);
	}
}

void	ft_print_is_eating(t_philo *tmp)
{
	struct timeval tv;
	
	if (tmp->data->dead)
		pthread_mutex_lock(tmp->mutex_print);
	pthread_mutex_lock(tmp->mutex_print);
	gettimeofday(&tv, NULL);
	tmp->last_meal = (tv.tv_usec / 1000) + (tv.tv_sec * 1000);
	printf("\e[32;1m%lld %d has taken a fork\e[0m\n", (tmp->last_meal - tmp->data->ts) ,tmp->num);
	printf("\e[34;49;1m%lld %d is eating \e[0m\n", (tmp->last_meal - tmp->data->ts), tmp->num);
	pthread_mutex_unlock(tmp->mutex_print);
	ft_time_eating(tmp, TIME_TO_EAT);
}

void	ft_print_is_sleeping(t_philo *tmp)
{
	struct timeval tv;
	
	if (tmp->data->dead)
		pthread_mutex_lock(tmp->mutex_print);
	pthread_mutex_lock(tmp->mutex_print);
	gettimeofday(&tv, NULL);
	printf("\e[36;49;1m%lld %d is sleeping \e[0m\n", ((tv.tv_usec / 1000) + (tv.tv_sec * 1000) - tmp->data->ts), tmp->num);
	pthread_mutex_unlock(tmp->mutex_print);
	ft_time_sleeping(TIME_TO_SLEEP, (tv.tv_usec / 1000) + (tv.tv_sec * 1000));
	
}

void	ft_print_is_thinking(t_philo *tmp)
{
	struct timeval tv;
	
	if (tmp->data->dead)
		pthread_mutex_lock(tmp->mutex_print);
	pthread_mutex_lock(tmp->mutex_print);
	gettimeofday(&tv, NULL);
	printf("\e[33;1m%lld %d is thinking\e[0m\n", ((tv.tv_usec / 1000) + (tv.tv_sec * 1000) - tmp->data->ts), tmp->num);
	pthread_mutex_unlock(tmp->mutex_print);
	
}