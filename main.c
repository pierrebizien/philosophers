/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:51:59 by pbizien           #+#    #+#             */
/*   Updated: 2023/05/30 18:32:45 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int	ft_think_n_eat_even(t_philo *tmp)
{
	struct timeval tv;
	if (tmp->num % 2 == 1)
	{
		pthread_mutex_lock(tmp->mutex_right);
		pthread_mutex_lock(tmp->mutex_print);
		pthread_mutex_lock(tmp->data->mutex_dead);
		if (tmp->data->dead)
			return (pthread_mutex_unlock(tmp->data->mutex_dead),pthread_mutex_unlock(tmp->mutex_right),  pthread_mutex_unlock(tmp->mutex_print), 1);
		pthread_mutex_unlock(tmp->data->mutex_dead);
		gettimeofday(&tv, NULL);
		printf("\e[32;1m%lld %d has taken a fork\e[0m\n", (ft_get_time() - tmp->data->ts), tmp->num);
		pthread_mutex_unlock(tmp->mutex_print);
		pthread_mutex_lock(tmp->mutex_left);
		pthread_mutex_lock(tmp->data->mutex_dead);
		if (tmp->data->dead)
			return (pthread_mutex_unlock(tmp->data->mutex_dead), pthread_mutex_unlock(tmp->mutex_right), pthread_mutex_unlock(tmp->mutex_left), pthread_mutex_unlock(tmp->mutex_print), 1);
		pthread_mutex_unlock(tmp->data->mutex_dead);
		if (ft_print_is_eating(tmp))
			return (1);
		pthread_mutex_unlock(tmp->mutex_left);
		pthread_mutex_unlock(tmp->mutex_right);
	}
	if (tmp->num % 2 == 0)
	{
		pthread_mutex_lock(tmp->mutex_left);
		pthread_mutex_lock(tmp->mutex_print);
		pthread_mutex_lock(tmp->data->mutex_dead);
		if (tmp->data->dead)
			return (pthread_mutex_unlock(tmp->data->mutex_dead), pthread_mutex_unlock(tmp->mutex_right), pthread_mutex_unlock(tmp->mutex_left), pthread_mutex_unlock(tmp->mutex_print), 1);
		pthread_mutex_unlock(tmp->data->mutex_dead);
		gettimeofday(&tv, NULL);
		printf("\e[32;1m%lld %d has taken a fork\e[0m\n", (ft_get_time() - tmp->data->ts), tmp->num);
		pthread_mutex_unlock(tmp->mutex_print);
		pthread_mutex_lock(tmp->mutex_right);
		pthread_mutex_lock(tmp->data->mutex_dead);
		if (tmp->data->dead)
			return (pthread_mutex_unlock(tmp->data->mutex_dead), pthread_mutex_unlock(tmp->mutex_right), pthread_mutex_unlock(tmp->mutex_left), pthread_mutex_unlock(tmp->mutex_print), 1);
		pthread_mutex_unlock(tmp->data->mutex_dead);
		if (ft_print_is_eating(tmp))
			return (1);
		pthread_mutex_unlock(tmp->mutex_right);
		pthread_mutex_unlock(tmp->mutex_left);
	}
	ft_print_is_sleeping(tmp);
	ft_print_is_thinking_even(tmp);
	return (0);
}

int	ft_think_n_eat_odd(t_philo *tmp)
{
	struct timeval tv;
	if (tmp->num % 2 == 1)
	{
		pthread_mutex_lock(tmp->mutex_right);
		pthread_mutex_lock(tmp->mutex_left);
		pthread_mutex_lock(tmp->mutex_print);
		pthread_mutex_lock(tmp->data->mutex_dead);
		if (tmp->data->dead)
			return (pthread_mutex_unlock(tmp->data->mutex_dead), pthread_mutex_unlock(tmp->mutex_left), pthread_mutex_unlock(tmp->mutex_right),  pthread_mutex_unlock(tmp->mutex_print), 1);
		pthread_mutex_unlock(tmp->data->mutex_dead);
		gettimeofday(&tv, NULL);
		printf("\e[32;1m%lld %d has taken a fork\e[0m\n", (ft_get_time() - tmp->data->ts), tmp->num);
		pthread_mutex_unlock(tmp->mutex_print);
		if (ft_print_is_eating(tmp))
			return (1);
		pthread_mutex_unlock(tmp->mutex_left);
		pthread_mutex_unlock(tmp->mutex_right);
	}
	if (tmp->num % 2 == 0)
	{
		pthread_mutex_lock(tmp->mutex_left);
		pthread_mutex_lock(tmp->mutex_right);
		pthread_mutex_lock(tmp->mutex_print);
		pthread_mutex_lock(tmp->data->mutex_dead);
		if (tmp->data->dead)
			return (pthread_mutex_unlock(tmp->data->mutex_dead), pthread_mutex_unlock(tmp->mutex_left), pthread_mutex_unlock(tmp->mutex_right), pthread_mutex_unlock(tmp->mutex_print), 1);
		pthread_mutex_unlock(tmp->data->mutex_dead);
		gettimeofday(&tv, NULL);
		printf("\e[32;1m%lld %d has taken a fork\e[0m\n", (ft_get_time() - tmp->data->ts), tmp->num);
		pthread_mutex_unlock(tmp->mutex_print);
		if (ft_print_is_eating(tmp))
			return (1);
		pthread_mutex_unlock(tmp->mutex_right);
		pthread_mutex_unlock(tmp->mutex_left);
	}
	ft_print_is_sleeping(tmp);
	ft_print_is_thinking_odd(tmp);
	return (0);
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
	if (tmp->data->nb_philo % 2 == 0)
	{
		while (1)
		{
			if(ft_think_n_eat_even(tmp))
				return (NULL);
		}
	}
	else
	{
		while (1)
			if (ft_think_n_eat_odd(tmp))
				return (NULL);
	}
		
	return (NULL);
}

void	*ft_check_die(void *arg)
{
	int	i;
	long long tmp_time;
	int			nb_full;
	int			nb_philo;
	t_philo *tmp;
	

	tmp = (t_philo *)arg;
	nb_full = 0;
	nb_philo = tmp->data->nb_philo;
	while (ft_get_time() < tmp->start_time)
	{
		usleep(50);
	}
	usleep(200);
	
	while (1)
	{
		i = 0;
		tmp = (t_philo *)arg;
		while (i < nb_philo)
		{
			tmp_time = ft_get_time();
			if (tmp->count_eat == tmp->data->min_eat)
				nb_full++;
			if (nb_full == nb_philo)
			{ 
				// fprintf(stderr, "hello nb philo ==");
				pthread_mutex_lock(tmp->data->mutex_dead);
				tmp->data->dead = 1;
				pthread_mutex_unlock(tmp->data->mutex_dead);
				return (NULL);
			}
			if (tmp_time - tmp->last_meal >= tmp->data->time_to_die)
			{
				pthread_mutex_lock(tmp->data->mutex_dead);
				tmp->data->dead = 1;
				pthread_mutex_unlock(tmp->data->mutex_dead);
				printf("%lld %d died \n", tmp_time - tmp->data->ts,tmp->num);
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
	data->pt = malloc(sizeof(pthread_t) * (data->nb_philo + 1));
	if (!data->pt)
		return (1);
	data->pt[data->nb_philo] = 0;
	tmp = data->philos;
	
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->pt[i], NULL, &routine, tmp) != 0)
			ft_putstr_fd("Gros pb de creation brrr brrr\n", 2);
		tmp = tmp->next;
		i++;
	}
	tmp = data->philos;
	ft_check_die(tmp);
	i = 0;
	// while (i < data->nb_philo)
	// {
	// 	if (pthread_join(data->pt[i], NULL) != 0)
	// 		ft_putstr_fd("Gros pb de creation brrr brrr\n", 2);
	// 	i++;
	// }
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

pthread_mutex_t	*ft_create_mutex_dead()
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
	data->mutex_dead = ft_create_mutex_dead();
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
	tmp->count_eat = 0;
	tmp->counted = 0;
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
		tmp->count_eat = 0;
		tmp->counted = 0;
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
	
	if (ft_parsing(&data, ac, av))
		return (1);
	data.philos = ft_init(data.nb_philo, &data, &alive);
	if (ft_create_thread(&data) != 0)
		return (1);
	
}

