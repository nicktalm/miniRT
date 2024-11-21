/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:28:38 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/21 14:29:31 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	hook(void *param)
{
	t_data	*data;

	data = param;
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
	if (!data->render)
		data->moved = true;
}
