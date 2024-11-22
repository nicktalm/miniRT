/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:24:36 by ntalmon           #+#    #+#             */
/*   Updated: 2024/11/22 15:03:59 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	main(int argc, char **argv)
{
	t_data	data;

	init_data(&data, argc, argv);
	// init_mlx(&data);
	// mlx_get_monitor_size(0, &data.win_w_max, &data.win_h_max);
	// mlx_set_window_limit(data.window, -1, -1, data.win_w_max, data.win_h_max);
	create_img(&data);
	// mlx_loop_hook(data.window, hook, &data);
	// mlx_loop(data.window);
	// mlx_delete_image(data.window, data.img);
	// mlx_terminate(data.window);
	free_all(&data);
	return (0);
}

void	get_resolution(t_data *data)
{
	if (!data->cache_use)
	{
		if (data->window->delta_time > 0.1)
		{
			data->res++;
			data->moved = true;
		}
		else if (data->window->delta_time < 0.05
			&& !data->cache_use && (data->height * data->width) > 10000)
		{
			if (data->res > 1)
				data->res--;
			data->moved = true;
		}
	}
}
