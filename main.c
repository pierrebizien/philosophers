/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:51:59 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/30 18:55:15 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_think_n_eat(t_philo *tmp)
{
	ft_print_is_thinking(tmp);
	if (tmp->num % 2 == 1)
	{
		pthread_mutex_lock(tmp->mutex_right);
		pthread_mutex_lock(tmp->mutex_left);
		ft_print_is_eating(tmp);
		usleep(200);
		pthread_mutex_unlock(tmp->mutex_left);
		pthread_mutex_unlock(tmp->mutex_right);
	}
	if (tmp->num % 2 == 0)
	{
		pthread_mutex_lock(tmp->mutex_left);
		pthread_mutex_lock(tmp->mutex_right);
		ft_print_is_eating(tmp);
		usleep(200);
		pthread_mutex_unlock(tmp->mutex_right);
		pthread_mutex_unlock(tmp->mutex_left);
	}
	ft_print_is_sleeping(tmp);
	usleep(200);
		
	
}

void *routine(void *arg)
{
	t_philo *tmp;
	struct timeval tv;

	tmp = (t_philo *)arg;
	gettimeofday(&tv, NULL);
	tmp->data->ts = (tv.tv_sec * 1000 )+( tv.tv_usec / 1000);
	while (tmp->alive)
	{
		ft_think_n_eat(tmp);
	}
	
	return (NULL);
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
		usleep(100);
		tmp = tmp->next;
		i++;
	}
	i = 0;
	while (i < NB_PHILO)
	{
		if (pthread_join(data->pt[i], NULL) != 0)
			ft_putstr_fd("Gros pb de creation brrr brrr\n", 2);
		i++;
	}
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
	int	j;
	
	j = 0;
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
	output = tmp;
	tmp->num = 1;
	tmp->alive = alive;
	tmp->right_fork = &data->forks[0];
	tmp->mutex_right = &data->mutex[0];
	tmp->mutex_print = data->mutex_print;
	tmp->data = data;
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
		tmp->mutex_right = &data->mutex[i];
		tmp->left_fork = &data->forks[i - 1];
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
	t_philo *tmp;
	int		alive;
	
	data.philos = ft_init(NB_PHILO, &data, &alive);
	if (ft_create_thread(&data) != 0)
		return (1);
	tmp = data.philos;
	// while (tmp)
	// {
	// 	fprintf(stderr, "Adresse gauche du %d vaut %p\n", tmp->num, tmp->mutex_left);
	// 	fprintf(stderr, "Adresse droite du %d vaut %p\n", tmp->num, tmp->mutex_right);
	// 	tmp = tmp->next;
	// }
	free(data.forks);
	free(data.pt);
	ft_free_list(data.philos);
	free(data.mutex);
	
}

