/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:00:57 by ntalmon           #+#    #+#             */
/*   Updated: 2024/09/11 15:28:55 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	free_params(char **params, int count)
{
	while (count--)
		free(params[count]);
	free(params);
}

void	free_all(t_data *data)
{
	if (data->set.sp)
		free(data->set.sp);
	if (data->set.pl)
		free(data->set.pl);
	if (data->set.cy)
		free(data->set.cy);
	if (data->c.hit)
		free(data->c.hit);
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
