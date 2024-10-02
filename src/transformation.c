/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:48:14 by lbohm             #+#    #+#             */
/*   Updated: 2024/10/02 12:57:33 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	create_matrix(t_cylinder *cy)
{
	t_vec3	rz;
	t_vec3	rcy;
	float	angle;
	float	mx[4][4];
	float	my[4][4];
	float	mz[4][4];
	float	t[4][4];
	float	tmp[4][4];
	float	tmp2[4][4];

	rz.x = 0.0;
	rz.y = 0.0;
	rz.z = 1.0;
	rcy = cross_vec(cy->norm, rz);
	angle = acos(dot(cy->norm, rcy) / sqrt(dot(cy->norm, cy->norm)));
	rotate_x(mx, angle, rcy);
	rotate_y(my, angle, rcy);
	rotate_z(mz, angle, rcy);
	translation(t, cy->coords);
	m_multi(tmp, my, mx);
	m_multi(tmp2, mz, tmp);
	m_multi(cy->m, t, tmp2);
	invers_m(cy->mi, cy->m);
}

void	rotate_x(float m[4][4], float angle, t_vec3 axis)
{
	printf("x rotation\n");
	m[0][0] = 1;
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = cos(axis.y * angle);
	m[1][2] = -sin(axis.z * angle);
	m[1][3] = 0;
	m[2][0] = 0;
	m[2][1] = sin(axis.y * angle);
	m[2][2] = cos(axis.z * angle);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
	print_m(m);
}

void	rotate_y(float m[4][4], float angle, t_vec3 axis)
{
	printf("y rotation\n");
	m[0][0] = cos(axis.x * angle);
	m[0][1] = 0;
	m[0][2] = sin(axis.z * angle);
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = -sin(axis.x * angle);
	m[2][1] = 0;
	m[2][2] = cos(axis.z * angle);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	m[3][3] = 1;
	print_m(m);
}

void	rotate_z(float m[4][4], float angle, t_vec3 axis)
{
	printf("z rotation\n");
	m[0][0] = cos(axis.x * angle);
	m[0][1] = -sin(axis.y * angle);
	m[0][2] = 0;
	m[0][3] = 0;
	m[1][0] = sin(axis.x * angle);
	m[1][1] = cos(axis.y * angle);
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
	print_m(m);
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

void	m_multi(float result[4][4], float mat1[4][4], float mat2[4][4])
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			result[i][j] = 0;
			while (k < 4)
			{
				result[i][j] += mat1[i][k] * mat2[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
}

t_vec4	r_vec(float m[4][4], t_vec4 v)
{
	t_vec4	result;

	result.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
	result.y = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
	result.z = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
	result.w = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
	return (result);
}

void	invers_m(float result[4][4], float m[4][4])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 4)
	{
		while (j < 4)
		{
			result[i][j] = m[j][i];
			j++;
		}
		i++;
	}
}
