#include "../includes/fractol.h"

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->pix_bits / 8));
	*(unsigned int*)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int	close_win(t_engine engine)
{
	mlx_destroy_window(engine.mlx,engine.window);
	return (0);
}

void	next_coor(t_coor *total, t_coor c)
{
	double	temp_x;
	
	temp_x = total->x * total->x - total->y * total->y + c.x;
	total->y = 2. * total->x * total->y + c.y;
	total->x = temp_x;
}

int	fractal_calc(t_coor c)
{
	int		i;
	t_coor	total;

	i = 1;
	total.x = 0;
	total.y = 0;
	while (i < 50)
	{
		next_coor(&total, c);
		if (pow(total.x,2) + pow(total.y, 2) > 20000)
		{
			break;
		}
		i++;
	}
	// printf("x:%f y:%f %i\n", total.x, total.y, i);
	return (i);
}

void	update_pixel(t_image *img/*, t_frac f*/)
{
	t_pixel		p;
	t_coor		c;
	int			w;

	p.x = 0;
	w = img->line_len/4;
	while (p.x < w) 
	{
		p.y = 0;
		while (p.y < img->height)
		{
			c.y = img->top_left.y + (double)p.y / (double)img->height * (img->bot_right.y - img->top_left.y);
			c.x = img->top_left.x + (double)p.x / (double)w * (img->bot_right.x - img->top_left.x);
			// printf("x:%f y:%f\n", c.x, c.y);
			if (fractal_calc(c) == 50)
				p.clr = 0xFF00000;
			else
				p.clr = 0x00FFFF00;
			my_mlx_pixel_put(img, p.x, p.y, p.clr);
			p.y += 1;
		}
		p.x += 1;
	}
}

void	init_img(t_image *img, t_engine *engine)
{
	img->height = 800;
	img->img = mlx_new_image(engine->mlx, 1200, img->height);
	img->addr = mlx_get_data_addr(img->img, &img->pix_bits, &img->line_len, &img->endian);
	img->top_left.x = -3;
	img->top_left.y = 1.5;
	img->bot_right.x = 1;
	img->bot_right.y = -1.5;
}

int	main(void)
{
	t_engine	engine;
	t_image		img;

	engine.mlx = mlx_init();
	engine.window = mlx_new_window(engine.mlx, 1200, 800, "\"E foi o Éder que os comeu\" - Luís Vaz de Camões");
	init_img(&img, &engine);
	
	update_pixel(&img);

	mlx_put_image_to_window(engine.mlx, engine.window, img.img, 0, 0);
	mlx_hook(engine.window, 2, 1L<<0, close_win, &engine);
	mlx_loop(engine.mlx);
}

