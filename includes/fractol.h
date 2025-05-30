#ifndef FRACTOL_H
#define FRACTOL_H
#include "../includes/libft.h"
#include <math.h>
#include <mlx.h>

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
	int		endian;
	t_coor	top_left;
	t_coor	bot_right;
}	t_image;

typedef struct s_engine
{
	void	*mlx;
	void	*window;
}	t_engine;

/* events.c */
int	close_win(t_engine *engine);


#endif
