/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:24:36 by ntalmon           #+#    #+#             */
/*   Updated: 2024/11/22 21:12:50 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	main(int argc, char **argv)
{
	t_data	data;

	init_data(&data, argc, argv);
	// printf("bump %p\n", data.set.obj[0].form.cn.bump_map);
	// printf("text %p\n", data.set.obj[0].form.cn.texture);
	init_mlx(&data);
	create_img(&data);
	if (mlx_image_to_window(data.window, data.img, 0, 0) == -1)
		error("image to window", &data);
	mlx_get_monitor_size(0, &data.win_w_max, &data.win_h_max);
	mlx_set_window_limit(data.window, -1, -1, data.win_w_max, data.win_h_max);
	mlx_loop_hook(data.window, hook, &data);
	mlx_loop(data.window);
	mlx_delete_image(data.window, data.img);
	mlx_terminate(data.window);
	free_all(&data);
	return (0);
}

void	get_resolution(t_data *data)
{
	static int	up = 0;
	static int	down = 0;

	if (!data->cache_use)
	{
		if (data->window->delta_time > 0.15 && down == 0)
		{
			data->res++;
			data->moved = true;
			up = 1;
		}
		else if (data->window->delta_time < 0.07 && up == 0
			&& !data->cache_use && (data->height * data->width) > 100000)
		{
			if (data->res > 1)
				data->res--;
			data->moved = true;
			down = 1;
		}
		else
		{
			up = 0;
			down = 0;
		}
	}
}

int	create_color(float x, float y, float z, float w)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = 255.0 * x;
	g = 255.0 * y;
	b = 255.0 * z;
	a = 255.0 * w;
	check_interval(&r);
	check_interval(&g);
	check_interval(&b);
	check_interval(&a);
	return (r << 24 | g << 16 | b << 8 | a);
}

void	check_interval(int *nbr)
{
	if (*nbr > 255)
		*nbr = 255;
	else if (*nbr < 0)
		*nbr = 0;
}
