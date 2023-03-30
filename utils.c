/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbizien <pbizien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:41:47 by pbizien           #+#    #+#             */
/*   Updated: 2023/03/30 11:30:32 by pbizien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;
	
	i = 0;
	while (str && str[i])
	{
		i++;
	}
	return (i);
}

int	ft_putstr_fd(char *str, int fd)
{
	if (!str)
		return (write(fd, "(null)", 6), 1);
	else
		return (write(fd, str, ft_strlen(str)), 0);
}