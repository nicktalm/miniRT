/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:24:36 by ntalmon           #+#    #+#             */
/*   Updated: 2024/10/08 16:34:19 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	main(int argc, char **argv)
{
	t_data	data;

	init_data(&data, argc, argv);
	init_mlx(&data);
	data.set.ambient.color = multi_vec_wnbr(data.set.ambient.color, data.set.ambient.ratio);
	printf("ambient x = %f y = %f z = %f\n", data.set.ambient.color.x, data.set.ambient.color.y, data.set.ambient.color.z);
	create_matrix(&data.set.obj[0].form.cy);
	// calc_quation(&data.set.obj[0].form.cy);
	// calc_quation(&data.set.obj[1].form.cy);
	if (data.name)
		create_img(&data);
	else
		creat_img_multi(&data);
	mlx_image_to_window(data.window, data.img, 0, 0);
	// mlx_loop_hook(data.window, hook, &data);
	mlx_loop(data.window);
	mlx_delete_image(data.window, data.img);
	mlx_terminate(data.window);
	free_all(&data);
	return (0);
}
