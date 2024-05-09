#include <math.h>
#include "mlx.h"
#include "libft/libft.h"
#include "main.h"

#define UP		65362
#define	DOWN	65364
#define LEFT	65361
#define	RIGHT	65363
#define	BG		0x00000000
#define RED_DOT 0x00FF0000
#define	WIDTH	100
#define	HEIGHT	100
#define	SPEED	3
#define	ROTATE_AMT	100

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef	struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	t_img	*img;
	double		pos[2];
	double		dir[2];
	double		plane[2];
}				t_mlx;


void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	draw_line(t_mlx *tx, int begin_x, int begin_y, int end_x, int end_y, int color)
{
	double	delta_x = end_x - begin_x;
	double	delta_y = end_y - begin_y;

	int	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));

	delta_x /= pixels;
	delta_y /= pixels;

	double pixel_x = begin_x;
	double pixel_y = begin_y;
	while (pixels)
	{
		put_pixel(tx->img, pixel_x, pixel_y, color);
		pixel_x += delta_x;
		pixel_y += delta_y;
		pixels--;
	}
}

void	*control_keys(int keycode, t_mlx *tx)
{
	double	temp;

	if (keycode == UP)
	{
		put_pixel(tx->img, tx->pos[0], tx->pos[1], BG);
		if (tx->pos[1] - SPEED >= 0)
		{
			//tx->pos[1] -= SPEED;
			tx->pos[0] += tx->dir[0];
			tx->pos[1] -= tx->dir[1];
			put_pixel(tx->img, tx->pos[0], tx->pos[1], RED_DOT);
			mlx_put_image_to_window(tx->mlx, tx->mlx_win, tx->img->img, 0, 0);
		}
		else
			tx->pos[1] = 0;
	}
	else if (keycode == DOWN)
	{
		put_pixel(tx->img, tx->pos[0], tx->pos[1], BG);
		if (tx->pos[1] + SPEED <= HEIGHT)
		{
			tx->pos[0] -= tx->dir[0];
			tx->pos[1] += tx->dir[1];
			put_pixel(tx->img, tx->pos[0], tx->pos[1], RED_DOT);
			mlx_put_image_to_window(tx->mlx, tx->mlx_win, tx->img->img, 0, 0);
		}
		else
			tx->pos[1] = HEIGHT - 1;
	}
	else if (keycode == LEFT)
	{
		temp = tx->dir[0];
		tx->dir[0] = tx->dir[0] * cos(-1 * ROTATE_AMT) - tx->dir[1] * sin(-1 * ROTATE_AMT);
		tx->dir[1] = temp * sin(-1 * ROTATE_AMT) + tx->dir[1] * cos(-1 * ROTATE_AMT);
	}
	else if (keycode == RIGHT)
	{
		temp = tx->dir[0];
		tx->dir[0] = tx->dir[0] * cos(ROTATE_AMT) - tx->dir[1] * sin(ROTATE_AMT);
		tx->dir[1] = temp * sin(ROTATE_AMT) + tx->dir[1] * cos(ROTATE_AMT);
	}
}

void	fill_minimap(void *data)
{
	int	i;
	int	j;
	t_mlx	*tx;

	i = 0;
	j = 0;
	tx = data;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
			put_pixel(tx->img, i, j++, BG);
		i++;
	}
}

void	render_frame(void *data)
{
	t_mlx	*tx;

	tx = data;
	fill_minimap(tx);
	draw_line(tx, tx->pos[0], tx->pos[1], tx->pos[0] + (tx->dir[0] * 10) + (tx->plane[0] * 10), tx->pos[1] - (tx->dir[1] * 10), 0x00FFFFFF);
	draw_line(tx, tx->pos[0], tx->pos[1], tx->pos[0] + (tx->dir[0] * 10), tx->pos[1] - (tx->dir[1] * 10), 0x00FFFFFF);
	mlx_put_image_to_window(tx->mlx, tx->mlx_win, tx->img->img, 0, 0);
}

int	main(void)
{
	t_mlx	tx;
	t_img	img;
	int		map[2][2] = 
	{
		{1, 1},
		{0, 1}
	};

	tx.pos[0] = 10;
	tx.pos[1] = 90;

	tx.dir[0] = 0;
	tx.dir[1] = 1;

	tx.plane[0] = 0.66;
	tx.plane[1] = 0;

	tx.mlx = mlx_init();
	tx.mlx_win = mlx_new_window(tx.mlx, WIDTH, HEIGHT, "cub3d");
	img.img = mlx_new_image(tx.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	tx.img = &img;
	put_pixel(tx.img, tx.pos[0], tx.pos[1], 0x00FF0000);
	mlx_put_image_to_window(tx.mlx, tx.mlx_win, tx.img->img, 0, 0);
	
	mlx_loop_hook(tx.mlx, render_frame, (void *)&tx);
	mlx_key_hook(tx.mlx_win, control_keys, (void *)&tx);
	mlx_loop(tx.mlx);
	return (0);
}