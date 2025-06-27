/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilveir <tsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:22:06 by tsilveir          #+#    #+#             */
/*   Updated: 2025/06/27 13:22:07 by tsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	show_help(void)
{
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(" +--------------- Let me help you! --------------+\n", 1);
	ft_putstr_fd(" |                                               |\n", 1);
	ft_putstr_fd(" | Usage: ./bin/fractol [mandelbrot / julia /    |\n", 1);
	ft_putstr_fd(" |                      tricorn]                 |\n", 1);
	ft_putstr_fd(" |                                               |\n", 1);
	ft_putstr_fd(" | e.g: ./bin/fractol mandelbrot                 |\n", 1);
	ft_putstr_fd(" |                                               |\n", 1);
	ft_putstr_fd(" | For Julia options, use                        |\n", 1);
	ft_putstr_fd(" |     ./bin/fractol/julia [1-2]                 |\n", 1);
	ft_putstr_fd(" |                                               |\n", 1);
	ft_putstr_fd(" |------------------- KEYBOARD ------------------|\n", 1);
	ft_putstr_fd(" |                                               |\n", 1);
	ft_putstr_fd(" | Press ESC to close the window                 |\n", 1);
	ft_putstr_fd(" | Press one of [q-r] keys to change the color   |\n", 1);
	ft_putstr_fd(" | Use mouse scroll to zoom in and out           |\n", 1);
	ft_putstr_fd(" | Press Zero to reset the fractal               |\n", 1);
	ft_putstr_fd(" +-----------------------------------------------+\n", 1);
	ft_putstr_fd("\n", 1);
	exit(EXIT_SUCCESS);
}

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->pix_bits / 8));
	*(unsigned int *)dst = color;
}

void	init_c(t_coor *c, t_pixel p, t_image img, int w)
{
	c->y = img.top_left.y + (double)p.y / (double)img.height
		* (img.bot_right.y - img.top_left.y);
	c->x = img.top_left.x + (double)p.x / (double)w
		* (img.bot_right.x - img.top_left.x);
}
