#include <math.h>
#include "mlx.h"
#include "libft/libft.h"
#include "main.h"

#define screenWidth	640
#define screenHeight	480
#define	texWidth	64
#define	texHeight	64
#define	mapWidth	24
#define	mapHeight	24
#define UP		119
#define	DOWN	115

#define RGB_Red 	0x00FF0000
#define RGB_Green 	0x0000FF00
#define RGB_Blue	0x000000FF
#define RGB_White	0x00FFFFFF
#define	RGB_Yellow	0x00FFFF00

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
	int			(*texture)[8][texHeight * texWidth];
	int			(*map)[mapWidth];
	int			*addr;
}				t_mlx;

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

double	abs_double(double x)
{
	if (x < 0)
		return (-1 * x);
	return (x);
}

void	*control_keys(int keycode, t_mlx *tx)
{
	double	temp;
	if (keycode == UP)
	{
		tx->pos_arr[0] += tx->dir[0] * 0.1;
		tx->pos_arr[1] += tx->dir[1] * 0.1;
	}
	else if (keycode == DOWN)
	{
		tx->pos_arr[0] -= tx->dir[0] * 0.1;
		tx->pos_arr[1] -= tx->dir[1] * 0.1;
	}
}

void	fill_screen(void *data)
{
	int	i;
	int	j;
	t_mlx	*tx;

	i = 0;
	j = 0;
	tx = data;
	while (i < screenWidth)
	{
		j = 0;
		while (j < screenHeight)
			put_pixel(tx->img, i, j++, 0x00000000);
		i++;
	}
}

void	render_frame(void *data)
{
	t_mlx	*tx = data;
	int	w = screenWidth;

	fill_screen(tx);
	for (int x = 0; x < w; x++)
	{
		double	cameraX = 2 * x / (double)w - 1;
		double	rayDirX = tx->dir[0] + tx->plane[0] * cameraX;
		double	rayDirY = tx->dir[1] + tx->plane[1] * cameraX;

		int	mapX = (int)tx->pos_arr[0];
		int	mapY = (int)tx->pos_arr[1];

		double	sideDistX;
		double	sideDistY;

		double	deltaDistX = (rayDirX == 0) ? 1e30 : abs_double(1 / rayDirX);
		double	deltaDistY = (rayDirY == 0) ? 1e30 : abs_double(1 / rayDirY);
		double	perpWallDist;

		int	stepX;
		int	stepY;

		int	hit = 0;
		int	side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (tx->pos_arr[0] - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - tx->pos_arr[0]) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (tx->pos_arr[1] - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - tx->pos_arr[1]) * deltaDistY;
		}

		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}

			if (tx->map[mapX][mapY] > 0) hit = 1;
		}
		
		if (side == 0) perpWallDist = (sideDistX - deltaDistX);
		else			perpWallDist = (sideDistY - deltaDistY);

		int	h = screenHeight;
		int	lineHeight = (int)(h / perpWallDist);
		int	pitch = 0;
		int drawStart = ((-1 * lineHeight)) / 2 + h / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if(drawEnd >= h) drawEnd = h - 1;

		double wallX; 
		if(side == 0) wallX = tx->pos_arr[1] + perpWallDist * rayDirY;
		else          wallX = tx->pos_arr[0] + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		int texX = (int)(wallX * (double)texWidth);
		if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
		if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

		double step = 1.0 * texHeight / lineHeight;
		double texPos = (drawStart - pitch - h / 2 + lineHeight / 2) * step;
		for(int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			int color = tx->addr[texHeight * texY + texX];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(side == 1) color = (color >> 1) & 8355711;
			put_pixel(tx->img, x, y, color);
		}
		//int	color;
		//switch(tx->map[mapX][mapY])
		//{
		//	case 1:  color = RGB_Red;    break; //red
		//	case 2:  color = RGB_Green;  break; //green
		//	case 3:  color = RGB_Blue;   break; //blue
		//	case 4:  color = RGB_White;  break; //white
		//	default: color = RGB_Yellow; break; //yellow
		//}
		//if (side == 1) { color = color / 2; }
		//for (int y=drawStart; y < drawEnd; y++)
		//{
		//	put_pixel(tx->img, x, y, color);
		//}
	}
	mlx_put_image_to_window(tx->mlx, tx->mlx_win, tx->img->img, 0, 0);
	
}

int	main(void)
{
	int worldMap[mapWidth][mapHeight]=
	{
		{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
		{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
		{4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
		{4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
		{4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
		{4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
		{4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
		{4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
		{4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
		{4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
		{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
		{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
		{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
		{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
		{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
		{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
		{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
		{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
		{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
		{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
		{4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
		{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
		{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
		{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
	};

	t_mlx	tx;
	t_img	img;

	tx.pos_arr[0] = 22;
	tx.pos_arr[1] = 12;

	tx.dir[0] = -1.0;
	tx.dir[1] = 0.0;

	tx.plane[0] = 0;
	tx.plane[1] = 0.66;

	tx.map = worldMap;

	tx.mlx = mlx_init();
	tx.mlx_win = mlx_new_window(tx.mlx, screenWidth, screenHeight, "cub3d");
	img.img = mlx_new_image(tx.mlx, screenWidth, screenHeight);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	tx.img = &img;
	t_img	temp_img;
	int	xpm_width;
	int	xpm_height;
	void	*img_ptr = mlx_xpm_file_to_image(tx.mlx, "mossy.xpm", &xpm_width, &xpm_height);
	tx.addr = (int *)mlx_get_data_addr(img_ptr, &temp_img.bits_per_pixel, &temp_img.line_length, &temp_img.endian);
	mlx_hook(tx.mlx_win, 2, 1L << 0, control_keys, (void *)&tx);
	//mlx_hook(tx.mlx_win, 6, 1L << 6, control_mouse, (void *)&tx);
	mlx_loop_hook(tx.mlx, render_frame, (void *)&tx);
	//mlx_mouse_hook(tx.mlx_win, control_mouse, &tx);
	mlx_loop(tx.mlx);
	return (0);
}