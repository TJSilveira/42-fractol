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

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
    int		x;
    int		y;
    t_image	img;
	int	color;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "tsilveir - Fractol implementation");
	img.img = mlx_new_image(mlx, 1920, 1080);
    img.addr = mlx_get_data_addr(img.img, &img.pix_bits, &img.line_len, &img.endian);

    x = 0;
	color = 0x00FF0000;
    while (++x < 1000)
    {
    	y = 0;
		while (++y < 500)
		{
			if (pow(x-200,2) + pow(y-200, 2) <= 4000 && pow(x-200,2) + pow(y-200, 2) >= 3600)
			{
				my_mlx_pixel_put(&img, x, y, color);
				color -= 255*100;
			}
		}
    }
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}