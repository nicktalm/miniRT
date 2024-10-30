/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucabohn <lucabohn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:11:35 by lucabohn          #+#    #+#             */
/*   Updated: 2024/10/30 09:14:53 by lucabohn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "transformation.h"

typedef struct s_camera
{
	t_vec3	coords;
	t_vec3	direction;
	float	fov;
}				t_camera;

typedef struct s_viewport
{
	t_vec3	size;
	t_vec3	u;
	t_vec3	v;
	t_vec3	du;
	t_vec3	dv;
	t_vec3	upper_left;
	t_vec3	p00;
}				t_viewport;

#endif