#include <math.h>
#include "mlx.h"
#include "libft/libft.h"
#include "main.h"

#define screenWidth		640
#define screenHeight	480
#define	texWidth		64
#define	texHeight		64
#define	mapWidth		8
#define	mapHeight		8
#define	miniWidth		120
#define	miniHeight		120
#define UP				119
#define	DOWN			115
#define LEFT			97
#define	RIGHT			100
#define LEFT_ARROW		65361
#define	RIGHT_ARROW		65363

#define RGB_Red 		0x00FF0000
#define RGB_Green 		0x0000FF00
#define RGB_Blue		0x000000FF
#define RGB_White		0x00FFFFFF
#define	RGB_Yellow		0x00FFFF00

#define numSprites 		8

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_prite
{
	double 	x;
	double 	y;
	int 	texture;
}		t_prite;

struct Pair {
    double first;
    int second;
};

void sortSprites(int* order, double* dist, int amount) {
    struct Pair* sprites = (struct Pair*)malloc(amount * sizeof(struct Pair));
    if (sprites == NULL) {
        // Handle memory allocation failure
        return;
    }
    
    // Populate sprites array
    for(int i = 0; i < amount; i++) {
        sprites[i].first = dist[i];
        sprites[i].second = order[i];
    }
    
    // Sort sprites array based on the first element (distance)
    for(int i = 0; i < amount - 1; i++) {
        for(int j = 0; j < amount - i - 1; j++) {
            if(sprites[j].first > sprites[j+1].first) {
                // Swap elements
                struct Pair temp = sprites[j];
                sprites[j] = sprites[j+1];
                sprites[j+1] = temp;
            }
        }
    }

    // Restore in reverse order to go from farthest to nearest
    for(int i = 0; i < amount; i++) {
        dist[i] = sprites[amount - i - 1].first;
        order[i] = sprites[amount - i - 1].second;
    }
    
    free(sprites); // Free dynamically allocated memory
}

typedef	struct s_mlx
{
	void		*mlx;
	void		*mlx_win;
	t_img		*img;
	double		pos[2];
	double		pos_arr[2];
	double		dir[2];
	double		plane[2];
	double		ZBuffer[screenWidth];
	t_prite		*sprite;
	int			spriteOrder[numSprites];
	double		spriteDistance[numSprites];
	int			(*texture)[8][texHeight * texWidth];
	int			(*map)[mapWidth];
	int			*addr;
	int			*eddr;
	int			*wddr;
	int			*nddr;
	int			*sddr;
	int			*light;
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
		if (tx->map[(int)(tx->pos_arr[0] + tx->dir[0])][(int)tx->pos_arr[1]] == 0) 
			tx->pos_arr[0] += tx->dir[0] * 0.1;
		if (tx->map[(int)tx->pos_arr[0]][(int)(tx->pos_arr[1] + tx->dir[1])] == 0) 
			tx->pos_arr[1] += tx->dir[1] * 0.1;
	}
	else if (keycode == DOWN)
	{
		if (tx->map[(int)(tx->pos_arr[0] + tx->dir[0])][(int)tx->pos_arr[1]] == 0) 
			tx->pos_arr[0] -= tx->dir[0] * 0.1;
		if (tx->map[(int)tx->pos_arr[0]][(int)(tx->pos_arr[1] + tx->dir[1])] == 0) 
			tx->pos_arr[1] -= tx->dir[1] * 0.1;
	}
	else if (keycode == LEFT)
	{
		if (tx->map[(int)(tx->pos_arr[0] + tx->plane[0])][(int)tx->pos_arr[1]] == 0) 
			tx->pos_arr[0] -= tx->plane[0] * 0.1;
		if (tx->map[(int)tx->pos_arr[0]][(int)(tx->pos_arr[1] + tx->plane[1])] == 0) 
			tx->pos_arr[1] -= tx->plane[1] * 0.1;
	}
	else if (keycode == RIGHT)
	{
		if (tx->map[(int)(tx->pos_arr[0] + tx->plane[0])][(int)tx->pos_arr[1]] == 0) 
			tx->pos_arr[0] += tx->plane[0] * 0.1;
		if (tx->map[(int)tx->pos_arr[0]][(int)(tx->pos_arr[1] + tx->plane[1])] == 0) 
			tx->pos_arr[1] += tx->plane[1] * 0.1;
	}
	else if (keycode == RIGHT_ARROW)
	{
		double	oldDirX = tx->dir[0];
		double	rotSpeed = 0.25;
		tx->dir[0] = tx->dir[0] * cos(-rotSpeed) - tx->dir[1] * sin(-rotSpeed);
      	tx->dir[1] = oldDirX * sin(-rotSpeed) + tx->dir[1] * cos(-rotSpeed);
		double oldPlaneX = tx->plane[0];
		tx->plane[0] = tx->plane[0] * cos(-rotSpeed) - tx->plane[1] * sin(-rotSpeed);
		tx->plane[1] = oldPlaneX * sin(-rotSpeed) + tx->plane[1] * cos(-rotSpeed);
	}
	else if (keycode == LEFT_ARROW)
	{
		double	rotSpeed = 0.25;
		double	oldDirX = tx->dir[0];
		tx->dir[0] = tx->dir[0] * cos(rotSpeed) - tx->dir[1] * sin(rotSpeed);
		tx->dir[1] = oldDirX * sin(rotSpeed) + tx->dir[1] * cos(rotSpeed);
		double oldPlaneX = tx->plane[0];
		tx->plane[0] = tx->plane[0] * cos(rotSpeed) - tx->plane[1] * sin(rotSpeed);
		tx->plane[1] = oldPlaneX * sin(rotSpeed) + tx->plane[1] * cos(rotSpeed);
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
			put_pixel(tx->img, i, j++, 0x004b3a26);
		i++;
	}
}

