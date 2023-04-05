/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:48:11 by pbizien           #+#    #+#             */
/*   Updated: 2023/04/05 15:30:11 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void    ft_format()
{
    printf("syntax: number_of_philosophers time_to_die time_to_eat \
time_to_sleep [Number_of_times_each_philosopher_must_eat]\n");
}

int ft_parsing(t_data *data, int ac, char **av)
{
    if (ac <= 4 || ac > 6)
        return (ft_format(), 1);
    if (ac == 5)
		data->min_eat = INT_MAX;
	else
	{
		data->min_eat = ft_atoi(av[5]);
		if (data->min_eat < 0)
       		return (ft_format(), 1);
	}
	data->nb_philo = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
	if (data->nb_philo < 0)
       	return (fprintf(stderr, "ICI nb philo %d\n", data->nb_philo), ft_format(), 1);
	if (data->time_to_die < 0)
       	return (fprintf(stderr, "ICI\n"), ft_format(), 1);
	if (data->time_to_eat < 0)
       	return (fprintf(stderr, "ICI\n"), ft_format(), 1);
	if (data->time_to_sleep < 0)
       	return (fprintf(stderr, "ICI\n"), ft_format(), 1);
    return (0);
}
