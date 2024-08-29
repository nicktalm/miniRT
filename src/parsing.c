/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:50:42 by ntalmon           #+#    #+#             */
/*   Updated: 2024/08/29 13:26:13 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	parse_ambient(t_data *data, char **line)
{
	char	**params;

	params = ft_split(*line, ' ');
	data->set.ambient.ratio = ft_atof(params[1]);
	if (data->set.ambient.ratio < 0 || data->set.ambient.ratio > 1)
		error("Error: Ambient light ratio must be between 0 and 1\n");
	parse_color(&data->set.ambient.color, params[2]);
}

void	parse_camera(t_data *data, char **line)
{
	char	**params;

	params = ft_split(*line, ' ');
	parse_coords(&data->set.cam.coords, params[1]);
	parse_normalized_vector(&data->set.cam.normalized, params[2]);
	data->set.cam.fov = ft_atoi(params[3]);
	if (data->set.cam.fov < 0 || data->set.cam.fov > 180)
		error("Error: FOV must be between 0 and 180\n");
}

void	parse_light(t_data *data, char **line)
{
	char	**params;

	params = ft_split(*line, ' ');
	parse_coords(&data->set.light.coords, params[1]);
	data->set.light.brightness = ft_atof(params[2]);
	if (data->set.light.brightness < 0 || data->set.light.brightness > 1)
		error("Error: Brightness must be between 0 and 1\n");
	parse_color(&data->set.light.color, params[3]);
}

int	parse_line(t_data *data, char **line)
{
	if (ft_strncmp(*line, "A", 1) == 0)
		parse_ambient(data, line);
	if (ft_strncmp(*line, "C", 1) == 0)
		parse_camera(data, line);
	if (ft_strncmp(*line, "L", 1) == 0)
		parse_light(data, line);
	if (ft_strncmp(*line, "sp", 2) == 0)
		parse_sphere(data, line);
	if (ft_strncmp(*line, "pl", 2) == 0)
		parse_plane(data, line);
	if (ft_strncmp(*line, "cy", 2) == 0)
		parse_cylinder(data, line);
	return (0);
}
