/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsilveir <tsilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:23:01 by tsilveir          #+#    #+#             */
/*   Updated: 2025/06/27 13:23:19 by tsilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "../libft/libft.h"
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <X11/X.h>
# define MANDELBROT 0
# define JULIA 1
# define TRICORN 2
# define KEY_ESC 65307

typedef struct s_pixel
{
	int				x;
	int				y;
	unsigned int	clr;
}	t_pixel;

typedef struct s_coor
{
	double	x;
	double	y;
}	t_coor;

typedef struct s_image
{
	void			*img;
	char			*addr;
	int				pix_bits;
	int				line_len;
	int				height;
	int				width;
	int				endian;
	int				iter;
	int				fractal_type;
	unsigned int	main_color;
	unsigned int	secundary_color;
	t_coor			c_julia;
	t_coor			top_left;
	t_coor			bot_right;
}	t_image;

typedef struct s_engine
{
	void	*mlx;
	void	*window;
	t_image	img;
}	t_engine;

/* fractol.c */
void			update_pixel(t_image *img);
void			init_img(t_engine *e);
void			fractal_option(t_engine *e, char *argv[], int argc);
void			init_engine(t_engine *e, char *argv[], int argc);

/* fractal_calc.c */
int				mandelbrot_calc(t_coor zn, t_coor c, int iter);
int				julia_calc(t_coor zn, t_coor c, int iter);
int				tricorn_calc(t_coor zn, t_coor c, int iter);
int				fractal_choice(t_coor zn, t_coor c, t_image *img);
void			update_c_julia(t_engine *e, double x, double y);

/* events.c */
int				close_win(t_engine *engine);
void			zoom_manager(t_engine *e);
int				mouse_wheel(int key, int x, int y, t_engine *e);
void			zoom_in_out(int key, double x_len, double y_len, t_engine *e);
int				key_fig(int key, t_engine *e);

/* utils.c */
void			show_help(void);
void			my_mlx_pixel_put(t_image *data, int x, int y, int color);
void			init_c(t_coor *c, t_pixel p, t_image img, int w);

/* utils_color.c */
unsigned int	add_color_gradient(t_image img, int i);
void			update_color_scheme(t_engine *e, int main, int secundary);
void			cleanup_image(t_engine *e);
void			cleanup_engine(t_engine *e);

#endif
