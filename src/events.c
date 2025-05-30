#include "../includes/fractol.h"

int	close_win(t_engine *engine)
{
	mlx_destroy_window(engine->mlx,engine->window);
	exit(0);
}

int	mouse_wheel(int key, int x, int y, t_engine *e)
{
	double	dist;
	double	x_len;
	double	y_len;
	double	x_mou;
	double	y_mou;

	x_len = e->img.bot_right.x - e->img.top_left.x;
	y_len = e->img.top_left.y - e->img.bot_right.y;
	x_mou = ((double)x / (double)(e->img.line_len / 4) - 0.5) * x_len;
	y_mou = (1. - (double)y / (double)e->img.height - 0.5) * y_len;
	printf("%f\n", x_mou);
	printf("%f\n", y_mou);

	e->img.top_left.x += x_mou;
	e->img.top_left.y += y_mou;
	e->img.bot_right.x += x_mou;
	e->img.bot_right.y += y_mou;
	dist = hypot(x_len, y_len);
	printf("%f\n", dist);
	if (key == 5)
	{
		e->img.top_left.x -= x_len * 0.3 / 2.0;
		e->img.top_left.y += y_len * 0.3 / 2.0;
		e->img.bot_right.x += x_len * 0.3 / 2.0;
		e->img.bot_right.y -= y_len * 0.3 / 2.0;
		e->img.iter = (double)e->img.iter / 1.3;
		printf("Inside Here\n");
	}
	if (key == 4)
	{
		e->img.top_left.x += x_len * 0.3 / 2.0;
		e->img.top_left.y -= y_len * 0.3 / 2.0;
		e->img.bot_right.x -= x_len * 0.3 / 2.0;
		e->img.bot_right.y += y_len * 0.3 / 2.0;
		e->img.iter = (double)e->img.iter * 1.3;
		printf("Inside Here\n");
	}
	mlx_put_image_to_window(e->mlx, e->window, e->img.img, 0, 0);
	update_pixel(&e->img);
	return (0);
}