/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:50:42 by ntalmon           #+#    #+#             */
/*   Updated: 2024/08/28 11:23:18 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	parse_ambient(t_data *data, char **line)
{
	char	**params;
	char	**color;
	int		i;

	i = 0;
	params = ft_split(*line, ' ');
	data->set.ambient.ratio = ft_atof(params[1]);
	if (data->set.ambient.ratio < 0 || data->set.ambient.ratio > 1)
		error("Error: Ambient light ratio must be between 0 and 1\n");
	color = ft_split(params[2], ',');
	data->set.ambient.color.x = ft_atof(color[0]);
	if (data->set.ambient.color.x < 0 || data->set.ambient.color.x > 255)
		error("Error: RGB values must be between 0 and 255\n");
	data->set.ambient.color.y = ft_atof(color[1]);
	if (data->set.ambient.color.y < 0 || data->set.ambient.color.y > 255)
		error("Error: RGB values must be between 0 and 255\n");
	data->set.ambient.color.z = ft_atof(color[2]);
	if (data->set.ambient.color.z < 0 || data->set.ambient.color.z > 255)
		error("Error: RGB values must be between 0 and 255\n");
}

void	parse_camera(t_data *data, char **line)
{
	char	**params;
	char	**coords;
	char	**normalized;

	params = ft_split(*line, ' ');
	coords = ft_split(params[1], ',');
	data->set.cam.coords.x = ft_atof(coords[0]);
	data->set.cam.coords.y = ft_atof(coords[1]);
	data->set.cam.coords.z = ft_atof(coords[2]);
	normalized = ft_split(params[2], ',');
	data->set.cam.normalized.x = ft_atof(normalized[0]);
	if (data->set.cam.normalized.x < -1 || data->set.cam.normalized.x > 1)
		error("Error: Normalized vector must be between -1 and 1\n");
	data->set.cam.normalized.y = ft_atof(normalized[1]);
	if (data->set.cam.normalized.y < -1 || data->set.cam.normalized.y > 1)
		error("Error: Normalized vector must be between -1 and 1\n");
	data->set.cam.normalized.z = ft_atof(normalized[2]);
	if (data->set.cam.normalized.z < -1 || data->set.cam.normalized.z > 1)
		error("Error: Normalized vector must be between -1 and 1\n");
	data->set.cam.fov = ft_atoi(params[3]);
	if (data->set.cam.fov < 0 || data->set.cam.fov > 180)
		error("Error: FOV must be between 0 and 180\n");
}

void	parse_light(t_data *data, char **line)
{
	char	**params;
	char	**coords;
	char	**color;

	params = ft_split(*line, ' ');
	coords = ft_split(params[1], ',');
	data->set.light.coords.x = ft_atof(coords[0]);
	data->set.light.coords.y = ft_atof(coords[1]);
	data->set.light.coords.z = ft_atof(coords[2]);
	data->set.light.brightness = ft_atof(params[2]);
	if (data->set.light.brightness < 0 || data->set.light.brightness > 1)
		error("Error: Brightness must be between 0 and 1\n");
	color = ft_split(params[3], ',');
	data->set.light.color.x = ft_atof(color[0]);
	if (data->set.light.color.x < 0 || data->set.light.color.x > 255)
		error("Error: RGB values must be between 0 and 255\n");
	data->set.light.color.y = ft_atof(color[1]);
	if (data->set.light.color.y < 0 || data->set.light.color.y > 255)
		error("Error: RGB values must be between 0 and 255\n");
	data->set.light.color.z = ft_atof(color[2]);
	if (data->set.light.color.z < 0 || data->set.light.color.z > 255)
		error("Error: RGB values must be between 0 and 255\n");
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
