/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_calc_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:13:15 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/21 13:30:04 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

float	leangth_vec(t_vec3 s1)
{
	return (sqrt(pow(s1.x, 2.0) + pow(s1.y, 2.0) + pow(s1.z, 2.0)));
}

t_vec3	norm_vec(t_vec3 s1)
{
	float	len;

	len = sqrt((s1.x * s1.x) + (s1.y * s1.y) + (s1.z * s1.z));
	if (len == 0)
		return (s1);
	s1.x /= len;
	s1.y /= len;
	s1.z /= len;
	return (s1);
}

float	dot(t_vec3 s1, t_vec3 s2)
{
	return (s1.x * s2.x + s1.y * s2.y + s1.z * s2.z);
}

t_vec3	sub_vec(t_vec3 s1, t_vec3 s2)
{
	t_vec3	result;

	result.x = s1.x - s2.x;
	result.y = s1.y - s2.y;
	result.z = s1.z - s2.z;
	return (result);
}

t_vec3	multi_vec(t_vec3 s1, t_vec3 s2)
{
	t_vec3	result;

	result.x = s1.x * s2.x;
	result.y = s1.y * s2.y;
	result.z = s1.z * s2.z;
	return (result);
}
