/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:00:57 by ntalmon           #+#    #+#             */
/*   Updated: 2024/10/28 21:40:39 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	free_double_p(char **double_p)
{
	int	count;

	count = 0;
	while (double_p[count])
	{
		free(double_p[count]);
		count++;
	}
	free(double_p);
}

void	free_all(t_data *data)
{
	if (data->set.obj)
		free(data->set.obj);
	if (data->cache)
		free(data->cache);
	// if (!data->name)
	// 	pthread_mutex_destroy(&data->random);
}

void	error_2(char *message, char *param, t_data *data)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(param, 2);
	ft_putstr_fd("\n", 2);
	free_all(data);
	exit(0);
}

void	error(char *message, t_data *data)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	free_all(data);
	exit(0);
}
