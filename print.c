/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:32:13 by pbizien           #+#    #+#             */
/*   Updated: 2023/04/05 15:44:06 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long ft_get_time()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long long ft_get_time_micro()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

void	ft_time_eating(t_philo *tmp, long val)
{
	int	gap;

	gap = 500;
	fprintf(stderr, "%lld AVANT MANGER PHILO %d val vaut %ld\n", ft_get_time() - tmp->start_time, tmp->num, val);
	while (ft_get_time() - tmp->last_meal < val)
	{
		usleep(gap);
	}
	fprintf(stderr, "%lld APRES MANGER PHILO %d\n", ft_get_time() - tmp->start_time, tmp->num);
}

void	ft_time_sleeping(long val, long long time_start)
{
	int	gap;

	gap = 500;
	while (ft_get_time() - time_start < val)
	{
		usleep(gap);
	}
}

void	ft_time_thinking(long val, long long time_start)
{
	int	gap;

	gap = 500;
	while (ft_get_time() - time_start < val)
	{
		usleep(gap);
	}
}

int	ft_print_is_eating(t_philo *tmp)
{
	struct timeval tv;
	
	if (tmp->data->dead)
		return (1);
	pthread_mutex_lock(tmp->mutex_print);
	gettimeofday(&tv, NULL);
	tmp->last_meal = (tv.tv_usec / 1000) + (tv.tv_sec * 1000);
	printf("\e[32;1m%lld %d has taken a fork\e[0m\n", (tmp->last_meal - tmp->data->ts) ,tmp->num);
	printf("\e[34;49;1m%lld %d is eating\e[0m\n", (tmp->last_meal - tmp->data->ts), tmp->num);
	tmp->count_eat++;
	pthread_mutex_unlock(tmp->mutex_print);
	
	ft_time_eating(tmp, tmp->data->time_to_eat);
	printf("\e[32;1m%lld %d devrait aller dormir\e[0m\n", (ft_get_time() - tmp->data->ts), tmp->num);
	return (0);
}

int	ft_print_is_sleeping(t_philo *tmp)
{
	struct timeval tv;
	
	if (tmp->data->dead)
		return (1);
	pthread_mutex_lock(tmp->mutex_print);
	gettimeofday(&tv, NULL);
	printf("\e[36;49;1m%lld %d is sleeping\e[0m\n", ((tv.tv_usec / 1000) + (tv.tv_sec * 1000) - tmp->data->ts), tmp->num);
	pthread_mutex_unlock(tmp->mutex_print);
	ft_time_sleeping(tmp->data->time_to_sleep, (tv.tv_usec / 1000) + (tv.tv_sec * 1000));
	return (0);
}

int	ft_print_is_thinking_odd(t_philo *tmp)
{
	struct timeval tv;
	
	if (tmp->data->dead)
		return (1);
	pthread_mutex_lock(tmp->mutex_print);
	gettimeofday(&tv, NULL);
	printf("\e[33;1m%lld %d is thinking\e[0m\n", ((tv.tv_usec / 1000) + (tv.tv_sec * 1000) - tmp->data->ts), tmp->num);
	pthread_mutex_unlock(tmp->mutex_print);
	ft_time_thinking(tmp->data->time_to_eat - tmp->data->time_to_sleep + 1, ft_get_time());
	return (0);
}

int	ft_print_is_thinking_even(t_philo *tmp)
{
	struct timeval tv;
	
	if (tmp->data->dead)
		return (1);
	pthread_mutex_lock(tmp->mutex_print);
	gettimeofday(&tv, NULL);
	printf("\e[33;1m%lld %d is thinking\e[0m\n", ((tv.tv_usec / 1000) + (tv.tv_sec * 1000) - tmp->data->ts), tmp->num);
	pthread_mutex_unlock(tmp->mutex_print);
	return (0);
}