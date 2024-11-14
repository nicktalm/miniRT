/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:52:19 by ntalmon           #+#    #+#             */
/*   Updated: 2024/11/14 14:19:03 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	ft_count_params(char **params)
{
	int	i;

	i = 0;
	while (params[i])
		i++;
	return (i);
}

void	parse_textures(t_data *data, char *texture, xpm_t *obj)
{
	texture += 8;
	obj = mlx_load_xpm42(texture);
	if (!obj)
		error("load xpm file", data);
}

void	parse_bump_map(t_data *data, char *bump_map, xpm_t *obj)
{
	bump_map += 9;
	obj = mlx_load_xpm42(bump_map);
	if (!obj)
		error("load xpm file", data);
}

int	is_texture(char *param)
{
	if (ft_strncmp(param, "texture=", 8) == 0)
		return (1);
	return (0);
}

int	is_bump_map(char *param)
{
	if (ft_strncmp(param, "bump_map=", 9) == 0)
		return (1);
	return (0);
}

void	parse_texture_or_bump_map(t_data *data, char *param, xpm_t **texture, xpm_t **bump_map)
{
	if (is_texture(param))
	{
		if (*texture != NULL)
			error("Duplicate texture parameter", data);
		parse_textures(data, param, *texture);
		*texture = mlx_load_xpm42(param + 8);
	}
	else if (is_bump_map(param))
	{
		if (*bump_map != NULL)
			error("Duplicate bump map parameter", data);
		parse_bump_map(data, param, *bump_map);
		*bump_map = mlx_load_xpm42(param + 9);
	}
	else
		error("Invalid parameter", data);
}

void	parse_sphere(t_data *data, char **line, int *i)
{
	char	**params;
	int		nbr_params;

	params = ft_split(*line, ' ');
	nbr_params = ft_count_params(params);
	if (nbr_params < 4 || nbr_params > 6)
		error("Invalid number of parameters for sphere", data);
	data->set.obj[*i].form.sp.texture = NULL;
	data->set.obj[*i].form.sp.bump_map = NULL;
	if (nbr_params >= 5)
		parse_texture_or_bump_map(data, params[4], &data->set.obj[*i].form.sp.texture, &data->set.obj[*i].form.sp.bump_map);
	if (nbr_params == 6)
		parse_texture_or_bump_map(data, params[5], &data->set.obj[*i].form.sp.texture, &data->set.obj[*i].form.sp.bump_map);
	data->set.obj[*i].type = SPHERE;
	parse_coords(&data->set.obj[*i].form.sp.coords, params[1], data);
	data->set.obj[*i].form.sp.diameter = ft_atof(params[2]);
	data->set.obj[*i].form.sp.radius = data->set.obj[*i].form.sp.diameter / 2.0;
	parse_color(&data->set.obj[*i].form.sp.color, params[3], data);
	create_m_sp(&data->set.obj[*i].form.sp);
	(*i)++;
	free_double_p(params);
}

void	parse_plane(t_data *data, char **line, int *i)
{
	char	**params;
	int		nbr_params;

	params = ft_split(*line, ' ');
	nbr_params = ft_count_params(params);
	if (nbr_params < 4 || nbr_params > 7)
		error("Invalid number of parameters for plane", data);
	data->set.obj[*i].form.pl.bump_map = NULL;
	data->set.obj[*i].form.pl.texture = NULL;
	data->set.obj[*i].form.pl.length = 0.0;
	data->set.obj[*i].form.pl.width = 0.0;
	if (nbr_params >= 5)
	{
		if (ft_isdigit(params[4][0]))
			parse_surface(&data->set.obj[*i].form.pl, params[4], data);
		else
			parse_texture_or_bump_map(data, params[4], &data->set.obj[*i].form.pl.texture, &data->set.obj[*i].form.pl.bump_map);
	}
	if (nbr_params >= 6)
	{
		if (ft_isdigit(params[5][0]))
			parse_surface(&data->set.obj[*i].form.pl, params[5], data);
		else
			parse_texture_or_bump_map(data, params[5], &data->set.obj[*i].form.pl.texture, &data->set.obj[*i].form.pl.bump_map);
	}
	if (nbr_params == 7)
	{
		if (ft_isdigit(params[6][0]))
			parse_surface(&data->set.obj[*i].form.pl, params[6], data);
	}
	data->set.obj[*i].type = PLANE;
	parse_coords(&data->set.obj[*i].form.pl.coords, params[1], data);
	parse_normalized_vector(&data->set.obj[*i].form.pl.norm, params[2], data);
	parse_color(&data->set.obj[*i].form.pl.color, params[3], data);
	create_m_pl(&data->set.obj[*i].form.pl);
	(*i)++;
	free_double_p(params);
}

void	parse_cylinder(t_data *data, char **line, int *i)
{
	char	**params;
	int		nbr_params;

	params = ft_split(*line, ' ');
	nbr_params = ft_count_params(params);
	if (nbr_params < 6 || nbr_params > 8)
		error("Invalid number of parameters for cylinder", data);
	data->set.obj[*i].form.cy.bump_map = NULL;
	data->set.obj[*i].form.cy.texture = NULL;
	if (nbr_params >= 7)
		parse_texture_or_bump_map(data, params[6], &data->set.obj[*i].form.cy.texture, &data->set.obj[*i].form.cy.bump_map);
	if (nbr_params == 8)
		parse_texture_or_bump_map(data, params[7], &data->set.obj[*i].form.cy.texture, &data->set.obj[*i].form.cy.bump_map);
	data->set.obj[*i].type = CYLINDER;
	parse_coords(&data->set.obj[*i].form.cy.coords, params[1], data);
	parse_normalized_vector(&data->set.obj[*i].form.cy.norm, params[2], data);
	data->set.obj[*i].form.cy.diameter = ft_atof(params[3]);
	data->set.obj[*i].form.cy.radius = data->set.obj[*i].form.cy.diameter / 2.0;
	data->set.obj[*i].form.cy.height = ft_atof(params[4]);
	parse_color(&data->set.obj[*i].form.cy.color, params[5], data);
	create_m_cy(&data->set.obj[*i].form.cy);
	(*i)++;
	free_double_p(params);
}

void	parse_cone(t_data *data, char **line, int *i)
{
	char	**params;
	int		nbr_params;

	params = ft_split(*line, ' ');
	nbr_params = ft_count_params(params);
	if (nbr_params < 6 || nbr_params > 8)
		error("Invalid number of parameters for cone", data);
	data->set.obj[*i].form.cn.bump_map = NULL;
	data->set.obj[*i].form.cn.texture = NULL;
	if (nbr_params >= 7)
		parse_texture_or_bump_map(data, params[6], &data->set.obj[*i].form.cn.texture, &data->set.obj[*i].form.cn.bump_map);
	if (nbr_params == 8)
		parse_texture_or_bump_map(data, params[7], &data->set.obj[*i].form.cn.texture, &data->set.obj[*i].form.cn.bump_map);
	data->set.obj[*i].type = CONE;
	parse_coords(&data->set.obj[*i].form.cn.coords, params[1], data);
	parse_normalized_vector(&data->set.obj[*i].form.cn.norm, params[2], data);
	data->set.obj[*i].form.cn.diameter = ft_atof(params[3]);
	data->set.obj[*i].form.cn.height = ft_atof(params[4]);
	data->set.obj[*i].form.cn.radius = data->set.obj[*i].form.cn.diameter / 2.0;
	parse_color(&data->set.obj[*i].form.cn.color, params[5], data);
	data->set.obj[*i].form.cn.angle
		= tanf(atanf(data->set.obj[*i].form.cn.radius
				/ data->set.obj[*i].form.cn.height))
		* tanf(atanf(data->set.obj[*i].form.cn.radius
				/ data->set.obj[*i].form.cn.height));
	data->set.obj[*i].form.cn.tangle = atan(data->set.obj[*i].form.cn.radius
			/ data->set.obj[*i].form.cn.height);
	create_m_cn(&data->set.obj[*i].form.cn);
	(*i)++;
	free_double_p(params);
}
