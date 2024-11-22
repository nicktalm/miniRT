/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:10:50 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/22 19:40:19 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

bool	check_vec(t_vec3 vec);

void	key(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	data->moved = true;
	if (!data->render)
	{
		if (wasd(keydata, data))
			return ;
		else if (cr(keydata, data, 0))
			return ;
	}
	if (cr(keydata, data, 1))
		return ;
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

bool	wasd(mlx_key_data_t key, t_data *data)
{
	t_vec3	t;
	t_vec3	bit;
	t_vec3	*coord;

	coord = &data->set.cam.coords;
	t = get_tangent(data->set.cam.direction);
	bit = norm_vec(cross_vec(t, data->set.cam.direction));
	if (key.key == MLX_KEY_W && (key.action == 1 || key.action == 2))
		*coord = add_vec(*coord, multi_vec_wnbr(data->set.cam.direction, 0.5));
	else if (key.key == MLX_KEY_S && (key.action == 1 || key.action == 2))
		*coord = sub_vec(*coord, multi_vec_wnbr(data->set.cam.direction, 0.5));
	else if (key.key == MLX_KEY_A && (key.action == 1 || key.action == 2))
		*coord = sub_vec(*coord, multi_vec_wnbr(t, 0.5));
	else if (key.key == MLX_KEY_D && (key.action == 1 || key.action == 2))
		*coord = add_vec(*coord, multi_vec_wnbr(t, 0.5));
	else if (key.key == MLX_KEY_Q && (key.action == 1 || key.action == 2))
		*coord = add_vec(*coord, multi_vec_wnbr(bit, 0.5));
	else if (key.key == MLX_KEY_E && (key.action == 1 || key.action == 2))
		*coord = sub_vec(*coord, multi_vec_wnbr(bit, 0.5));
	else if (lrud(key, data, t, bit))
		return (true);
	else
		return (false);
	return (true);
}

bool	lrud(mlx_key_data_t key, t_data *data, t_vec3 t, t_vec3 bit)
{
	t_vec3	*dir;

	dir = &data->set.cam.direction;
	if (key.key == MLX_KEY_LEFT && (key.action == 1 || key.action == 2))
		*dir = norm_vec(sub_vec(*dir, multi_vec_wnbr(t, 0.1)));
	else if (key.key == MLX_KEY_RIGHT && (key.action == 1 || key.action == 2))
		*dir = norm_vec(add_vec(*dir, multi_vec_wnbr(t, 0.1)));
	else if (key.key == MLX_KEY_UP && (key.action == 1 || key.action == 2))
		*dir = norm_vec(add_vec(*dir, multi_vec_wnbr(bit, 0.1)));
	else if (key.key == MLX_KEY_DOWN && (key.action == 1 || key.action == 2))
		*dir = norm_vec(sub_vec(*dir, multi_vec_wnbr(bit, 0.1)));
	else
		return (false);
	return (true);
}

bool	cr(mlx_key_data_t key, t_data *data, int i)
{
	if (key.key == MLX_KEY_C && key.action == 1 && i == 0)
	{
		if (!data->checker)
			data->checker = true;
		else
			data->checker = false;
		return (true);
	}
	else if (key.key == MLX_KEY_R && key.action == 1)
	{
		if (!data->render)
		{
			data->render = true;
			mlx_set_window_limit(data->window, data->width,
				data->height, data->width, data->height);
		}
		else
		{
			data->render = false;
			mlx_set_window_limit(data->window, -1, -1,
				data->win_w_max, data->win_h_max);
		}
		return (true);
	}
	return (false);
}

bool	check_vec(t_vec3 vec)
{
	if (fabsf(vec.x) > 0.9 || fabsf(vec.y) > 0.9 || fabsf(vec.z) > 0.9)
		return (false);
	return (true);
}
