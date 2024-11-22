/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:16:32 by ntalmon           #+#    #+#             */
/*   Updated: 2024/11/22 16:39:37 by ntalmon          ###   ########.fr       */
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
	{
		free_double_p(&texture);
		error("load xpm file", data);
	}
}

void	parse_bump_map(t_data *data, char *bump_map, xpm_t *obj)
{
	bump_map += 9;
	obj = mlx_load_xpm42(bump_map);
	if (!obj)
	{
		free_double_p(&bump_map);
		error("load xpm file", data);
	}
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
