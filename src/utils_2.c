/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilveir <tsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:21:39 by tsilveir          #+#    #+#             */
/*   Updated: 2025/06/27 13:21:41 by tsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	update_color_scheme(t_engine *e, int main, int secundary)
{
	e->img.main_color = main;
	e->img.secundary_color = secundary;
	mlx_put_image_to_window(e->mlx, e->window, e->img.img, 0, 0);
	update_pixel(&e->img);
}

unsigned int	add_color_gradient(t_image img, int i)
{
	unsigned int	mask;

	mask = ~img.secundary_color;
	img.main_color = img.main_color & mask;
	img.main_color += img.secundary_color
		* ((double)i / (double)img.iter - (double)i);
	return (img.main_color);
}

void	cleanup_image(t_engine *e)
{
	if (!e)
		return ;
	if (e->img.img && e->mlx)
	{
		mlx_destroy_image(e->mlx, e->img.img);
		e->img.img = NULL;
	}
}

void	cleanup_engine(t_engine *e)
{
	cleanup_image(e);
	if (e->window)
	{
		mlx_destroy_window(e->mlx, e->window);
		e->window = NULL;
	}
	if (e->mlx)
	{
		mlx_destroy_display(e->mlx);
		free(e->mlx);
		e->mlx = NULL;
	}
}

void	error_handler(t_engine *e)
{
	ft_putstr_fd("Error: Option not available.\n", 2);
	ft_putstr_fd("Type \'./bin/fractol\' to see options\n", 2);
	cleanup_engine(e);
	exit(EXIT_SUCCESS);
}
