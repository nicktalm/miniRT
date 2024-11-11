/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:13:15 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/11 13:31:06 by lbohm            ###   ########.fr       */
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
	{
		fprintf(stderr, "Error: Zero length vector cannot be normalized.\n");
		return (s1);
	}
	s1.x /= len;
	s1.y /= len;
	s1.z /= len;
	return (s1);
}

float	dot(t_vec3 s1, t_vec3 s2)
{
	return (s1.x * s2.x + s1.y * s2.y + s1.z * s2.z);
}

float	dot4(t_vec4 s1, t_vec4 s2)
{
	return (s1.w * s2.w + s1.x * s2.x + s1.y * s2.y + s1.z * s2.z);
}

t_vec3	sub_vec(t_vec3 s1, t_vec3 s2)
{
	t_vec3	result;

	result.x = s1.x - s2.x;
	result.y = s1.y - s2.y;
	result.z = s1.z - s2.z;
	return (result);
}

t_vec4	sub_vec4(t_vec4 s1, t_vec4 s2)
{
	t_vec4	result;

	result.w = s1.w - s2.w;
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

t_vec3	multi_vec_wnbr(t_vec3 s1, float nbr)
{
	t_vec3	result;

	result.x = s1.x * nbr;
	result.y = s1.y * nbr;
	result.z = s1.z * nbr;
	return (result);
}

t_vec4	multi_vec4_wnbr(t_vec4 s1, float nbr)
{
	t_vec4	result;

	result.x = s1.x * nbr;
	result.y = s1.y * nbr;
	result.z = s1.z * nbr;
	result.w = s1.w * nbr;
	return (result);
}

t_vec3	dev_vec(t_vec3 s1, t_vec3 s2)
{
	t_vec3	result;

	result.x = s1.x / s2.x;
	result.y = s1.y / s2.y;
	result.z = s1.z / s2.z;
	return (result);
}

t_vec3	dev_vec_wnbr(t_vec3 s1, float nbr)
{
	t_vec3	result;

	result.x = s1.x / nbr;
	result.y = s1.y / nbr;
	result.z = s1.z / nbr;
	return (result);
}

t_vec4	dev_vec4_wnbr(t_vec4 s1, float nbr)
{
	t_vec4	result;

	result.w = s1.w / nbr;
	result.x = s1.x / nbr;
	result.y = s1.y / nbr;
	result.z = s1.z / nbr;
	return (result);
}

t_vec3	add_vec(t_vec3 s1, t_vec3 s2)
{
	t_vec3	result;

	result.x = s1.x + s2.x;
	result.y = s1.y + s2.y;
	result.z = s1.z + s2.z;
	return (result);
}

t_vec4	add_vec4(t_vec4 s1, t_vec4 s2)
{
	t_vec4	result;

	result.w = s1.w + s2.w;
	result.x = s1.x + s2.x;
	result.y = s1.y + s2.y;
	result.z = s1.z + s2.z;
	return (result);
}

t_vec3	add_vec_wnbr(t_vec3 s1, float nbr)
{
	t_vec3	result;

	result.x = s1.x + nbr;
	result.y = s1.y + nbr;
	result.z = s1.z + nbr;
	return (result);
}

t_vec3	ray_vec(t_vec3 origin, float t, t_vec3 dir)
{
	return (add_vec(origin, multi_vec_wnbr(dir, t)));
}

t_vec4	ray_vec4(t_vec4 origin, float t, t_vec4 direction)
{
	t_vec4	result;

	result.w = origin.w + t * direction.w;
	result.x = origin.x + t * direction.x;
	result.y = origin.y + t * direction.y;
	result.z = origin.z + t * direction.z;
	return (result);
}

t_vec3	cross_vec(t_vec3 s1, t_vec3 s2)
{
	t_vec3	result;

	result.x = (s1.y * s2.z) - (s1.z * s2.y);
	result.y = (s1.z * s2.x) - (s1.x * s2.z);
	result.z = (s1.x * s2.y) - (s1.y * s2.x);
	return (result);
}

t_vec3	reflect_vec3(t_vec3 s1, t_vec3 s2)
{
	return (sub_vec(s1, multi_vec_wnbr(s2, 2 * dot(s1, s2))));
}

int	cmp_vec(t_vec3 s1, t_vec3 s2)
{
	if (s1.x == s2.x)
	{
		if (s1.y == s2.y)
		{
			if (s1.z == s2.z)
				return (0);
		}
	}
	return (1);
}

t_vec3	copy_vec(t_vec3 s1)
{
	t_vec3	result;

	result.x = s1.x;
	result.y = s1.y;
	result.z = s1.z;
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

t_vec3	convert_to_vec3(t_vec4 s1)
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

t_vec4	convert_to_vec4(t_vec3 s1, float w)
{
	t_vec4	result;

	result.x = s1.x;
	result.y = s1.y;
	result.z = s1.z;
	result.w = w;
	return (result);
}
