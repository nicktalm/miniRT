/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:46:05 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/21 19:15:21 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	check_obj(t_data *data, t_hitpoint *hit, t_ray *ray, int i);

void	check_hit(t_ray *ray, t_hitpoint *hit, t_data *data)
{
	int	i;

	i = 0;
	hit->i = 0;
	hit->t = __FLT_MAX__;
	while (i < data->set.obj_count)
	{
		check_obj(data, hit, ray, i);
		i++;
	}
	if (data->set.obj_count != 0)
		in_out_object(ray, hit);
}

void	check_obj(t_data *data, t_hitpoint *hit, t_ray *ray, int i)
{
	if (data->set.obj[i].type == SPHERE)
	{
		if (calc_sp(data, data->set.obj[i].form.sp, *ray, hit))
			hit->i = i;
	}
	else if (data->set.obj[i].type == PLANE)
	{
		if (calc_pl(data, data->set.obj[i].form.pl, *ray, hit))
			hit->i = i;
	}
	else if (data->set.obj[i].type == CYLINDER)
	{
		if (calc_cy(data, data->set.obj[i].form.cy, *ray, hit))
			hit->i = i;
	}
	else
	{
		if (calc_cn(data, data->set.obj[i].form.cn, *ray, hit))
			hit->i = i;
	}
}
