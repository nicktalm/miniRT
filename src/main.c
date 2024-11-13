/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:24:36 by ntalmon           #+#    #+#             */
/*   Updated: 2024/11/13 17:58:05 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	main(int argc, char **argv)
{
	t_data	data;

	init_data(&data, argc, argv);
	init_mlx(&data);
	data.set.obj[0].form.pl.length = 10.0;
	data.set.obj[0].form.pl.width = 10.0;
	data.set.obj[0].form.pl.texture = NULL;
	data.set.obj[1].form.pl.length = 10.0;
	data.set.obj[1].form.pl.width = 10.0;
	data.set.obj[1].form.pl.texture = NULL;
	data.set.obj[2].form.pl.length = 10.0;
	data.set.obj[2].form.pl.width = 10.0;
	data.set.obj[2].form.pl.texture = NULL;
	data.set.obj[3].form.pl.length = 1.0;
	data.set.obj[3].form.pl.width = 1.0;
	data.set.obj[3].form.pl.texture = mlx_load_xpm42("textures/xpm42/wood_floor.xpm42");
	if (!data.set.obj[3].form.pl.texture)
		error("load xpm file", &data);
	data.set.obj[4].form.pl.length = 1.0;
	data.set.obj[4].form.pl.width = 1.0;
	data.set.obj[4].form.pl.texture = mlx_load_xpm42("textures/xpm42/wood_floor.xpm42");
	if (!data.set.obj[4].form.pl.texture)
		error("load xpm file", &data);
	data.set.obj[5].form.pl.length = 1.0;
	data.set.obj[5].form.pl.width = 1.0;
	data.set.obj[5].form.pl.texture = mlx_load_xpm42("textures/xpm42/wood_floor.xpm42");
	if (!data.set.obj[5].form.pl.texture)
		error("load xpm file", &data);
	data.set.obj[6].form.pl.length = 1.0;
	data.set.obj[6].form.pl.width = 1.0;
	data.set.obj[6].form.pl.texture = mlx_load_xpm42("textures/xpm42/wood_floor.xpm42");
	if (!data.set.obj[6].form.pl.texture)
		error("load xpm file", &data);
	data.set.obj[7].form.pl.length = 1.0;
	data.set.obj[7].form.pl.width = 1.0;
	data.set.obj[7].form.pl.texture = mlx_load_xpm42("textures/xpm42/wood_floor.xpm42");
	if (!data.set.obj[7].form.pl.texture)
		error("load xpm file", &data);
	data.set.obj[8].form.pl.length = 1.0;
	data.set.obj[8].form.pl.width = 1.0;
	data.set.obj[8].form.pl.texture = mlx_load_xpm42("textures/xpm42/wood_floor.xpm42");
	if (!data.set.obj[8].form.pl.texture)
		error("load xpm file", &data);
	data.set.obj[9].form.sp.texture = mlx_load_xpm42("textures/xpm42/basketball_bump.xpm42");
	if (!data.set.obj[9].form.sp.texture)
		error("load xpm file", &data);
	// data.set.obj[1].form.sp.texture = mlx_load_xpm42("textures/xpm42/stars.xpm42");
	// if (!data.set.obj[1].form.sp.texture)
	// 	error("load xpm file", &data);
	// data.set.obj[0].form.pl.texture = mlx_load_xpm42("textures/xpm42/earth.xpm42");
	// if (!data.set.obj[0].form.pl.texture)
	// 	error("load xpm file", &data);
	// data.set.obj[1].form.pl.texture = mlx_load_xpm42("textures/xpm42/earth.xpm42");
	// if (!data.set.obj[1].form.pl.texture)
	// 	error("load xpm file", &data);
	// data.set.obj[2].form.pl.texture = mlx_load_xpm42("textures/xpm42/earth.xpm42");
	// if (!data.set.obj[2].form.pl.texture)
	// 	error("load xpm file", &data);
	// data.set.obj[3].form.pl.texture = mlx_load_xpm42("textures/xpm42/wood_floor.xpm42");
	// if (!data.set.obj[3].form.pl.texture)
	// 	error("load xpm file", &data);
	// data.set.obj[4].form.pl.texture = mlx_load_xpm42("textures/xpm42/wood_floor.xpm42");
	// if (!data.set.obj[4].form.pl.texture)
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
