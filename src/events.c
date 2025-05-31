#include "../includes/fractol.h"

int	close_win(t_engine *engine)
{
	mlx_destroy_window(engine->mlx,engine->window);
	exit(0);
}

void	zoom_manager(t_engine *e)
{
	double	dist;
	double	x_len;
	double	y_len;

	x_len = e->img.bot_right.x - e->img.top_left.x;
	y_len = e->img.top_left.y - e->img.bot_right.y;
	dist = hypot(x_len, y_len);
	if (dist > 5.0)
		e->img.iter = 90;
	else if (dist > 3.0)
		e->img.iter = 100;
	else if (dist > 1.0)
		e->img.iter = 200;
	else if (dist > 0.2)
		e->img.iter = 400;
	else if (dist > 0.05)
		e->img.iter = 800;
	else if (dist > 0.005)
		e->img.iter = 1600;
	else if (dist > 0.0001)
		e->img.iter = 3200;
	else
		e->img.iter = 6400;
}

int	mouse_wheel(int key, int x, int y, t_engine *e)
{
	double	x_len;
	double	y_len;
	double	x_mou;
	double	y_mou;

	x_len = e->img.bot_right.x - e->img.top_left.x;
	y_len = e->img.top_left.y - e->img.bot_right.y;
	x_mou = ((double)x / (double)(e->img.line_len / 4) - 0.5) * x_len;
	y_mou = (1. - (double)y / (double)e->img.height - 0.5) * y_len;

	/* Move the display to center of the mouse */
	e->img.top_left.x += x_mou;
	e->img.top_left.y += y_mou;
	e->img.bot_right.x += x_mou;
	e->img.bot_right.y += y_mou;
	zoom_manager(e);
	if (key == 5)
	{
		e->img.top_left.x -= x_len * 0.3 / 2.0;
		e->img.top_left.y += y_len * 0.3 / 2.0;
		e->img.bot_right.x += x_len * 0.3 / 2.0;
		e->img.bot_right.y -= y_len * 0.3 / 2.0;
	}
	if (key == 4)
	{
		e->img.top_left.x += x_len * 0.3 / 2.0;
		e->img.top_left.y -= y_len * 0.3 / 2.0;
		e->img.bot_right.x -= x_len * 0.3 / 2.0;
		e->img.bot_right.y += y_len * 0.3 / 2.0;
	}
	mlx_put_image_to_window(e->mlx, e->window, e->img.img, 0, 0);
	update_pixel(&e->img);
	return (0);
}

int	resize_window(t_engine *e)
{
	init_img(e);
	update_pixel(&e->img);
	mlx_put_image_to_window(e->mlx, e->window, e->img.img, 0, 0);
	return (0);
}