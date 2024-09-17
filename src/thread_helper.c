/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:22:48 by lbohm             #+#    #+#             */
/*   Updated: 2024/09/17 16:28:22 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	sp_count(t_data *data)
{
	int	ret;

	pthread_mutex_lock(&data->count);
	ret = data->set.sp_count;
	pthread_mutex_unlock(&data->count);
	return (ret);
}
