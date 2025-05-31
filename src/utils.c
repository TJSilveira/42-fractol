#include "../includes/fractol.h"

int	resize_window(t_engine *e)
{
	init_img(e);
	update_pixel(&e->img);
	mlx_put_image_to_window(e->mlx, e->window, e->img.img, 0, 0);
	return (0);
}

int	add_red(int clr, int i, int total_i)
{
	clr = clr & 0xFF00FFFF;
	clr += 0x00FF0000 * ((double)i / (double)total_i - (double)i);
	return (clr);
}

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
	ft_putstr_fd(" |------------------- KEYBOARD ------------------|\n", 1);
	ft_putstr_fd(" |                                               |\n", 1);
	ft_putstr_fd(" | Press ESC to close the window                 |\n", 1);
	ft_putstr_fd(" | Press one of [1-6] to move to another fractal |\n", 1);
	ft_putstr_fd(" | Press one of [Q-Y] keys to change the color   |\n", 1);
	ft_putstr_fd(" | Press one of [A-H] keys to change the color   |\n", 1);
	ft_putstr_fd(" | Use mouse scroll to zoom in and out           |\n", 1);
	ft_putstr_fd(" | Press the arrow keys to change the viewpoint  |\n", 1);
	ft_putstr_fd(" | Press L to lock Julia's fractal               |\n", 1);
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
	c->y = img.top_left.y + (double)p.y / (double)img.height * (img.bot_right.y - img.top_left.y);
	c->x = img.top_left.x + (double)p.x / (double)w * (img.bot_right.x - img.top_left.x);
}
