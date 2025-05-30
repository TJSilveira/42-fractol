#include "../includes/fractol.h"

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->pix_bits / 8));
	*(unsigned int*)dst = color;
}

int	close_win(t_engine engine)
{
	mlx_destroy_window(engine.mlx,engine.window);
	return (0);
}

int	mandelbrot_calc(t_coor zn, t_coor c)
{
	int		i;
	double	temp_x;
	
	i = 1;
	zn.x = 0;
	zn.y = 0;
	while (i < 50)
	{
		temp_x = zn.x * zn.x - zn.y * zn.y + c.x;
		zn.y = 2. * zn.x * zn.y + c.y;
		zn.x = temp_x;
		if (pow(zn.x,2) + pow(zn.y, 2) > 20)
		{
			break;
		}
		i++;
	}
	return (i);
}

int	julia_calc(t_coor zn, t_coor c)
{
	int		i;
	double	temp_x;
	
	i = 1;
	c.x = -0.4;
	c.y = 0.6;
	while (i < 50)
	{
		temp_x = zn.x * zn.x - zn.y * zn.y + c.x;
		zn.y = 2. * zn.x * zn.y + c.y;
		zn.x = temp_x;
		if (pow(zn.x,2) + pow(zn.y, 2) > 20)
		{
			break;
		}
		i++;
	}
	return (i);
}

int	add_red(int clr, int i, int total_i)
{
	clr = clr & 0xFF00FFFF;
	clr += 0x00FF0000 * ((double)i / (double)total_i - (double)i);
	return(clr);
}

int	fractal_choice(t_coor zn, t_coor c, char * choice)
{
	if (ft_strcmp(choice, "Mandelbrot") == 0)
		return (mandelbrot_calc(zn, c));
	else if (ft_strcmp(choice, "Julia") == 0)
		return (julia_calc(zn, c));

	return (0);
}

void	init_c(t_coor *c, t_pixel p, t_image img, int w)
{
	c->y = img.top_left.y + (double)p.y / (double)img.height * \
			(img.bot_right.y - img.top_left.y);
	c->x = img.top_left.x + (double)p.x / (double)w * \
			(img.bot_right.x - img.top_left.x);
}

void	update_pixel(t_image *img/*, t_frac f*/)
{
	t_pixel		p;
	t_coor		c;
	int			w;
	int			i;

	p.x = 0;
	w = img->line_len/4;
	while (p.x < w) 
	{
		p.y = 0;
		while (p.y < img->height)
		{
			init_c(&c, p, *img, w);
			i = fractal_choice(c, c, "Julia");
			if (i == 50)
				p.clr = 0xFF000000;
			else
				p.clr = add_red(0x0000FF00, i, 50);
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
	img->top_left.y = 2;
	img->bot_right.x = 3;
	img->bot_right.y = -2;
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

