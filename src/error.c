/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:00:57 by ntalmon           #+#    #+#             */
/*   Updated: 2024/11/25 12:18:54 by ntalmon          ###   ########.fr       */
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

void	delete_bump_texture(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->set.obj_count)
	{
		if (data->set.obj[i].type == SPHERE)
			check_bump_texture(data->set.obj[i].form.sp.bump_map,
				data->set.obj[i].form.sp.texture);
		else if (data->set.obj[i].type == PLANE)
			check_bump_texture(data->set.obj[i].form.pl.bump_map,
				data->set.obj[i].form.pl.texture);
		else if (data->set.obj[i].type == CYLINDER)
			check_bump_texture(data->set.obj[i].form.cy.bump_map,
				data->set.obj[i].form.cy.texture);
		else if (data->set.obj[i].type == CONE)
			check_bump_texture(data->set.obj[i].form.cn.bump_map,
				data->set.obj[i].form.cn.texture);
		i++;
	}
}

void	free_all(t_data *data)
{
	if (data->set.obj)
	{
		delete_bump_texture(data);
		free(data->set.obj);
	}
	if (data->set.light)
		free(data->set.light);
	if (data->garbage.line)
		free_double_p(data->garbage.line);
	if (data->garbage.params)
		free_double_p(data->garbage.params);
}

void	error_2(char *message, char *param, t_data *data)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(param, 2);
	ft_putstr_fd("\n", 2);
	free_all(data);
	mlx_delete_image(data->window, data->img);
	mlx_terminate(data->window);
	exit(0);
}

void	error(char *message, t_data *data)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	free_all(data);
	mlx_delete_image(data->window, data->img);
	mlx_terminate(data->window);
	exit(0);
}
