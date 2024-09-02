/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:50:42 by ntalmon           #+#    #+#             */
/*   Updated: 2024/09/02 11:44:35 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	parse_ambient(t_data *data, char **line)
{
	char	**params;

	params = ft_split(*line, ' ');
	check_param_nbr_2(params, 3, data);
	data->set.ambient.ratio = ft_atof(params[1]);
	if (data->set.ambient.ratio < 0 || data->set.ambient.ratio > 1)
		error("Ambient light ratio must be between 0 and 1", data);
	parse_color(&data->set.ambient.color, params[2], data);
	free(params[0]);
	free(params[1]);
	free(params[2]);
	free(params);
}

void	parse_camera(t_data *data, char **line)
{
	char	**params;

	params = ft_split(*line, ' ');
	check_param_nbr_2(params, 4, data);
	parse_coords(&data->set.cam.coords, params[1], data);
	parse_normalized_vector(&data->set.cam.normalized, params[2], data);
	data->set.cam.fov = ft_atoi(params[3]);
	if (data->set.cam.fov < 0 || data->set.cam.fov > 180)
		error("FOV must be between 0 and 180", data);
	free(params[0]);
	free(params[1]);
	free(params[2]);
	free(params[3]);
	free(params);
}

void	parse_light(t_data *data, char **line)
{
	char	**params;

	params = ft_split(*line, ' ');
	check_param_nbr_2(params, 4, data);
	parse_coords(&data->set.light.coords, params[1], data);
	data->set.light.brightness = ft_atof(params[2]);
	if (data->set.light.brightness < 0 || data->set.light.brightness > 1)
		error("Brightness must be between 0 and 1", data);
	parse_color(&data->set.light.color, params[3], data);
	free(params[0]);
	free(params[1]);
	free(params[2]);
	free(params[3]);
	free(params);
}

void	check_wrong_line(char *line, t_data *data)
{
	if (ft_strncmp(line, "A ", 2) != 0 && ft_strncmp(line, "C ", 2) != 0
		&& ft_strncmp(line, "L ", 2) != 0 && ft_strncmp(line, "sp ", 3) != 0
		&& ft_strncmp(line, "pl ", 3) != 0 && ft_strncmp(line, "cy ", 3) != 0
		&& ft_strncmp(line, "\n", 1) != 0 && line[0] != '\0')
		error("Wrong line", data);
}

int	parse_line(t_data *data, char **line)
{
	if (ft_strncmp(*line, "A ", 2) == 0)
		parse_ambient(data, line);
	if (ft_strncmp(*line, "C ", 2) == 0)
		parse_camera(data, line);
	if (ft_strncmp(*line, "L ", 2) == 0)
		parse_light(data, line);
	if (ft_strncmp(*line, "sp ", 3) == 0)
		parse_sphere(data, line);
	if (ft_strncmp(*line, "pl ", 3) == 0)
		parse_plane(data, line);
	if (ft_strncmp(*line, "cy ", 3) == 0)
		parse_cylinder(data, line);
	check_wrong_line(*line, data);
	return (0);
}
