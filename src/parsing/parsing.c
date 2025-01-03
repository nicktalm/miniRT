/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:50:42 by ntalmon           #+#    #+#             */
/*   Updated: 2024/11/22 20:00:20 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	parse_ambient(t_data *data, char *line)
{
	data->garbage.params = ft_split(line, ' ');
	check_param_nbr_2(data->garbage.params, 3, data);
	data->set.ambient.ratio = ft_atof(data->garbage.params[1]);
	if (data->set.ambient.ratio < 0 || data->set.ambient.ratio > 1)
	{
		error("Ambient light ratio must be between 0 and 1", data);
	}
	parse_color(&data->set.ambient.color, data->garbage.params[2], data);
	free_double_p(data->garbage.params);
	data->garbage.params = NULL;
}

void	parse_camera(t_data *data, char *line)
{
	data->garbage.params = ft_split(line, ' ');
	check_param_nbr_2(data->garbage.params, 4, data);
	parse_coords(&data->set.cam.coords, data->garbage.params[1], data);
	parse_normalized_vector(&data->set.cam.direction,
		data->garbage.params[2], data);
	data->set.cam.fov = ft_atof(data->garbage.params[3]);
	if (data->set.cam.fov < 0 || data->set.cam.fov > 180)
	{
		error("FOV must be between 0 and 180", data);
	}
	data->set.cam.fov *= (M_PI / 180.0);
	free_double_p(data->garbage.params);
	data->garbage.params = NULL;
}

void	parse_light(t_data *data, char *line, int *l)
{
	data->garbage.params = ft_split(line, ' ');
	check_param_nbr_2(data->garbage.params, 4, data);
	parse_coords(&data->set.light[*l].coords, data->garbage.params[1], data);
	data->set.light[*l].brightness = ft_atof(data->garbage.params[2]);
	if (data->set.light[*l].brightness < 0
		|| data->set.light[*l].brightness > 1)
	{
		error("Brightness must be between 0 and 1", data);
	}
	if (data->set.light[*l].brightness == 0.0)
		data->set.light[*l].end = 1;
	else
		data->set.light[*l].end = 2;
	parse_color(&data->set.light[*l].color, data->garbage.params[3], data);
	(*l)++;
	free_double_p(data->garbage.params);
	data->garbage.params = NULL;
}

void	check_wrong_line(char *line, t_data *data)
{
	if (ft_strncmp(line, "A ", 2) != 0 && ft_strncmp(line, "C ", 2) != 0
		&& ft_strncmp(line, "L ", 2) != 0 && ft_strncmp(line, "sp ", 3) != 0
		&& ft_strncmp(line, "pl ", 3) != 0 && ft_strncmp(line, "cy ", 3) != 0
		&& ft_strncmp(line, "cn ", 3) && ft_strncmp(line, "\n", 1) != 0
		&& line[0] != '\0')
		error("Wrong line", data);
}

int	parse_line(t_data *data, char *line)
{
	static int	i = 0;
	static int	l = 0;

	if (ft_strncmp(line, "A ", 2) == 0)
		parse_ambient(data, line);
	if (ft_strncmp(line, "C ", 2) == 0)
		parse_camera(data, line);
	if (ft_strncmp(line, "L ", 2) == 0)
		parse_light(data, line, &l);
	if (ft_strncmp(line, "sp ", 3) == 0)
		parse_sphere(data, line, &i);
	if (ft_strncmp(line, "pl ", 3) == 0)
		parse_plane(data, line, &i);
	if (ft_strncmp(line, "cy ", 3) == 0)
		parse_cylinder(data, line, &i);
	if (ft_strncmp(line, "cn ", 3) == 0)
		parse_cone(data, line, &i);
	check_wrong_line(line, data);
	return (0);
}