void	fill_obstacle(void	*data)
{
	int		i;
	int		j;
	t_mlx	*tx;

	i = 0;
	j = 0;
	tx = data;
	int	ratio = miniHeight / mapHeight;
	while (i < mapHeight)
	{
		j = 0;
		while (j < mapWidth)
		{
			if (tx->map[i][j] != 0)
			{
				for (int m = i * ratio; m < (i + 1) * ratio; m++)
				for (int n = j * ratio; n < (j + 1) * ratio; n++)
					put_pixel(tx->img, m, n, 0x00FFFFFF);
			}
			j++;
		}
		i++;
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
	while (i < miniWidth)
	{
		j = 0;
		while (j < miniHeight)
			put_pixel(tx->img, i, j++, 0x00000000);
		i++;
	}
}

void fill_ceiling(void *data)
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
		while (j < screenHeight / 2)
			put_pixel(tx->img, i, j++, 0x0087ceeb);
		i++;
	}
}

void	render_frame(void *data)
{
	t_mlx	*tx = data;
	int	w = screenWidth;

	fill_screen(tx);
	fill_ceiling(tx);
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
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			int	color;
			if (rayDirX < 0 && side == 0)
				color = tx->eddr[texHeight * texY + texX];
			else if (rayDirX > 0 && side == 0)
				color = tx->wddr[texHeight * texY + texX];
			else if (rayDirY < 0 && side == 1)
				color = tx->nddr[texHeight * texY + texX];
			else if (rayDirY > 0 && side == 1)
				color = tx->sddr[texHeight * texY + texX];
			if(side == 1) color = (color >> 1) & 8355711;
			put_pixel(tx->img, x, y, color);

		}
		tx->ZBuffer[x] = perpWallDist;
	}

	// for (int i=0; i < numSprites; i++)
	// {
	// 	tx->spriteOrder[i] = i;
	// 	tx->spriteDistance[i] = ((tx->pos_arr[0] - tx->sprite[i].x) * (tx->pos_arr[0] - tx->sprite[i].x) + (tx->pos_arr[1] - tx->sprite[i].y) * (tx->pos_arr[1] - tx->sprite[i].y));
	// }

	// sortSprites(tx->spriteOrder, tx->spriteDistance, numSprites);

	// for (int i = 0; i < numSprites; i++)
	// {
	// 	double	spriteX = tx->sprite[tx->spriteOrder[i]].x - tx->pos_arr[0];
	// 	double	spriteY = tx->sprite[tx->spriteOrder[i]].y - tx->pos_arr[1];
	// 	double	invDet = 1.0 / (tx->plane[0] * tx->dir[1] - tx->dir[0] * tx->plane[1]);
	// 	double	transformX = invDet * (tx->dir[1] * spriteX - tx->dir[0] * spriteY);
	// 	double 	transformY = invDet * (-tx->plane[1] * spriteX + tx->plane[0] * spriteY);

	// 	int spriteScreenX = (int)((w / 2) * (1 + transformX / transformY));
	// 	//parameters for scaling and moving the sprites
	// 	#define uDiv 1
	// 	#define vDiv 1
	// 	#define vMove 0.0
	// 	int vMoveScreen = (int)(vMove / transformY);

	// 	//calculate height of the sprite on screen
	// 	int	h = screenHeight;
	// 	int spriteHeight = abs((int)(h / (transformY))) / vDiv; //using "transformY" instead of the real distance prevents fisheye
	// 	//calculate lowest and highest pixel to fill in current stripe
	// 	int drawStartY = -spriteHeight / 2 + h / 2 + vMoveScreen;
	// 	if(drawStartY < 0) drawStartY = 0;
	// 	int drawEndY = spriteHeight / 2 + h / 2 + vMoveScreen;
	// 	if(drawEndY >= h) drawEndY = h - 1;

	// 	//calculate width of the sprite
	// 	int spriteWidth = abs((int) (h / (transformY))) / uDiv; // same as height of sprite, given that it's square
	// 	int drawStartX = -spriteWidth / 2 + spriteScreenX;
	// 	if(drawStartX < 0) drawStartX = 0;
	// 	int drawEndX = spriteWidth / 2 + spriteScreenX;
	// 	if(drawEndX > w) drawEndX = w;

	// 	//loop through every vertical stripe of the sprite on screen
	// 	for(int stripe = drawStartX; stripe < drawEndX; stripe++)
	// 	{
	// 		int texX = (int)((stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth);
	// 		//the conditions in the if are:
	// 		//1) it's in front of camera plane so you don't see things behind you
	// 		//2) ZBuffer, with perpendicular distance
	// 		if(transformY > 0 && transformY < tx->ZBuffer[stripe])
	// 		{
	// 			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
	// 			{
	// 				int d = (y - vMoveScreen) - h * 1/2 + spriteHeight * 1/2; //256 and 128 factors to avoid floats
	// 				int texY = ((d * texHeight) / spriteHeight);
	// 				int color = tx->light[texWidth * texY + texX]; //get current color from the texture
	// 				if((color & 0x00FFFFFF) != 0) put_pixel(tx->img, stripe, y, color); //paint pixel if it isn't black, black is the invisible color
	// 			}
	// 		}
	// 	}

	// }

	fill_minimap(tx);
	fill_obstacle(tx);
	//printf("%f %f\n", tx->pos_arr[0] * 5, tx->pos_arr[1] * 5);
	put_pixel(tx->img, (int)(tx->pos_arr[0] * 5), (int)(tx->pos_arr[1] * 5), 0x00FF0000);
	mlx_put_image_to_window(tx->mlx, tx->mlx_win, tx->img->img, 0, 0);
}

