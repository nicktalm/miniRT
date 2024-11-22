/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:28:38 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/22 12:29:06 by lbohm            ###   ########.fr       */
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
	if (!mlx_resize_image(data->img, width, height))
		error("resized failed", data);
	if (!data->render)
		data->moved = true;
}
