/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_calc_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:28:35 by ntalmon           #+#    #+#             */
/*   Updated: 2024/11/21 13:29:52 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_vec3	ray_vec(t_vec3 origin, float t, t_vec3 dir)
{
	return (add_vec(origin, multi_vec_wnbr(dir, t)));
}

t_vec3	cross_vec(t_vec3 s1, t_vec3 s2)
{
	t_vec3	result;

	result.x = (s1.y * s2.z) - (s1.z * s2.y);
	result.y = (s1.z * s2.x) - (s1.x * s2.z);
	result.z = (s1.x * s2.y) - (s1.y * s2.x);
	return (result);
}

t_vec4	r_vec(float m[4][4], t_vec4 v)
{
	t_vec4	result;

	result.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
	result.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
	result.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
	result.w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;
	return (result);
}

t_vec3	con_to_vec3(t_vec4 s1)
{
	t_vec3	result;

	if (s1.w == 0 || s1.w == 1)
	{
		result.x = s1.x;
		result.y = s1.y;
		result.z = s1.z;
	}
	else
	{
		result.x = s1.x / s1.w;
		result.y = s1.y / s1.w;
		result.z = s1.z / s1.w;
	}
	return (result);
}

t_vec4	con_to_vec4(t_vec3 s1, float w)
{
	t_vec4	result;

	result.x = s1.x;
	result.y = s1.y;
	result.z = s1.z;
	result.w = w;
	return (result);
}
