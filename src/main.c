/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:24:36 by ntalmon           #+#    #+#             */
/*   Updated: 2024/11/20 10:38:10 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	get_resolution(t_data *data);

int	main(int argc, char **argv)
{
	t_data	data;

	init_data(&data, argc, argv);
	init_mlx(&data);
	mlx_image_to_window(data.window, data.img, 0, 0);
	create_img(&data);
	mlx_loop_hook(data.window, hook, &data);
	mlx_loop(data.window);
	mlx_delete_image(data.window, data.img);
	mlx_terminate(data.window);
	free_all(&data);
	return (0);
}

void	get_resolution(t_data *data)
{
	printf("delta time = %f\n", data->window->delta_time);
	while (data->window->delta_time > 1.0 || data->window->delta_time == 0.0)
	{
		printf("delta time = %f\n", data->window->delta_time);
		data->res++;
		create_img(data);
	}
}
