/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:10:50 by lbohm             #+#    #+#             */
/*   Updated: 2024/09/03 17:36:41 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	hook(void *param)
{
	t_data	*data;
	double	time;

	data = param;
	time = mlx_get_time();
	mlx_key_hook(data->window, key, data);
	mlx_cursor_hook(data->window, cursor, data);
	mlx_resize_hook(data->window, resize, data);
	mlx_delete_image(data->window, data->img);
	data->img = mlx_new_image(data->window, data->width, data->hight);
	if (data->moved)
	{
		free(data->caches_t);
		data->caches_t = (t_vec *)malloc (sizeof(t_vec) * data->width * data->hight);
		if (!data->caches_t)
			error("malloc failed", data);
	}
	create_img(data);
	mlx_image_to_window(data->window, data->img, 0, 0);
	printf("time = %f\n", (mlx_get_time() - time) * 1000);
}

void	resize(int width, int hight, void *param)
{
	t_data	*data;

	data = param;
	data->hight = hight;
	data->width = width;
	data->aspect_ratio = (float)width / (float)hight;
	data->moved = true;
}

void	key(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_W && (keydata.action == 1 || keydata.action == 2))
		data->set.cam.coords.z -= 0.5;
	if (keydata.key == MLX_KEY_S && (keydata.action == 1 || keydata.action == 2))
		data->set.cam.coords.z += 0.5;
	if (keydata.key == MLX_KEY_A && (keydata.action == 1 || keydata.action == 2))
		data->set.cam.coords.x += 0.5;
	if (keydata.key == MLX_KEY_D && (keydata.action == 1 || keydata.action == 2))
		data->set.cam.coords.x -= 0.5;
	if (keydata.key == MLX_KEY_Q && (keydata.action == 1 || keydata.action == 2))
		data->set.cam.coords.y -= 0.5;
	if (keydata.key == MLX_KEY_E && (keydata.action == 1 || keydata.action == 2))
		data->set.cam.coords.y += 0.5;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == 1)
	{
		mlx_delete_image(data->window, data->img);
		mlx_terminate(data->window);
		free_all(data);
		exit(0);
	}
	data->moved = true;
}

void	cursor(double xpos, double ypos, void *param)
{
	t_data	*data;

	data = param;
	static int	mouseX = 0;
	static int	mouseY = 0;

	if (!mouseX && !mouseY)
	{
		mouseX = xpos / data->dpi;
		mouseY = ypos / data->dpi;
	}
	else
	{
		if (mlx_is_mouse_down(data->window, MLX_MOUSE_BUTTON_LEFT))
		{
			data->set.light.coords.x -= ((float)xpos / data->dpi) - (float)mouseX;
			data->set.light.coords.z -= ((float)ypos / data->dpi) - (float)mouseY;
			data->set.light.normalized = norm_vec(data->set.light.coords);
			data->set.light.normalized.x *= -1;
			data->set.light.normalized.y *= -1;
			data->set.light.normalized.z *= -1;
			data->moved = true;
		}
		else
		{
			mouseX = 0;
			mouseY = 0;
		}
	}
}
