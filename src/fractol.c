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

int		in_scope(t_coor *c)
{
	if (pow(c->x,2) + pow(c->y, 2) > 2)
	{
		return (1);
	}
	return (0);
}

void	fractal_calc(t_coor *c)
{
	int	i;
	// double	total;

	i = 0;
	while (i < 20)
	{
		/* code */
		i++;
	}
	c->x = 0;
}

void	update_pixel(t_image *img/*, t_frac f*/)
{
	t_pixel		p;
	t_coor		c;

	p.x = 0;
	while (p.x < img->line_len/4) 
	{
		p.y = 0;
		while (p.y < img->height)
		{
			p.clr = 0x00FFFF00;
			my_mlx_pixel_put(img, p.x, p.y, p.clr);
			c.y = p.y / img->height * (img->top_left.y - img->bot_right.y);
			c.x = p.x / img->height * (img->top_left.x - img->bot_right.x);


			/*if (pow(p.x-200,2) + pow(p.y-200, 2) <= 8000 && pow(p.x-200,2) + pow(p.y-200, 2) >= 3600)
			{
				p.clr = 0x0000FF00;
				my_mlx_pixel_put(img, p.x, p.y, p.clr);
			}*/
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

