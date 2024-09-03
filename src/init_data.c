/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:17:29 by lbohm             #+#    #+#             */
/*   Updated: 2024/09/03 10:57:20 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	init_data(t_data *data, int argc, char **argv)
{
	if (argc == 2)
	{
		data->set.sp = NULL;
		data->set.pl = NULL;
		data->set.cy = NULL;
		data->caches = NULL;
		data->width = 900;
		data->hight = 900;
		data->aspect_ratio = data->width / data->hight;
		data->dpi = 10;
		data->caches = (t_vec *)malloc(sizeof(t_vec) * data->width * data->hight);
		if (!data->caches)
			error("malloc failed", data);
		data->pos = 0;
		data->moved = true;
		open_file(argv[1], data);
		data->set.light.normalized = norm_vec(data->set.light.coords);
		data->set.light.normalized.x *= -1;
		data->set.light.normalized.y *= -1;
		data->set.light.normalized.z *= -1;
	}
	else
		error("Wrong nbr of Arguments", data);
}

void	init_mlx(t_data *data)
{
	data->window = mlx_init(data->width, data->hight, "miniRT", true);
	data->img = mlx_new_image(data->window, data->width, data->hight);
}
