#ifndef FRACTOL_H
#define FRACTOL_H
#include "../includes/libft.h"
#include <math.h>
#include <mlx.h>
#define MANDELBROT 0
#define JULIA 1
#define TRICORN 2

typedef	struct s_fractal
{
	/* data */
}	t_frac;

typedef	struct s_pixel
{
	int	x;
	int	y;
	int	clr;
}	t_pixel;

typedef	struct s_coor
{
	double	x;
	double	y;
}	t_coor;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		pix_bits;
	int		line_len;
	int		height;
	int		width;
	int		endian;
	int		iter;
	int		fractal_type;
	t_coor	c_julia;
	t_coor	top_left;
	t_coor	bot_right;
}	t_image;

typedef struct s_engine
{
	void	*mlx;
	void	*window;
	t_image	img;
}	t_engine;

/* fractal.c */
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);
int	mandelbrot_calc(t_coor zn, t_coor c, int iter);
int	julia_calc(t_coor zn, t_coor c, int iter);
int	add_red(int clr, int i, int total_i);
int	fractal_choice(t_coor zn, t_coor c, t_image *img);
void	init_c(t_coor *c, t_pixel p, t_image img, int w);
void	update_pixel(t_image *img/*, t_frac f*/);
void	init_img(t_engine *e);


/* events.c */
int	close_win(t_engine *engine);
void	zoom_manager(t_engine *e);
int	mouse_wheel(int key, int x, int y, t_engine *e);
int	resize_window(t_engine *e);



#endif
