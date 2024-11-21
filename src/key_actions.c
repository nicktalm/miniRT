/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:10:50 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/20 15:55:37 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

bool	wasd(mlx_key_data_t keydata, t_data *data);
bool	lrud(mlx_key_data_t keydata, t_data *data, t_vec3 t, t_vec3 bit);

void	hook(void *param)
{
	t_data	*data;

	data = param;
	// printf("delta time = %f\n", data->window->delta_time);
	get_resolution(data);
	mlx_resize_hook(data->window, resize, data);
	mlx_key_hook(data->window, key, data);
	create_img(data);
}

void	resize(int width, int height, void *param)
{
	t_data	*data;

	data = param;
	data->height = height;
	data->width = width;
	data->aspect_ratio = (float)width / (float)height;
	if (data->cache)
		free(data->cache);
	data->cache = (t_vec3 *)malloc
		(data->width * data->height * sizeof(t_vec3));
	if (!data->cache)
		error("malloc", data);
	if (!mlx_resize_image(data->img, width, height))
		error("resized failed", data);
	data->moved = true;
}

void	key(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	data->moved = true;
	if (!data->render)
	{
		if (wasd(keydata, data))
			return ;
		else if (keydata.key == MLX_KEY_C && keydata.action == 1)
		{
			if (!data->checker)
				data->checker = true;
			else
				data->checker = false;
			return ;
		}
	}
	if (keydata.key == MLX_KEY_R && keydata.action == 1)
	{
		if (!data->render)
		{
			data->render = true;
			mlx_set_window_limit(data->window, data->width, data->height, data->width, data->height);
		}
		else
		{
			data->render = false;
			mlx_set_window_limit(data->window, -1, -1, data->win_w_max, data->win_h_max);
		}
	}
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == 1)
	{
		mlx_delete_image(data->window, data->img);
		mlx_terminate(data->window);
		free_all(data);
		exit(0);
	}
	else
		data->moved = false;
}

bool	wasd(mlx_key_data_t keydata, t_data *data)
{
	t_vec3	tangent;
	t_vec3	bitangent;

	bitangent = get_tangent(data->set.cam.direction);
	tangent = cross_vec(data->set.cam.direction, bitangent);
	if (keydata.key == MLX_KEY_W && (keydata.action == 1 || keydata.action == 2))
		data->set.cam.coords = add_vec(data->set.cam.coords, multi_vec_wnbr(data->set.cam.direction, 0.5));
	else if (keydata.key == MLX_KEY_S && (keydata.action == 1 || keydata.action == 2))
		data->set.cam.coords = sub_vec(data->set.cam.coords, multi_vec_wnbr(data->set.cam.direction, 0.5));
	else if (keydata.key == MLX_KEY_A && (keydata.action == 1 || keydata.action == 2))
		data->set.cam.coords = add_vec(data->set.cam.coords, multi_vec_wnbr(bitangent, 0.5));
	else if (keydata.key == MLX_KEY_D && (keydata.action == 1 || keydata.action == 2))
		data->set.cam.coords = sub_vec(data->set.cam.coords, multi_vec_wnbr(bitangent, 0.5));
	else if (keydata.key == MLX_KEY_Q && (keydata.action == 1 || keydata.action == 2))
		data->set.cam.coords = add_vec(data->set.cam.coords, multi_vec_wnbr(tangent, 0.5));
	else if (keydata.key == MLX_KEY_E && (keydata.action == 1 || keydata.action == 2))
		data->set.cam.coords = sub_vec(data->set.cam.coords, multi_vec_wnbr(tangent, 0.5));
	else if (lrud(keydata, data, tangent, bitangent))
		return (true);
	else
		return (false);
	return (true);
}

bool	lrud(mlx_key_data_t keydata, t_data *data, t_vec3 t, t_vec3 bit)
{
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == 1 || keydata.action == 2))
		data->set.cam.direction = add_vec(data->set.cam.direction, multi_vec_wnbr(bit, 0.1));
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == 1 || keydata.action == 2))
		data->set.cam.direction = sub_vec(data->set.cam.direction, multi_vec_wnbr(bit, 0.1));
	else if (keydata.key == MLX_KEY_UP && (keydata.action == 1 || keydata.action == 2))
		data->set.cam.direction = add_vec(data->set.cam.direction, multi_vec_wnbr(t, 0.1));
	else if (keydata.key == MLX_KEY_DOWN && (keydata.action == 1 || keydata.action == 2))
		data->set.cam.direction = sub_vec(data->set.cam.direction, multi_vec_wnbr(t, 0.1));
	else
		return (false);
	return (true);
}
