/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:51:59 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/30 15:16:25 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	

void *routine(void * arg)
{
	t_philo *tmp;

	tmp = (t_philo *)arg;
	
	printf("\e[35;40;1mhello world je suis le philo %d \e[0m\n", tmp->num);
	while (tmp->alive)
	{
		ft_think_n_eat()
	}
	
	tmp->num++;
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

t_philo	*ft_init(int nb, t_data *data, int *alive)
{
	t_philo *output;
	t_philo *tmp;
	int	i;

	*alive = 1;
	data->forks = ft_create_forks(nb);
	if (!data->forks)
		return (NULL);
	data->mutex = ft_create_mutex(nb);
	if (!data->mutex)
		return (free(data->forks), NULL);
	tmp = malloc(sizeof(t_philo));
	if (!tmp)	
		return (free(data->forks), free(data->mutex), NULL);
	output = tmp;
	tmp->num = 1;
	tmp->alive = alive;
	i = 1;
	while (i < nb)
	{
		tmp->next = malloc(sizeof(t_philo));
		if (!tmp->next)
			return (free(data->forks), free(data->mutex), ft_free_list(output), NULL);
		tmp = tmp->next;
		tmp->num = i + 1;
		tmp->alive = alive;
		tmp->right_fork = &data->forks[nb - 1];
		if (i == 0)
			tmp->left_fork = &data->forks[nb - 1];
		else
			tmp->left_fork = &data->forks[i - 1];
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
	while (tmp)
	{
		fprintf(stderr, "num vaut %d\n", tmp->num);
		tmp = tmp->next;
	}
	free(data.forks);
	free(data.pt);
	ft_free_list(data.philos);
	free(data.mutex);
	
}
