/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:10:50 by lbohm             #+#    #+#             */
/*   Updated: 2024/09/12 18:18:48 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	hook(void *param)
{
	t_data	*data;
	double	time;

	data = param;
	time = mlx_get_time();
	mlx_delete_image(data->window, data->img);
	mlx_resize_hook(data->window, resize, data);
	data->img = mlx_new_image(data->window, data->width, data->height);
	create_img(data);
	mlx_image_to_window(data->window, data->img, 0, 0);
	printf("fps = %f\n", 1 / (mlx_get_time() - time));
}

void	resize(int width, int height, void *param)
{
	t_data	*data;

	data = param;
	data->height = height;
	data->width = width;
	data->aspect_ratio = (float)width / (float)height;
	free(data->c.hit);
	data->c.hit = NULL;
	data->c.hit = (t_hitpoint *)malloc
		(data->width * data->height * sizeof(t_hitpoint));
	if (!data->c.hit)
		error("malloc failed", data);
	data->moved = true;
}

// void	key(mlx_key_data_t keydata, void *param)
// {
// 	t_data	*data;

// 	data = param;
// 	if (keydata.key == MLX_KEY_W && (keydata.action == 1 || keydata.action == 2))
// 		data->set.cam.coords.z -= 0.5;
// 	if (keydata.key == MLX_KEY_S && (keydata.action == 1 || keydata.action == 2))
// 		data->set.cam.coords.z += 0.5;
// 	if (keydata.key == MLX_KEY_A && (keydata.action == 1 || keydata.action == 2))
// 		data->set.cam.coords.x += 0.5;
// 	if (keydata.key == MLX_KEY_D && (keydata.action == 1 || keydata.action == 2))
// 		data->set.cam.coords.x -= 0.5;
// 	if (keydata.key == MLX_KEY_Q && (keydata.action == 1 || keydata.action == 2))
// 		data->set.cam.coords.y -= 0.5;
// 	if (keydata.key == MLX_KEY_E && (keydata.action == 1 || keydata.action == 2))
// 		data->set.cam.coords.y += 0.5;
// 	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == 1)
// 	{
// 		mlx_delete_image(data->window, data->img);
// 		mlx_terminate(data->window);
// 		free_all(data);
// 		exit(0);
// 	}
// 	data->moved = true;
// }
