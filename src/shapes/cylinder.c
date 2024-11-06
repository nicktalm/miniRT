/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:01:37 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/06 22:04:01 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	calc_cy(t_cylinder cy, t_ray ray, t_hitpoint *hit, int i)
{
	float	t;
	float	a;
	float	b;
	float	c;
	float	dis;
	t_ray	test;
	t_vec3	tmp;

	test.origin = convert_to_vec3(r_vec(cy.mtt, convert_to_vec4(ray.origin, 1)));
	test.direction = convert_to_vec3(r_vec(cy.mtt, convert_to_vec4(ray.direction, 0)));
	top_bottom(cy, hit, test, i, 0);
	test.origin = convert_to_vec3(r_vec(cy.mtb, convert_to_vec4(ray.origin, 1)));
	test.direction = convert_to_vec3(r_vec(cy.mtb, convert_to_vec4(ray.direction, 0)));
	top_bottom(cy, hit, test, i, 1);
	ray.origin = convert_to_vec3(r_vec(cy.mt, convert_to_vec4(ray.origin, 1)));
	ray.direction = convert_to_vec3(r_vec(cy.mt, convert_to_vec4(ray.direction, 0)));
	a = pow(ray.direction.x, 2) + pow(ray.direction.z, 2);
	b = ray.origin.x * ray.direction.x + ray.origin.z * ray.direction.z;
	c = pow(ray.origin.x, 2) + pow(ray.origin.z, 2) - cy.radius * cy.radius;
	dis = (b * b) - (a * c);
	if (dis > 0.0)
	{
		t = (-b - sqrt(dis)) / a;
		if (t <= 0.0 || t >= INFINITY)
		{
			t = (-b + sqrt(dis)) / a;
			if (t <= 0.0 || t >= INFINITY)
				t = __FLT_MAX__;
		}
		if (hit->t > t)
		{
			tmp = ray_vec(ray.origin, t, ray.direction);
			if (fabsf(tmp.y) <= cy.height / 2.0)
			{
				hit->p = convert_to_vec3(r_vec(cy.mti, convert_to_vec4(tmp, 1)));
				cy_norm_calc(cy, hit);
				// printf("hit p x = %f y = %f z = %f\n", hit->p.x, hit->p.y, hit->p.z);
				// printf("hit normal x = %f y = %f z = %f\n", hit->normal.x, hit->normal.y, hit->normal.z);
				hit->t = t;
				hit->i = i;
			}
		}
	}
}

void	top_bottom(t_cylinder cy, t_hitpoint *hit, t_ray ray, int i, int lol)
{
	float	dis;
	float	t;
	t_vec3	tmp;
	t_vec3	test;

	test.x = 0.0;
	test.y = 1.0;
	test.z = 0.0;
	t = -dot(test, ray.origin) / dot(test, ray.direction);
	if (t > 0.0 && hit->t > t)
	{
		tmp = ray_vec(ray.origin, t, ray.direction);
		dis = pow(tmp.x, 2.0) + pow(tmp.z, 2.0);
		if (dis <= cy.radius * cy.radius)
		{
			if (lol == 0)
				hit->p = convert_to_vec3(r_vec(cy.mtit, convert_to_vec4(tmp, 1)));
			else
				hit->p = convert_to_vec3(r_vec(cy.mtib, convert_to_vec4(tmp, 1)));
			hit->normal = cy.norm;
			hit->t = t;
			hit->i = i;
		}
	}
}

void	cy_norm_calc(t_cylinder cy, t_hitpoint *hit)
{
	t_vec3	center;
	t_vec3	oc;

	oc = sub_vec(hit->p, cy.coords);
	center = add_vec(cy.coords, multi_vec_wnbr(cy.norm,
				dot(oc, cy.norm) / dot(cy.norm, cy.norm)));
	hit->normal = norm_vec(sub_vec(hit->p, center));
}

void	create_m_cy(t_cylinder *cy)
{
	float	angle_x;
	float	angle_z;
	float	t[4][4];
	float	tmp[4][4];
	float	full_r[4][4];
	t_vec3	test;

	angle_x = 0.0;
	angle_z = 0.0;
	calc_angle_cy(cy, &angle_x, &angle_z);
	printf("angle x = %f angle z = %f\n", angle_x * (180 / M_PI), angle_z * (180 / M_PI));
	get_full_r(full_r, angle_x, 0.0, angle_z);
	print_m(full_r);
	translation(t, cy->coords);
	print_m(t);
	multi_m(cy->mt, t, full_r);
	print_m(cy->mt);
	copy_m(tmp, cy->mt);
	if (!create_m_inverse(tmp, cy->mti))
		printf("fail\n");
	print_m(cy->mti);
	test = ray_vec(cy->coords, cy->height / 2.0, cy->norm);
	translation(t, test);
	multi_m(cy->mtt, t, full_r);
	copy_m(tmp, cy->mtt);
	create_m_inverse(tmp, cy->mtit);
	test = ray_vec(cy->coords, cy->height / -2.0, cy->norm);
	translation(t, test);
	multi_m(cy->mtb, t, full_r);
	copy_m(tmp, cy->mtb);
	create_m_inverse(tmp, cy->mtib);

	t_vec3	input = {5, 5, 5};
	t_vec3	output;

	printf("input x = %f y = %f z = %f\n", input.x, input.y, input.z);
	output	= convert_to_vec3(r_vec(cy->mt, convert_to_vec4(input, 1)));
	printf("output mt x = %f y = %f z = %f\n", output.x, output.y, output.z);
	output	= convert_to_vec3(r_vec(cy->mti, convert_to_vec4(output, 1)));
	printf("\033[1;31moutput mti x = %f y = %f z = %f\033[0m\n", output.x, output.y, output.z);
	printf("input x = %f y = %f z = %f\n", input.x, input.y, input.z);
	output	= convert_to_vec3(r_vec(cy->mtt, convert_to_vec4(input, 1)));
	printf("output mtt x = %f y = %f z = %f\n", output.x, output.y, output.z);
	output	= convert_to_vec3(r_vec(cy->mtit, convert_to_vec4(output, 1)));
	printf("\033[1;31moutput mtit x = %f y = %f z = %f\033[0m\n", output.x, output.y, output.z);
	printf("input x = %f y = %f z = %f\n", input.x, input.y, input.z);
	output	= convert_to_vec3(r_vec(cy->mtb, convert_to_vec4(input, 1)));
	printf("output mtb x = %f y = %f z = %f\n", output.x, output.y, output.z);
	output	= convert_to_vec3(r_vec(cy->mtib, convert_to_vec4(output, 1)));
	printf("\033[1;31moutput mtib x = %f y = %f z = %f\033[0m\n", output.x, output.y, output.z);
}

void	calc_angle_cy(t_cylinder *cy, float *x, float *z)
{
	double	ratio;
	t_vec3	test = {0,1,0};
	t_vec3	test2 = cross_vec(cy->norm, test);

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
	if (test2.z < 0.0)
		*z *= -1.0;
	if (test2.x < 0.0)
	{
		if (*x > 0.0)
			*x *= -1.0;
	}
	else
	{
		if (*x < 0.0)
			*x *= -1.0;
	}
}
