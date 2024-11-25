/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:29:09 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/25 11:17:41 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	get_color(t_data *data, t_ray *ray, t_hitpoint *hit)
{
	t_vec3	index;
	t_vec3	full_color;
	t_ray	first;

	full_color.x = 0.0;
	full_color.y = 0.0;
	full_color.z = 0.0;
	first = *ray;
	index.x = 0;
	index.y = 0;
	while (index.y < data->set.light_count)
	{
		*ray = first;
		index.x = 0;
		if (light_loop(data, ray, hit, index))
			return ;
		full_color = add_vec(full_color, hit->color);
		index.y++;
	}
	hit->color = full_color;
}

bool	light_loop(t_data *data, t_ray *ray, t_hitpoint *hit, t_vec3 index)
{
	while (index.x < data->set.light[(int)index.y].end)
	{
		check_hit(ray, hit, data);
		if (hit->t != __FLT_MAX__)
		{
			if (!get_distanz(hit, data->set.light[(int)index.y], index.x))
				return (false);
			if (index.x == 0)
				obj_shading(data, hit, ray, data->set.light[(int)index.y]);
			else
				shading(data, hit, data->set.light[(int)index.y]);
		}
		else
		{
			if (index.x == 0)
			{
				hit->color = data->bg;
				return (true);
			}
			return (false);
		}
		index.x++;
	}
	return (false);
}

bool	get_distanz(t_hitpoint *hit, t_light light, int i)
{
	static int		distanz = 0;
	static t_vec3	color;
	static int		ib = 0;
	static t_vec3	pb = {0, 0, 0};

	if (i == 0)
	{
		distanz = leangth_vec(sub_vec(hit->p, light.coords));
		pb = hit->p;
		color = hit->obj_color;
		ib = hit->i;
	}
	else
	{
		if (distanz < leangth_vec(sub_vec(pb, hit->p))
			|| hit->i == ib)
			return (false);
		hit->obj_color = color;
		hit->i = ib;
	}
	return (true);
}
