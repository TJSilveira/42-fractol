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
	ft_putstr_fd(" | Use arrows to move                            |\n", 1);
	ft_putstr_fd(" | Click on a point to recenter to your mouse    |\n", 1);
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

void	zoom_reset(t_engine *e)
{
	e->img.top_left.x = -2.0 * e->img.width / e->img.height;
	e->img.top_left.y = 2;
	e->img.bot_right.x = 2.0 * e->img.width / e->img.height;
	e->img.bot_right.y = -2;
	zoom_manager(e);
	mlx_put_image_to_window(e->mlx, e->window, e->img.img, 0, 0);
	update_pixel(&e->img);
}

void	arrow_move(t_engine *e, double updown, double leftrigth)
{
	double	x_len;
	double	y_len;

	x_len = e->img.bot_right.x - e->img.top_left.x;
	y_len = e->img.top_left.y - e->img.bot_right.y;
	e->img.top_left.x += leftrigth * x_len * 0.3 / 2.0;
	e->img.bot_right.x += leftrigth * x_len * 0.3 / 2.0;
	e->img.top_left.y += updown * y_len * 0.3 / 2.0;
	e->img.bot_right.y += updown * y_len * 0.3 / 2.0;
	mlx_put_image_to_window(e->mlx, e->window, e->img.img, 0, 0);
	update_pixel(&e->img);
}
