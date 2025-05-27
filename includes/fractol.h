#ifndef FRACTOL_H
#define FRACTOL_H
#include "../includes/libft.h"
#include <math.h>
#include <mlx.h>


typedef struct s_image
{
	void	*img;
	char	*addr;
	int		pix_bits;
	int		line_len;
	int		endian;
}	t_image;


#endif
