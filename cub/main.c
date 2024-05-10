#include <math.h>
#include "mlx.h"
#include "libft/libft.h"
#include "main.h"

#define UP		65362
#define	DOWN	65364
#define LEFT	65361
#define	RIGHT	65363
#define	SPACE	32
#define	BG		0x00000000
#define RED_DOT 0x00FF0000
#define	BOX		0x00FFFFFF
#define	WIDTH	100
#define	HEIGHT	100
#define MAP_WIDTH	2
#define	MAP_HEIGHT	2
#define	SPEED	3
#define	ROTATE_AMT	25

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
	void		*mlx;
	void		*mlx_win;
	t_img		*img;
	double		pos[2];
	double		pos_arr[2];
	double		dir[2];
	double		plane[2];
	int			(*map)[MAP_WIDTH];
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
		if (pixel_y < 0 || pixel_y > HEIGHT)
			break;
		if (pixel_x > WIDTH || pixel_x < 0)
			break;
		pixels--;
	}
}

void	*control_keys(int keycode, t_mlx *tx)
{
	double	temp;
	printf("%d\n", keycode);
	if (keycode == UP)
	{
		if (tx->pos[1] - SPEED >= 0)
		{
			draw_line(tx, tx->pos[0], tx->pos[1], tx->pos[0] + (tx->dir[0] * 10) + (tx->plane[0] * 10), tx->pos[1] - (tx->dir[1] * 10) - (tx->plane[1] * 10), 0x00000000);
		draw_line(tx, tx->pos[0], tx->pos[1], tx->pos[0] + (tx->dir[0] * 10), tx->pos[1] - (tx->dir[1] * 10), 0x00000000);
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
		if (tx->pos[1] + SPEED <= HEIGHT)
		{
			draw_line(tx, tx->pos[0], tx->pos[1], tx->pos[0] + (tx->dir[0] * 10) + (tx->plane[0] * 10), tx->pos[1] - (tx->dir[1] * 10) - (tx->plane[1] * 10), 0x00000000);
			draw_line(tx, tx->pos[0], tx->pos[1], tx->pos[0] + (tx->dir[0] * 10), tx->pos[1] - (tx->dir[1] * 10), 0x00000000);
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
		draw_line(tx, tx->pos[0], tx->pos[1], tx->pos[0] + (tx->dir[0] * 10) + (tx->plane[0] * 10), tx->pos[1] - (tx->dir[1] * 10) - (tx->plane[1] * 10), 0x00000000);
		draw_line(tx, tx->pos[0], tx->pos[1], tx->pos[0] + (tx->dir[0] * 10), tx->pos[1] - (tx->dir[1] * 10), 0x00000000);
		temp = tx->dir[0];
		tx->dir[0] = tx->dir[0] * cos(-1 * ROTATE_AMT) - tx->dir[1] * sin(-1 * ROTATE_AMT);
		tx->dir[1] = temp * sin(-1 * ROTATE_AMT) + tx->dir[1] * cos(-1 * ROTATE_AMT);

		temp = tx->plane[0];
		tx->plane[0] = tx->plane[0] * cos(-1 * ROTATE_AMT) - tx->plane[1] * sin(-1 * ROTATE_AMT);
		tx->plane[1] = temp * sin(-1 * ROTATE_AMT) + tx->plane[1] * cos(-1 * ROTATE_AMT);
	}
	else if (keycode == RIGHT)
	{
		draw_line(tx, tx->pos[0], tx->pos[1], tx->pos[0] + (tx->dir[0] * 10) + (tx->plane[0] * 10), tx->pos[1] - (tx->dir[1] * 10) - (tx->plane[1] * 10), 0x00000000);
		draw_line(tx, tx->pos[0], tx->pos[1], tx->pos[0] + (tx->dir[0] * 10), tx->pos[1] - (tx->dir[1] * 10), 0x00000000);
		temp = tx->dir[0];
		tx->dir[0] = tx->dir[0] * cos(ROTATE_AMT) - tx->dir[1] * sin(ROTATE_AMT);
		tx->dir[1] = temp * sin(ROTATE_AMT) + tx->dir[1] * cos(ROTATE_AMT);

		temp = tx->plane[0];
		tx->plane[0] = tx->plane[0] * cos(ROTATE_AMT) - tx->plane[1] * sin(ROTATE_AMT);
		tx->plane[1] = temp * sin(ROTATE_AMT) + tx->plane[1] * cos(ROTATE_AMT);

		printf("%f %f %f %f\n", tx->dir[0], tx->dir[1], tx->plane[0], tx->plane[1]);
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

float	abs_float(float	x)
{
	if (x < 0)
		return (x * -1);
	return (x);
}

void	render_frame(void *data)
{
	t_mlx	*tx;

	tx = data;
	//float	x = 0.2;
	//while (x < 0.66)
	//{
	//	float	tempX = tx->dir[0] + x;
	//	float	tempY = tx->dir[1] + tx->plane[1];

	//	float	unitX = sqrt(1 + ((tempY * tempY)/(tempX *tempX)));
	//	float	unitY = sqrt(1 + ((tempX * tempX)/(tempY *tempY)));

	//	float	distX = 0;
	//	float	distY = 0;

	//	distX += unitX;
	//	distY += unitY;

	//	float	scale = distX * 50 / distY;

	//	float	lineX = tx->pos[0] + (tx->dir[0] * (int)scale) + (x * (int)scale);
	//	float	lineY = tx->pos[1] - (tx->dir[1] * (int)scale) - (tx->plane[1] * (int)scale);
		
	//	draw_line(tx, tx->pos[0], tx->pos[1], lineX, lineY, 0x00FFFFFF);
	//	draw_line(tx, tx->pos[0], tx->pos[1], tx->pos[0] + (tx->dir[0] * 10), tx->pos[1] - (tx->dir[1] * 10), 0x00FFFFFF);
	//	x += 0.02;
	//}
	
	draw_line(tx, tx->pos[0], tx->pos[1], tx->pos[0] + (tx->dir[0] * 10) + (tx->plane[0] * 10), tx->pos[1] - (tx->dir[1] * 10) - (tx->plane[1] * 10), 0x00FFFFFF);
	draw_line(tx, tx->pos[0], tx->pos[1], tx->pos[0] + (tx->dir[0] * 10), tx->pos[1] - (tx->dir[1] * 10), 0x00FFFFFF);
	mlx_put_image_to_window(tx->mlx, tx->mlx_win, tx->img->img, 0, 0);
}

void	fill_obstacle(t_mlx *tx, int i, int j, int ppv)
{
	int	h;
	int	w;

	h = i * ppv;
	while (h < (i * ppv) + ppv - 1)
	{
		w = j * ppv;
		while (w < (j * ppv) + ppv - 1)
		{
			put_pixel(tx->img, w, h, 0x00FFFFFF);
			w++;
		}
		h++;
	}
	mlx_put_image_to_window(tx->mlx, tx->mlx_win, tx->img->img, 0, 0);
}

void	fill_minimap_init(void *data)
{
	t_mlx	*tx;
	int		i;
	int		j;
	int		pixel_per_value;

	tx = data;
	pixel_per_value = WIDTH / MAP_WIDTH; // 100 / 2 = 50
	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			if (tx->map[i][j] == 1)
			{
				fill_obstacle(tx, i, j, pixel_per_value);
			}
			j++;
		}
		i++;
	}
}

int	main(void)
{
	t_mlx	tx;
	t_img	img;

	int		map[MAP_HEIGHT][MAP_WIDTH] = 
	{
		{1, 1},
		{0, 1}
	};

	tx.pos[0] = 30;
	tx.pos[1] = 90;

	tx.pos_arr[0] = tx.pos[0] / 50;
	tx.pos_arr[1] = tx.pos[1] / 50;

	tx.dir[0] = 0;
	tx.dir[1] = 1;

	//tx.dir[0] = 0.86;
	//tx.dir[1] = 0.5;

	tx.plane[0] = 1;
	tx.plane[1] = 0;

	//tx.plane[0] = -0.5;
	//tx.plane[1] = 0.86;

	tx.map = map;

	tx.mlx = mlx_init();
	tx.mlx_win = mlx_new_window(tx.mlx, WIDTH, HEIGHT, "cub3d");
	img.img = mlx_new_image(tx.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	tx.img = &img;
	put_pixel(tx.img, tx.pos[0], tx.pos[1], 0x00FF0000);
	mlx_put_image_to_window(tx.mlx, tx.mlx_win, tx.img->img, 0, 0);
	fill_minimap_init(&tx);

	float x = 0.001;

	float	rayX, rayY;
	float	deltaX, deltaY;
	float	distX, distY;
	int		hit = 0;
	int		mapX, mapY;
	int		side = 0;

	mapX = (int)tx.pos_arr[0];
	mapY = (int)tx.pos_arr[1];

	//while (x < 1)
	//{
		
	//	x += 0.02;
	//}

	x = 0.4;
	mapX = (int)tx.pos_arr[0];
	mapY = (int)tx.pos_arr[1];
	//printf("%d %d\n", mapX, mapY);
	hit = 0;
	rayX = tx.dir[0] + tx.plane[0] * x;
	rayY = tx.dir[1] + tx.plane[1] * x;

	deltaX = sqrt(1 + ((rayY * rayY)/(rayX * rayX)));
	deltaY = sqrt(1 + ((rayX * rayX)/(rayY * rayY)));

	distX = (mapX + 1.0 - tx.pos_arr[0]) * deltaX;
	//distY = (mapY + 1.0 - tx.pos_arr[1]) * deltaY;
	distY = (tx.pos_arr[1] - mapY) * deltaY;

	printf("%f %f\n", deltaX, deltaY);
	printf("%f %f\n", distX, distY);

	while (hit == 0)
	{
		if (distX < distY)
		{
			distX += deltaX;
			mapX += 1;
			side = 0;
		}
		else
		{
			distY += deltaY;
			mapY += -1;
			side = 1;
		}
		if (tx.map[mapY][mapX] == 1)
		{
			hit = 1;
		}
	}
	printf("%f %f %d %d %d =%d\n", distX, distY, mapX, mapY, tx.map[mapY][mapX], side);

	//if (distX < distY)
	//{
	//	distX += deltaX;
	//	mapY += 1;
	//	side = 0;
	//}
	//else
	//{
	//	distY += deltaY;
	//	mapX += -1;
	//	side = 1;
	//}
	
	mlx_loop_hook(tx.mlx, render_frame, (void *)&tx);
	mlx_key_hook(tx.mlx_win, control_keys, (void *)&tx);
	mlx_loop(tx.mlx);
	return (0);
}