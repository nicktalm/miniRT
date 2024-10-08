/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:24:36 by ntalmon           #+#    #+#             */
/*   Updated: 2024/10/08 15:31:11 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

// void	print_obj(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	printf("Lights\n");
// 	while (i < data->set.light_count)
// 	{
// 		printf("Coords: %f %f %f\n", data->set.light[i].coords.x, data->set.light[i].coords.y, data->set.light[i].coords.z);
// 		printf("Brightness: %f\n", data->set.light[i].brightness);
// 		printf("Color: %f %f %f\n", data->set.light[i].color.x, data->set.light[i].color.y, data->set.light[i].color.z);
// 		i++;
// 		printf("\n");
// 	}
// 	i = 0;
// 	printf("Camera\n");
// 	printf("Coords: %f %f %f\n", data->set.cam.coords.x, data->set.cam.coords.y, data->set.cam.coords.z);
// 	printf("Direction: %f %f %f\n", data->set.cam.direction.x, data->set.cam.direction.y, data->set.cam.direction.z);
// 	printf("FOV: %f\n", data->set.cam.fov);
// 	printf("\n");
// 	printf("Ambient\n");
// 	printf("Ratio: %f\n", data->set.ambient.ratio);
// 	printf("Color: %f %f %f\n", data->set.ambient.color.x, data->set.ambient.color.y, data->set.ambient.color.z);
// 	printf("\n");
// 	while (i < data->set.obj_count)
// 	{
// 		if (data->set.obj[i].type == SPHERE)
// 		{
// 			printf("Sphere\n");
// 			printf("Coords: %f %f %f\n", data->set.obj[i].form.sp.coords.x, data->set.obj[i].form.sp.coords.y, data->set.obj[i].form.sp.coords.z);
// 			printf("Diameter: %f\n", data->set.obj[i].form.sp.diameter);
// 			printf("Radius: %f\n", data->set.obj[i].form.sp.radius);
// 			printf("Color: %f %f %f\n", data->set.obj[i].form.sp.color.x, data->set.obj[i].form.sp.color.y, data->set.obj[i].form.sp.color.z);
// 			printf("Material: %f\n", data->set.obj[i].form.sp.material);
// 		}
// 		else if (data->set.obj[i].type == PLANE)
// 		{
// 			printf("Plane\n");
// 			printf("Coords: %f %f %f\n", data->set.obj[i].form.pl.coords.x, data->set.obj[i].form.pl.coords.y, data->set.obj[i].form.pl.coords.z);
// 			printf("Normalized: %f %f %f\n", data->set.obj[i].form.pl.norm.x, data->set.obj[i].form.pl.norm.y, data->set.obj[i].form.pl.norm.z);
// 			printf("Color: %f %f %f\n", data->set.obj[i].form.pl.color.x, data->set.obj[i].form.pl.color.y, data->set.obj[i].form.pl.color.z);
// 			printf("Material: %f\n", data->set.obj[i].form.pl.material);
// 			printf("Length: %f\n", data->set.obj[i].form.pl.length);
// 			printf("Width: %f\n", data->set.obj[i].form.pl.width);
// 		}
// 		else if (data->set.obj[i].type == CYLINDER)
// 		{
// 			printf("Cylinder\n");
// 			printf("Coords: %f %f %f\n", data->set.obj[i].form.cy.coords.x, data->set.obj[i].form.cy.coords.y, data->set.obj[i].form.cy.coords.z);
// 			printf("Normalized: %f %f %f\n", data->set.obj[i].form.cy.norm.x, data->set.obj[i].form.cy.norm.y, data->set.obj[i].form.cy.norm.z);
// 			printf("Diameter: %f\n", data->set.obj[i].form.cy.diameter);
// 			printf("Radius: %f\n", data->set.obj[i].form.cy.radius);
// 			printf("Height: %f\n", data->set.obj[i].form.cy.height);
// 			printf("Color: %f %f %f\n", data->set.obj[i].form.cy.color.x, data->set.obj[i].form.cy.color.y, data->set.obj[i].form.cy.color.z);
// 			printf("Material: %f\n", data->set.obj[i].form.cy.material);
// 		}
// 		i++;
// 		printf("\n");
// 	}
// }

int	main(int argc, char **argv)
{
	t_data	data;

	init_data(&data, argc, argv);
	init_mlx(&data);
	// print_obj(&data);
	if (data.name)
		create_img(&data);
	else
		creat_img_multi(&data);
	mlx_image_to_window(data.window, data.img, 0, 0);
	// mlx_loop_hook(data.window, hook, &data);
	mlx_loop(data.window);
	mlx_delete_image(data.window, data.img);
	mlx_terminate(data.window);
	free_all(&data);
	return (0);
}
