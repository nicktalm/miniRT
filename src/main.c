/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:24:36 by ntalmon           #+#    #+#             */
/*   Updated: 2024/08/30 12:33:00 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		error("Wrong number of arguments");
	else
		open_file(argv[1], &data);
	return (0);
}
