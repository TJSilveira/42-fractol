#include "../includes/fractol.h"

void	update_pixel(t_image *img)
{
	t_pixel		p;
	t_coor		c;
	int			w;
	int			i;

	p.x = 0;
	w = img->line_len / 4;
	while (p.x < w)
	{
		p.y = 0;
		while (p.y < img->height)
		{
			init_c(&c, p, *img, w);
			i = fractal_choice(c, c, img);
			if (i == img->iter)
				p.clr = 0xFF000000;
			else
				p.clr = add_red(0x0000FF00, i, img->iter);
			my_mlx_pixel_put(img, p.x, p.y, p.clr);
			p.y += 1;
		}
		p.x += 1;
	}
}

void	init_img(t_engine *e)
{
	e->img.height = 800;
	e->img.width = 1200;
	e->img.img = mlx_new_image(e->mlx, e->img.width, e->img.height);
	e->img.addr = mlx_get_data_addr(e->img.img, &e->img.pix_bits, &e->img.line_len, &e->img.endian);
	e->img.top_left.x = -2.0 * e->img.width / e->img.height;
	e->img.top_left.y = 2;
	e->img.bot_right.x = 2.0 * e->img.width / e->img.height;
	e->img.bot_right.y = -2;
	zoom_manager(e);
}

void	fractal_option(t_engine *e, char *argv[], int argc)
{
	if (ft_strcmp(argv[1], "mandelbrot") == 0 && argc == 2)
		e->img.fractal_type = MANDELBROT;
	else if (ft_strcmp(argv[1], "julia") == 0)
	{
		e->img.fractal_type = JULIA;
		update_c_julia(e, -0.4, 0.6);
		if (argc == 3 && ft_strcmp(argv[2], "1") == 0)
			update_c_julia(e, -0.8, 0.156);
		else if (argc == 3 && ft_strcmp(argv[2], "2") == 0)
			update_c_julia(e, 0.285, 0.01);
	}
	else if (ft_strcmp(argv[1], "tricorn") == 0 && argc == 2)
		e->img.fractal_type = TRICORN;
	else
	{
		ft_putstr_fd("Error: Option not available.\n", 2);
		ft_putstr_fd("Type \'./bin/fractol\' to see options\n", 2);
		exit(EXIT_SUCCESS);
	}
}

void	init_engine(t_engine *e, char *argv[], int argc)
{
	char	*header;

	header = "\"E foi o Éder que os comeu\" - Luís Vaz de Camões";
	e->mlx = mlx_init();
	e->window = mlx_new_window(e->mlx, 1200, 800, header);
	init_img(e);
	update_pixel(&e->img);
	fractal_option(e, argv, argc);
}

int	main(int argc, char *argv[])
{
	t_engine	eng;

	if (argc == 1)
		show_help();
	init_engine(&eng, argv, argc);
	mlx_put_image_to_window(eng.mlx, eng.window, eng.img.img, 0, 0);
	mlx_mouse_hook(eng.window, mouse_wheel, &eng);
	mlx_key_hook(eng.window, key_fig, &eng);
	mlx_expose_hook(eng.window, resize_window, &eng);
	mlx_hook(eng.window, 17, 0L, close_win, &eng);
	mlx_loop(eng.mlx);
	return (0);
}
