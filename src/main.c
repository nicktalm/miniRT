/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:24:36 by ntalmon           #+#    #+#             */
/*   Updated: 2024/11/06 17:17:16 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	main(int argc, char **argv)
{
	t_data	data;

	init_data(&data, argc, argv);
	init_mlx(&data);
	// free(data.set.obj);
	// data.set.obj = (t_objects *)malloc (sizeof(t_objects));
	// if (!data.set.obj)
	// 	error("malloc", &data);
	// data.set.obj_count = 1;
	// data.set.obj[0].type = CONE;
	// data.set.obj[0].form.cn.diameter = 2;
	// data.set.obj[0].form.cn.radius = 1;
	// data.set.obj[0].form.cn.height = 3.0;
	// data.set.obj[0].form.cn.coords.x = 0.0;
	// data.set.obj[0].form.cn.coords.y = 1.5;
	// data.set.obj[0].form.cn.coords.z = 0.0;
	// data.set.obj[0].form.cn.color.x = 0.8;
	// data.set.obj[0].form.cn.color.y = 0.2;
	// data.set.obj[0].form.cn.color.z = 0.2;
	// data.set.obj[0].form.cn.norm.x = 0.0;
	// data.set.obj[0].form.cn.norm.y = 1.0;
	// data.set.obj[0].form.cn.norm.z = 0.0;
	// data.set.obj[0].form.cn.angle = tanf(atanf(1.0 / 3.0)) * tanf(atanf(1.0 / 3.0));
	// data.set.obj[0].form.cn.tangle = atan(1.0 / 3.0);
	// create_m_cn(&data.set.obj[0].form.cn);
	create_img(&data);
	mlx_image_to_window(data.window, data.img, 0, 0);
	// mlx_loop_hook(data.window, hook, &data);
	mlx_loop(data.window);
	mlx_delete_image(data.window, data.img);
	mlx_terminate(data.window);
	free_all(&data);
	return (0);
}
