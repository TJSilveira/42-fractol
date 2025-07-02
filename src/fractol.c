/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilveir <tsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:21:59 by tsilveir          #+#    #+#             */
/*   Updated: 2025/06/27 13:22:00 by tsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
				p.clr = add_color_gradient(*img, i);
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
	if (!e->img.img)
	{
		ft_putstr_fd("Error: Failed to create image\n", 2);
		cleanup_engine(e);
		exit(EXIT_FAILURE);
	}
	e->img.addr = mlx_get_data_addr(e->img.img, &e->img.pix_bits,
			&e->img.line_len, &e->img.endian);
	e->img.top_left.x = -2.0 * e->img.width / e->img.height;
	e->img.top_left.y = 2;
	e->img.bot_right.x = 2.0 * e->img.width / e->img.height;
	e->img.bot_right.y = -2;
	e->img.main_color = 0x0000FF00;
	e->img.secundary_color = 0x00FF0000;
	zoom_manager(e);
}

void	fractal_option(t_engine *e, char *argv[], int argc)
{
	if (ft_strncmp(argv[1], "mandelbrot", 10) == 0 && argc == 2)
		e->img.fractal_type = MANDELBROT;
	else if (ft_strncmp(argv[1], "julia", 5) == 0)
	{
		e->img.fractal_type = JULIA;
		if (argc == 2)
			update_c_julia(e, -0.4, 0.6);
		else if (argc == 3 && ft_strncmp(argv[2], "1", 1) == 0
			&& ft_strlen(argv[2]) == 1)
			update_c_julia(e, -0.8, 0.156);
		else if (argc == 3 && ft_strncmp(argv[2], "2", 1) == 0
			&& ft_strlen(argv[2]) == 1)
			update_c_julia(e, 0.285, 0.01);
		else
			error_handler(e);
	}
	else if (ft_strncmp(argv[1], "tricorn", 7) == 0 && argc == 2)
		e->img.fractal_type = TRICORN;
	else
		error_handler(e);
}

void	init_engine(t_engine *e, char *argv[], int argc)
{
	char	*header;

	header = "\"E foi o Eder que os comeu\" - Luis Vaz de Camoes, 1986";
	e->mlx = mlx_init();
	e->window = mlx_new_window(e->mlx, 1200, 800, header);
	fractal_option(e, argv, argc);
	init_img(e);
	update_pixel(&e->img);
}

int	main(int argc, char *argv[])
{
	t_engine	eng;

	if (argc == 1)
		show_help();
	ft_memset(&eng, 0, sizeof(t_engine));
	init_engine(&eng, argv, argc);
	mlx_put_image_to_window(eng.mlx, eng.window, eng.img.img, 0, 0);
	mlx_mouse_hook(eng.window, mouse_wheel, &eng);
	mlx_key_hook(eng.window, key_fig, &eng);
	mlx_hook(eng.window, 17, 0L, close_win, &eng);
	mlx_loop(eng.mlx);
	cleanup_engine(&eng);
	return (0);
}
