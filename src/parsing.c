/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:50:42 by ntalmon           #+#    #+#             */
/*   Updated: 2024/09/30 17:25:11 by ntalmon          ###   ########.fr       */
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
	data->set.ambient.color = multi_vec_wnbr(data->set.ambient.color, data->set.ambient.ratio);
	free_double_p(params);
}

void	parse_camera(t_data *data, char **line)
{
	char	**params;

	params = ft_split(*line, ' ');
	check_param_nbr_2(params, 4, data);
	parse_coords(&data->set.cam.coords, params[1], data);
	parse_normalized_vector(&data->set.cam.direction, params[2], data);
	data->set.cam.fov = ft_atoi(params[3]);
	if (data->set.cam.fov < 0 || data->set.cam.fov > 180)
		error("FOV must be between 0 and 180", data);
	data->set.cam.fov = data->set.cam.fov * (M_PI / 180.0);
	free_double_p(params);
}

void	parse_light(t_data *data, char **line, int *l)
{
	char	**params;

	params = ft_split(*line, ' ');
	check_param_nbr_2(params, 4, data);
	parse_coords(&data->set.light[*l].coords, params[1], data);
	data->set.light[*l].brightness = ft_atof(params[2]);
	if (data->set.light[*l].brightness < 0 \
		|| data->set.light[*l].brightness > 1)
		error("Brightness must be between 0 and 1", data);
	parse_color(&data->set.light[*l].color, params[3], data);
	(*l)++;
	free_double_p(params);
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
	static int	i = 0;
	static int	l = 0;

	if (ft_strncmp(*line, "A ", 2) == 0)
		parse_ambient(data, line);
	if (ft_strncmp(*line, "C ", 2) == 0)
		parse_camera(data, line);
	if (ft_strncmp(*line, "L ", 2) == 0)
		parse_light(data, line, &l);
	if (ft_strncmp(*line, "sp ", 3) == 0)
		parse_sphere(data, line, &i);
	if (ft_strncmp(*line, "pl ", 3) == 0)
		parse_plane(data, line, &i);
	if (ft_strncmp(*line, "cy ", 3) == 0)
		parse_cylinder(data, line, &i);
	check_wrong_line(*line, data);
	return (0);
}
