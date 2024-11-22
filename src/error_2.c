/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 19:39:37 by ntalmon           #+#    #+#             */
/*   Updated: 2024/11/22 20:03:20 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	check_bump_texture(xpm_t *bump_map, xpm_t *texture)
{
	if (bump_map)
		mlx_delete_xpm42(bump_map);
	if (texture)
		mlx_delete_xpm42(texture);
}
