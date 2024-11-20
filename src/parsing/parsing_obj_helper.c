/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_obj_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:33:40 by ntalmon           #+#    #+#             */
/*   Updated: 2024/11/19 12:36:01 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	parse_txt_bump(t_data *data, char *param,
			xpm_t **texture, xpm_t **bump_map)
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

void	parse_sp_specific(t_data *data, char **params, int *i)
{
	data->set.obj[*i].form.sp.texture = NULL;
	data->set.obj[*i].form.sp.bump_map = NULL;
	if (ft_count_params(params) >= 5)
		parse_txt_bump(data, params[4], &data->set.obj[*i].form.sp.texture,
			&data->set.obj[*i].form.sp.bump_map);
	if (ft_count_params(params) == 6)
		parse_txt_bump(data, params[5], &data->set.obj[*i].form.sp.texture,
			&data->set.obj[*i].form.sp.bump_map);
	data->set.obj[*i].type = SPHERE;
	parse_coords(&data->set.obj[*i].form.sp.coords, params[1], data);
	data->set.obj[*i].form.sp.diameter = ft_atof(params[2]);
	data->set.obj[*i].form.sp.radius = data->set.obj[*i].form.sp.diameter / 2.0;
	parse_color(&data->set.obj[*i].form.sp.color, params[3], data);
	create_m_sp(&data->set.obj[*i].form.sp);
}

void	parse_pl_specific(t_data *data, char **params, int *i)
{
	if (ft_count_params(params) >= 5)
	{
		if (ft_isdigit(params[4][0]))
			parse_surface(&data->set.obj[*i].form.pl, params[4], data);
		else
			parse_txt_bump(data, params[4], &data->set.obj[*i].form.pl.texture,
				&data->set.obj[*i].form.pl.bump_map);
	}
	if (ft_count_params(params) >= 6)
	{
		if (ft_isdigit(params[5][0]))
			parse_surface(&data->set.obj[*i].form.pl, params[5], data);
		else
			parse_txt_bump(data, params[5], &data->set.obj[*i].form.pl.texture,
				&data->set.obj[*i].form.pl.bump_map);
	}
	if (ft_count_params(params) == 7 && ft_isdigit(params[6][0]))
		parse_surface(&data->set.obj[*i].form.pl, params[6], data);
	data->set.obj[*i].type = PLANE;
	parse_coords(&data->set.obj[*i].form.pl.coords, params[1], data);
	parse_normalized_vector(&data->set.obj[*i].form.pl.norm, params[2], data);
	parse_color(&data->set.obj[*i].form.pl.color, params[3], data);
	create_m_pl(&data->set.obj[*i].form.pl);
}

void	parse_cy_specific(t_data *data, char **params, int *i)
{
	data->set.obj[*i].form.cy.bump_map = NULL;
	data->set.obj[*i].form.cy.texture = NULL;
	if (ft_count_params(params) >= 7)
		parse_txt_bump(data, params[6], &data->set.obj[*i].form.cy.texture,
			&data->set.obj[*i].form.cy.bump_map);
	if (ft_count_params(params) == 8)
		parse_txt_bump(data, params[7], &data->set.obj[*i].form.cy.texture,
			&data->set.obj[*i].form.cy.bump_map);
	data->set.obj[*i].type = CYLINDER;
	parse_coords(&data->set.obj[*i].form.cy.coords, params[1], data);
	parse_normalized_vector(&data->set.obj[*i].form.cy.norm, params[2], data);
	data->set.obj[*i].form.cy.diameter = ft_atof(params[3]);
	data->set.obj[*i].form.cy.radius = data->set.obj[*i].form.cy.diameter / 2.0;
	data->set.obj[*i].form.cy.height = ft_atof(params[4]);
	parse_color(&data->set.obj[*i].form.cy.color, params[5], data);
	create_m_cy(&data->set.obj[*i].form.cy);
}

void	parse_cone_specific(t_data *data, char **params, int *i)
{
	data->set.obj[*i].form.cn.bump_map = NULL;
	data->set.obj[*i].form.cn.texture = NULL;
	if (ft_count_params(params) >= 7)
		parse_txt_bump(data, params[6], &data->set.obj[*i].form.cn.texture,
			&data->set.obj[*i].form.cn.bump_map);
	if (ft_count_params(params) == 8)
		parse_txt_bump(data, params[7], &data->set.obj[*i].form.cn.texture,
			&data->set.obj[*i].form.cn.bump_map);
	data->set.obj[*i].type = CONE;
	parse_coords(&data->set.obj[*i].form.cn.coords, params[1], data);
	parse_normalized_vector(&data->set.obj[*i].form.cn.norm, params[2], data);
	data->set.obj[*i].form.cn.height = ft_atof(params[3]);
	data->set.obj[*i].form.cn.diameter = ft_atof(params[4]);
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
}
