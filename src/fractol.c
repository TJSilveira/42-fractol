#include "../includes/fractol.h"

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->pix_bits / 8));
	*(unsigned int*)dst = color;
}

int	mandelbrot_calc(t_coor zn, t_coor c, int iter)
{
	int		i;
	double	temp_x;
	
	i = 1;
	zn.x = 0;
	zn.y = 0;
	while (i < iter)
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

int	julia_calc(t_coor zn, t_coor c, int iter)
{
	int		i;
	double	temp_x;
	
	i = 1;
	while (i < iter)
	{
		temp_x = zn.x * zn.x - zn.y * zn.y + c.x;
		zn.y = 2. * zn.x * zn.y + c.y;
		zn.x = temp_x;
		if (pow(zn.x,2) + pow(zn.y, 2) > 20)
			break;
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

int	fractal_choice(t_coor zn, t_coor c, t_image *img)
{
	if (img->fractal_type == MANDELBROT)
		return (mandelbrot_calc(zn, c, img->iter));
	else if (img->fractal_type == JULIA)
		return (julia_calc(zn, img->c_julia, img->iter));
	return (0);
}

void	init_c(t_coor *c, t_pixel p, t_image img, int w)
{
	c->y = img.top_left.y + (double)p.y / (double)img.height * \
			(img.bot_right.y - img.top_left.y);
	c->x = img.top_left.x + (double)p.x / (double)w * \
			(img.bot_right.x - img.top_left.x);
}

void	update_pixel(t_image *img)
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

void	show_help(void)
{
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(" +--------------- Let me help you! --------------+\n", 1);
	ft_putstr_fd(" |                                               |\n", 1);
	ft_putstr_fd(" | Usage: ./bin/fractol [mandelbrot / julia /    |\n", 1);
	ft_putstr_fd(" |                      burning_ship /           |\n", 1);
	ft_putstr_fd(" |                      tricorn / mandelbox /    |\n", 1);
	ft_putstr_fd(" |                      celtic_mandelbar]        |\n", 1);
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

void	fractal_option(t_engine *e, char *argv[], int argc)
{
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
		e->img.fractal_type = MANDELBROT;
	else if (ft_strcmp(argv[1], "julia") == 0)
	{
		e->img.fractal_type = JULIA;
		e->img.c_julia.x = -0.4;
		e->img.c_julia.y = 0.6;
		if (argc == 3 && ft_strcmp(argv[2], "1") == 0)
		{
			e->img.c_julia.x = -0.8;
			e->img.c_julia.y = 0.156;
		}
		else if (argc == 3 && ft_strcmp(argv[2], "2") == 0)
		{
			e->img.c_julia.x = 0.285;
			e->img.c_julia.y = 0.01;
		}
	}
	else
	{
		ft_putstr_fd("Error: Option not available.\n", 2);
		ft_putstr_fd("Type \'./bin/fractol\' to see options\n", 2);
		exit(EXIT_SUCCESS);
	}
}

void	init_engine(t_engine *e, char *argv[], int argc)
{
	char *header;

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
	mlx_expose_hook(eng.window, resize_window, &eng);
	mlx_hook(eng.window, 17, 0L, close_win, &eng);
	mlx_loop(eng.mlx);
	return (0);
}