int	main(void)
{
	// int worldMap[mapWidth][mapHeight]=
	// {
	// 	{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
	// 	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
	// 	{4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
	// 	{4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
	// 	{4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
	// 	{4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
	// 	{4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
	// 	{4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
	// 	{4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
	// 	{4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
	// 	{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
	// 	{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
	// 	{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
	// 	{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
	// 	{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
	// 	{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
	// 	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
	// 	{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
	// 	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
	// 	{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
	// 	{4,0,0,5,0,0,0,20,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
	// 	{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
	// 	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
	// 	{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
	// };

	int worldMap[mapWidth][mapHeight]=
	{
		{1,1,1,1,1,1,1,1},
		{1,0,0,0,1,2,1,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1},
		{1,1,0,0,0,0,1,1},
		{1,1,1,1,1,1,1,1}
	};

	t_mlx	tx;
	t_img	img;

	t_prite sprite[numSprites] =
	{
		{20.5, 11.5, 10},
		{18.5,4.5, 10},
		{10.0,4.5, 10},
		{10.0,12.5,10},
		{3.5, 6.5, 10},
		{3.5, 20.5,10},
		{3.5, 14.5,10},
		{14.5,20.5,10}
	};

	tx.sprite = sprite;

	tx.pos_arr[0] = 6;
	tx.pos_arr[1] = 5;

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
	void	*img_ptr_e = mlx_xpm_file_to_image(tx.mlx, "east.xpm", &xpm_width, &xpm_height);
	tx.eddr = (int *)mlx_get_data_addr(img_ptr_e, &temp_img.bits_per_pixel, &temp_img.line_length, &temp_img.endian);
	void	*img_ptr_w = mlx_xpm_file_to_image(tx.mlx, "west.xpm", &xpm_width, &xpm_height);
	tx.wddr = (int *)mlx_get_data_addr(img_ptr_w, &temp_img.bits_per_pixel, &temp_img.line_length, &temp_img.endian);
	void	*img_ptr_n = mlx_xpm_file_to_image(tx.mlx, "north.xpm", &xpm_width, &xpm_height);
	tx.nddr = (int *)mlx_get_data_addr(img_ptr_n, &temp_img.bits_per_pixel, &temp_img.line_length, &temp_img.endian);
	void	*img_ptr_s = mlx_xpm_file_to_image(tx.mlx, "south.xpm", &xpm_width, &xpm_height);
	tx.sddr = (int *)mlx_get_data_addr(img_ptr_s, &temp_img.bits_per_pixel, &temp_img.line_length, &temp_img.endian);
	void	*img_ptr_l = mlx_xpm_file_to_image(tx.mlx, "greenlight.xpm", &xpm_width, &xpm_height);
	tx.light = (int *)mlx_get_data_addr(img_ptr_l, &temp_img.bits_per_pixel, &temp_img.line_length, &temp_img.endian);
	mlx_hook(tx.mlx_win, 2, 1L << 0, control_keys, (void *)&tx);
	//mlx_hook(tx.mlx_win, 6, 1L << 6, control_mouse, (void *)&tx);
	mlx_loop_hook(tx.mlx, render_frame, (void *)&tx);
	//mlx_mouse_hook(tx.mlx_win, control_mouse, &tx);
	mlx_loop(tx.mlx);
	return (0);
}