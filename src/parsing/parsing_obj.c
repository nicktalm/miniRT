/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:52:19 by ntalmon           #+#    #+#             */
/*   Updated: 2024/11/20 10:37:16 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	parse_common_params(t_data *data, char **params, int *i,
			void (*parse_specific_params)(t_data *, char **, int *))
{
	parse_specific_params(data, params, i);
	(*i)++;
	free_double_p(params);
}

void	parse_sphere(t_data *data, char **line, int *i)
{
	char	**params;
	int		nbr_params;

	params = ft_split(*line, ' ');
	nbr_params = ft_count_params(params);
	data->set.obj[*i].form.sp.bump_map = NULL;
	data->set.obj[*i].form.sp.texture = NULL;
	if (nbr_params < 4 || nbr_params > 6)
		error("Invalid number of parameters", data);
	parse_common_params(data, params, i, parse_sp_specific);
}

void	parse_plane(t_data *data, char **line, int *i)
{
	char	**params;
	int		nbr_params;

	params = ft_split(*line, ' ');
	nbr_params = ft_count_params(params);
	data->set.obj[*i].form.pl.bump_map = NULL;
	data->set.obj[*i].form.pl.texture = NULL;
	data->set.obj[*i].form.pl.length = 0.0;
	data->set.obj[*i].form.pl.width = 0.0;
	if (nbr_params < 4 || nbr_params > 7)
		error("Invalid number of parameters", data);
	parse_common_params(data, params, i, parse_pl_specific);
}

void	parse_cylinder(t_data *data, char **line, int *i)
{
	char	**params;
	int		nbr_params;

	params = ft_split(*line, ' ');
	nbr_params = ft_count_params(params);
	data->set.obj[*i].form.cy.bump_map = NULL;
	data->set.obj[*i].form.cy.texture = NULL;
	if (nbr_params < 6 || nbr_params > 8)
		error("Invalid number of parameters", data);
	parse_common_params(data, params, i, parse_cy_specific);
}

void	parse_cone(t_data *data, char **line, int *i)
{
	char	**params;
	int		nbr_params;

	params = ft_split(*line, ' ');
	nbr_params = ft_count_params(params);
	data->set.obj[*i].form.cn.bump_map = NULL;
	data->set.obj[*i].form.cn.texture = NULL;
	if (nbr_params < 6 || nbr_params > 8)
		error("Invalid number of parameters", data);
	parse_common_params(data, params, i, parse_cone_specific);
}
