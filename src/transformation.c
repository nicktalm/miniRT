/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:48:14 by lbohm             #+#    #+#             */
/*   Updated: 2024/10/08 21:01:40 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

// void	create_matrix(t_cylinder *cy)
// {
// 	t_vec3	rz;
// 	t_vec3	rcy;
// 	float	leange;
// 	float	angle;
// 	float	anglex;
// 	float	angley;
// 	float	anglez;
// 	float	mx[4][4];
// 	float	my[4][4];
// 	float	mz[4][4];
// 	float	t[4][4];
// 	float	tmp[4][4];
// 	float	tmp2[4][4];

// 	rz.x = 0.0;
// 	rz.y = 0.0;
// 	rz.z = 1.0;
// 	rcy = cross_vec(cy->norm, rz);
// 	printf("rcy x = %f y = %f z = %f\n", rcy.x, rcy.y, rcy.z);
// 	translation(t, cy->coords);
// 	if (rcy.x == 0.0 && rcy.y == 0.0 && rcy.z == 0.0)
// 	{
// 		normal_m(cy->m);
// 		copy_m(cy->mt, t);
// 	}
// 	else
// 	{
// 		angle = acos(dot(cy->norm, rz) / (sqrt(dot(cy->norm, cy->norm)) * sqrt(dot(rz, rz))));
// 		anglex = angle * rcy.x;
// 		angley = angle * rcy.y;
// 		anglez = angle * rcy.z;
// 		printf("anglex = %f angley = %f anglez = %f\n", anglex, angley, anglez);
// 		rotate_x(mx, anglex);
// 		rotate_y(my, angley);
// 		rotate_z(mz, anglez);
// 		m_multi(tmp, my, mx);
// 		m_multi(cy->m, mz, tmp);
// 		m_multi(tmp, my, mx);
// 		m_multi(tmp2, mz, tmp);
// 		m_multi(cy->mt, t, tmp2);
// 	}
// 	printf("mt\n");
// 	print_m(cy->mt);
// 	invers_m(cy->mi, cy->m);
// 	invers_m(cy->mti, cy->mt);
// }

void	create_matrix(t_cylinder *cy)
{
	float	angle_x;
	float	angle_z;
	float	ratio;
	float	mx[4][4];
	float	my[4][4];
	float	mz[4][4];
	float	t[4][4];
	float	s[4][4];
	float	tmp[4][4];
	float	tmp2[4][4];

	ratio = sqrt((cy->norm.x * cy->norm.x) + (cy->norm.y * cy->norm.y));
	if (ratio == 0.0)
		angle_z = M_PI_2;
	else
		angle_z = acos(cy->norm.y / ratio);
	angle_x = acos(ratio);
	scaling(s, cy->radius, 1, cy->radius);
	translation(t, cy->coords);
	rotate_x(mx, angle_x);
	rotate_z(mz, angle_z);
	m_multi(tmp, mz, mx);
	m_multi(tmp2, tmp, s);
	m_multi(cy->mt, t, tmp2);
	invers_m(cy->mti, cy->mt);
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

void	m_multi(float result[4][4], float m1[4][4], float m2[4][4])
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
			result[i][j] = m1[i][0] * m2[0][j]
				+ m1[i][1] * m2[1][j]
				+ m1[i][2] * m2[2][j]
				+ m1[i][3] * m2[3][j];
			j++;
		}
		i++;
	}
}

t_vec3	r_vec(float m[4][4], t_vec3 v)
{
	t_vec3	result;

	result.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3];
	result.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3];
	result.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3];
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

void	copy_m(float result[4][4], float m[4][4])
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result[i][j] = m[i][j];
			j++;
		}
		i++;
	}
}

void	normal_m(float result[4][4])
{
	result[0][0] = 1;
	result[0][1] = 0;
	result[0][2] = 0;
	result[0][3] = 0;
	result[1][0] = 0;
	result[1][1] = 1;
	result[1][2] = 0;
	result[1][3] = 0;
	result[2][0] = 0;
	result[2][1] = 0;
	result[2][2] = 1;
	result[2][3] = 0;
	result[3][0] = 0;
	result[3][1] = 0;
	result[3][2] = 0;
	result[3][3] = 1;
}