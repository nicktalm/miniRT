/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:49:14 by lbohm             #+#    #+#             */
/*   Updated: 2024/11/08 15:33:04 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "minimath.h"

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}				t_ray;

typedef struct s_hitpoint
{
	t_vec3		p;
	t_vec3		normal;
	t_vec3		color;
	t_vec3		obj_color;
	float		t;
	int			i;
}				t_hitpoint;

#endif