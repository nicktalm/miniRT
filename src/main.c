/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:24:36 by ntalmon           #+#    #+#             */
/*   Updated: 2024/09/03 10:17:49 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	main(void)
{
	t_data	data;

	init_data(&data);
	init_mlx(&data);
	create_img(&data);
	mlx_image_to_window(data.window, data.img, 0, 0);
	mlx_loop_hook(data.window, hook, &data);
	mlx_loop(data.window);
	mlx_delete_image(data.window, data.img);
	mlx_terminate(data.window);
	free(data.set.sp);
	free(data.set.pl);
	free(data.set.cy);
	free(data.caches);
	return (0);
}
