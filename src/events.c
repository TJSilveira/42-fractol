#include "../includes/fractol.h"


int	close_win(t_engine *engine)
{
	mlx_destroy_window(engine->mlx,engine->window);
	exit(0);
}