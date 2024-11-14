/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:24:36 by ntalmon           #+#    #+#             */
/*   Updated: 2024/11/12 12:58:12 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	main(int argc, char **argv)
{
	t_data	data;

	init_data(&data, argc, argv);
	init_mlx(&data);
	// data.set.obj[0].form.sp.bump_map = mlx_load_xpm42("textures/xpm42/earth.xpm42");
	// if (!data.set.obj[0].form.sp.bump_map)
	// 	error("load xpm file", &data);
	// data.set.obj[1].form.sp.bump_map = mlx_load_xpm42("textures/xpm42/moon.xpm42");
	// if (!data.set.obj[1].form.sp.bump_map)
	// 	error("load xpm file", &data);
	// data.set.obj[2].form.pl.bump_map = mlx_load_xpm42("textures/xpm42/stars.xpm42");
	// if (!data.set.obj[2].form.pl.bump_map)
	// 	error("load xpm file", &data);
	create_img(&data);
	mlx_image_to_window(data.window, data.img, 0, 0);
	// mlx_loop_hook(data.window, hook, &data);
	mlx_loop(data.window);
	mlx_delete_image(data.window, data.img);
	mlx_terminate(data.window);
	free_all(&data);
	return (0);
}
