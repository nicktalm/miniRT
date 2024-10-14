/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:48:14 by lbohm             #+#    #+#             */
/*   Updated: 2024/10/14 14:22:48 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	create_matrix(t_cylinder *cy)
{
	float	angle_x;
	float	angle_z;
	float	mx[4][4];
	float	my[4][4];
	float	mz[4][4];
	float	t[4][4];
	float	s[4][4];
	float	tmp[4][4];
	float	full_r[4][4];

	angle_x = 0.0;
	angle_z = 0.0;
	calc_angle(cy, &angle_x, &angle_z);
	rotate_z(mz, angle_z);
	rotate_x(mx, angle_x);
	multi_m(full_r, mx, mz);
	translation(t, cy->coords);
	multi_m(cy->mt, full_r, t);
	copy_m(tmp, cy->mt);
	create_m_inverse(tmp, cy->mti);
}

void	calc_angle(t_cylinder *cy, float *x, float *z)
{
	double	ratio;

	*z = 0.0;
	ratio = sqrt((cy->norm.x * cy->norm.x) + (cy->norm.y * cy->norm.y));
	if (cy->norm.x == 0.0 && cy->norm.y == 0.0 && fabsf(cy->norm.z) == 1.0)
		*x = atan2(cy->norm.z, ratio);
	else
	{
		if (ratio == 0.0)
			*z = M_PI_2;
		else
			*z = acos(cy->norm.y / ratio);
		*x = atan2(cy->norm.z, ratio);
	}
}

void	rotate_x(float m[4][4], float angle)
{
	m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = cos(angle);
	m[1][2] = -sin(angle);
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = sin(angle);
	m[2][2] = cos(angle);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

void	rotate_y(float m[4][4], float angle)
{
	m[0][0] = cos(angle);
	m[0][1] = 0;
	m[0][2] = sin(angle);
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = -sin(angle);
	m[2][1] = 0;
	m[2][2] = cos(angle);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

void	rotate_z(float m[4][4], float angle)
{
	m[0][0] = cos(angle);
	m[0][1] = -sin(angle);
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = sin(angle);
	m[1][1] = cos(angle);
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

void	translation(float m[4][4], t_vec3 t)
{
	m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = t.x;
	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;
	m[1][3] = t.y;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = 1;
	m[2][3] = t.z;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
}

void	scaling(float m[4][4], float x, float y, float z)
{
	m[0][0] = x;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = y;
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = z;
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
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
