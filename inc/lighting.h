/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:12:15 by lucabohn          #+#    #+#             */
/*   Updated: 2024/10/31 13:01:41 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
# define LIGHTING_H

# include "minimath.h"

typedef struct s_light
{
	t_vec3	coords;
	float	brightness;
	t_vec3	color;
	t_vec3	norm;
}				t_light;

typedef struct s_lighting
{
	t_vec3	light;
	t_vec3	light_dir;
	t_vec3	diffuse;
	float	diffuse_strength;
}				t_lighting;

typedef struct s_ambient
{
	float	ratio;
	t_vec3	color;
}				t_ambient;

#endif