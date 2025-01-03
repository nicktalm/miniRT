/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:12:15 by lucabohn          #+#    #+#             */
/*   Updated: 2024/11/10 22:11:59 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
# define LIGHTING_H

# include "minimath.h"

typedef struct s_light
{
	t_vec3	coords;
	t_vec3	color;
	t_vec3	norm;
	float	brightness;
	int		end;
}				t_light;

typedef struct s_lighting
{
	t_vec3	light_dir;
	t_vec3	ambient;
	t_vec3	diffuse;
	t_vec3	specular;
	float	len;
}				t_lighting;

typedef struct s_ambient
{
	t_vec3	color;
	float	ratio;
}				t_ambient;

#endif