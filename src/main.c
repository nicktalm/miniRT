/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:24:36 by ntalmon           #+#    #+#             */
/*   Updated: 2024/08/26 16:32:45 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	main(void)
{
	t_data	data;

	data.set.ambient.range = 0.2;
	data.set.ambient.color.x = 255;
	data.set.ambient.color.y = 255;
	data.set.ambient.color.z = 255;
	data.set.cam.coords.x = -50.0;
	data.set.cam.coords.y = 0;
	data.set.cam.coords.z = 20;
	data.set.cam.normalized.x = 0.0;
	data.set.cam.normalized.y = 0.0;
	data.set.cam.normalized.z = 1.0;
	data.set.cam.fov = 70;
	data.set.light.coords.x = -40.0;
	data.set.light.coords.y = 50.0;
	data.set.light.coords.z = 0.0;
	data.set.light.brightness = 0.6;
	data.set.light.color.x = 10;
	data.set.light.color.y = 0;
	data.set.light.color.z = 255;
	data.set.sp[0].coords.x = 0.0;
	data.set.sp[0].coords.y = 0.0;
	data.set.sp[0].coords.z = 20.6;
	data.set.sp[0].diameter = 12.6;
	data.set.sp[0].color.x = 10;
	data.set.sp[0].color.y = 0;
	data.set.sp[0].color.z = 255;
	data.set.pl[0].coords.x = 0.0;
	data.set.pl[0].coords.y = 0.0;
	data.set.pl[0].coords.z = -10.0;
	data.set.pl[0].normalized.x = 0.0;
	data.set.pl[0].normalized.y = 1.0;
	data.set.pl[0].normalized.z = 0.0;
	data.set.pl[0].color.x = 0;
	data.set.pl[0].color.y = 0;
	data.set.pl[0].color.z = 255;
	data.set.cy[0].coords.x = 50.0;
	data.set.cy[0].coords.y = 0.0;
	data.set.cy[0].coords.z = 20.6;
	data.set.cy[0].normalized.x = 0.0;
	data.set.cy[0].normalized.y = 0.0;
	data.set.cy[0].normalized.z = 1.0;
	data.set.cy[0].diameter = 14.2;
	data.set.cy[0].height = 21.42;
	data.set.cy[0].color.x = 10;
	data.set.cy[0].color.y = 0;
	data.set.cy[0].color.z = 255;
	return (0);
}
