/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:51:59 by pbizien           #+#    #+#             */
/*   Updated: 2023/04/04 19:31:19 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	ft_think_n_eat_even(t_philo *tmp)
{
	// struct timeval tv;
	
	if (tmp->num % 2 == 1)
	{
		pthread_mutex_lock(tmp->mutex_right);
		// pthread_mutex_lock(tmp->mutex_print);
		// gettimeofday(&tv, NULL);
		// printf("\e[32;1m%lld %d has taken a right fork %p\e[0m\n", (ft_get_time() - tmp->data->ts), tmp->num, tmp->mutex_right);
		// pthread_mutex_unlock(tmp->mutex_print);
		pthread_mutex_lock(tmp->mutex_left);
		ft_print_is_eating(tmp);
		pthread_mutex_unlock(tmp->mutex_left);
		pthread_mutex_unlock(tmp->mutex_right);
	}
	if (tmp->num % 2 == 0)
	{
		pthread_mutex_lock(tmp->mutex_left);
		// pthread_mutex_lock(tmp->mutex_print);
		// gettimeofday(&tv, NULL);
		// // printf("\e[32;1m%lld %d has taken a left fork %p\e[0m\n", (ft_get_time() - tmp->data->ts), tmp->num, tmp->mutex_left);
		// pthread_mutex_unlock(tmp->mutex_print);
		pthread_mutex_lock(tmp->mutex_right);
		ft_print_is_eating(tmp);
		pthread_mutex_unlock(tmp->mutex_right);
		pthread_mutex_unlock(tmp->mutex_left);
	}
	ft_print_is_sleeping(tmp);
	ft_print_is_thinking_even(tmp);
}

void	ft_think_n_eat_odd(t_philo *tmp)
{
	if (tmp->num % 2 == 1)
	{
		pthread_mutex_lock(tmp->mutex_right);
		pthread_mutex_lock(tmp->mutex_left);
		ft_print_is_eating(tmp);
		pthread_mutex_unlock(tmp->mutex_left);
		pthread_mutex_unlock(tmp->mutex_right);
	}
	if (tmp->num % 2 == 0)
	{
		pthread_mutex_lock(tmp->mutex_left);
		pthread_mutex_lock(tmp->mutex_right);
		ft_print_is_eating(tmp);
		pthread_mutex_unlock(tmp->mutex_right);
		pthread_mutex_unlock(tmp->mutex_left);
	}
	ft_print_is_sleeping(tmp);
	ft_print_is_thinking_odd(tmp);
}

void *routine(void *arg)
{
	t_philo *tmp;

	tmp = (t_philo *)arg;
	while (ft_get_time() < tmp->start_time)
	{
		usleep(50);
	}
	if (tmp->num % 2 == 1)
		usleep(100);
	if (NB_PHILO % 2 == 0)
		while (1)
			ft_think_n_eat_even(tmp);
	else
		while (1)
			ft_think_n_eat_odd(tmp);
			
		
	return (NULL);
}

void	*ft_check_die(void *arg)
{
	int	i;
	long long tmp_time;
	t_philo *tmp;

	tmp = (t_philo *)arg;
	while (1)
	{
		if (tmp->data->bool_start != 0)
			break;
	}
	usleep(100);
	while (1)
	{
		i = 0;
		tmp = (t_philo *)arg;
		while (i < NB_PHILO)
		{
			tmp_time = ft_get_time();
			if (tmp_time - tmp->last_meal >= TIME_TO_DIE)
			{
				tmp->data->dead = 1;
				printf("\e[31;1m%lld %lld PHILO %d est dead\e\n", tmp_time - tmp->data->ts,tmp_time - tmp->last_meal, tmp->num);
				fprintf(stderr, "LE MUTEX DE DROITE EST %d\n", pthread_mutex_trylock(tmp->mutex_right));
				fprintf(stderr, "LE MUTEX DE GAUCHE EST %d\n", pthread_mutex_trylock(tmp->mutex_left));
				return (NULL);
			}
			 i++;
			 tmp = tmp->next;
		}
		
	}
}
int	ft_create_thread(t_data *data)
{
	int	i;
	t_philo *tmp;

	i = 0;
	data->pt = malloc(sizeof(pthread_t) * (NB_PHILO + 1));
	if (!data->pt)
		return (1);
	data->pt[NB_PHILO] = 0;
	tmp = data->philos;
	
	while (i < NB_PHILO)
	{
		if (pthread_create(&data->pt[i], NULL, &routine, tmp) != 0)
			ft_putstr_fd("Gros pb de creation brrr brrr\n", 2);
		tmp = tmp->next;
		i++;
	}
	tmp = data->philos;
	*(data->bool_start) = 1;
	ft_check_die(tmp);
	i = 0;
	return (0);
}

int	*ft_create_forks(int nb)
{
	int	*output;
	int	j;
	
	j = 0;
	output = malloc(sizeof(int) * (nb + 1));
	if (!output)
		return (NULL);
	while (j <= nb)
	{
		output[j] = 0;
		j++;
	}
	return (output);
}

pthread_mutex_t	*ft_create_mutex(int nb)
{
	pthread_mutex_t	*output;
	int	j;
	
	j = 0;
	output = malloc(sizeof(pthread_mutex_t) * (nb));
	if (!output)
		return (NULL);
	while (j < nb)
	{
		pthread_mutex_init(&output[j], NULL);
		j++;
	}
	return (output);
}

pthread_mutex_t	*ft_create_mutex_print()
{
	pthread_mutex_t	*output;
	
	output = malloc(sizeof(pthread_mutex_t));
	if (!output)
		return (NULL);
	pthread_mutex_init(output, NULL);
	return (output);
}

t_philo	*ft_init(int nb, t_data *data, int *alive)
{
	t_philo *output;
	t_philo *tmp;
	int	i;

	*alive = 1;
	data->dead = 0;
	data->bool_start = malloc(sizeof(int));
	if (!data->bool_start)
		return (NULL);
	*data->bool_start = 0;
	data->ts = ft_get_time();
	data->i = 0;
	data->forks = ft_create_forks(nb);
	if (!data->forks)
		return (NULL);
	data->mutex = ft_create_mutex(nb);
	if (!data->mutex)
		return (free(data->forks), NULL);
	data->mutex_print = ft_create_mutex_print();
	if (!data->mutex_print)	
		return (free(data->forks), free(data->mutex), NULL);
	tmp = malloc(sizeof(t_philo));
	if (!tmp)	
		return (free(data->forks), free(data->mutex), free(data->mutex_print), NULL);
	data->ts = ft_get_time() + 100;
	output = tmp;
	tmp->num = 1;
	tmp->alive = alive;
	tmp->right_fork = &data->forks[0];
	tmp->mutex_right = &data->mutex[0];
	tmp->mutex_print = data->mutex_print;
	tmp->data = data;
	tmp->start_time = data->ts; // gerer nb de filo
	tmp->last_meal = data->ts;
	tmp->left_fork = &data->forks[nb - 1];
	tmp->mutex_left = &data->mutex[nb - 1];
	i = 1;
	while (i < nb)
	{
		tmp->next = malloc(sizeof(t_philo));
		if (!tmp->next)
			return (free(data->forks), free(data->mutex), ft_free_list(output), NULL);
		tmp = tmp->next;
		tmp->num = i + 1;
		tmp->alive = alive;
		tmp->mutex_print = data->mutex_print;
		tmp->right_fork = &data->forks[i];
		tmp->data = data;
		tmp->start_time = data->ts;
		tmp->mutex_right = &data->mutex[i];
		tmp->left_fork = &data->forks[i - 1];
		tmp->last_meal = data->ts;
		tmp->mutex_left = &data->mutex[i - 1];
		i++;
	}
	tmp->next = NULL;
	return (output);
}

int	main(int ac, char**av)
{
	(void)ac;
	(void)av;
	t_data data;
	int		alive;
	
	data.philos = ft_init(NB_PHILO, &data, &alive);
	if (ft_create_thread(&data) != 0)
		return (1);
	// free(data.forks);
	// free(data.pt);
	// ft_free_list(data.philos);
	// free(data.mutex);
	
}

