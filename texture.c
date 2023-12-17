#include "cub3D.h"

void	get_texture_adress(t_mdata *data)
{
	data->textures[0].addr = (int *)mlx_get_data_addr(data->textures[0].img,
			&data->textures[0].bits_per_pixel,
			&data->textures[0].line_length, &data->textures[0].endian);
	data->textures[1].addr = (int *)mlx_get_data_addr(data->textures[1].img,
			&data->textures[1].bits_per_pixel,
			&data->textures[1].line_length, &data->textures[1].endian);
	data->textures[2].addr = (int *)mlx_get_data_addr(data->textures[2].img,
			&data->textures[2].bits_per_pixel,
			&data->textures[2].line_length, &data->textures[2].endian);
	data->textures[3].addr = (int *)mlx_get_data_addr(data->textures[3].img,
			&data->textures[3].bits_per_pixel,
			&data->textures[3].line_length, &data->textures[3].endian);
}

void	get_texture_img(t_mdata *data)
{
	if (!(data->textures[0].img = mlx_xpm_file_to_image(data->main_data.mlx_ptr, \
	data->so, &(data->textures[0].width), &(data->textures[0].height))))
		error_handle(data, "Texture SO\n");
	if (!(data->textures[1].img = mlx_xpm_file_to_image(data->main_data.mlx_ptr,
					data->no, &(data->textures[1].width),
					&(data->textures[1].height))))
		error_handle(data, "Texture NO\n");
	if (!(data->textures[2].img = mlx_xpm_file_to_image(data->main_data.mlx_ptr,
					data->ea, &(data->textures[2].width),
					&(data->textures[2].height))))
		error_handle(data, "Texture EA\n");
	if (!(data->textures[3].img = mlx_xpm_file_to_image(data->main_data.mlx_ptr,
					data->we, &(data->textures[3].width),
					&(data->textures[3].height))))
		error_handle(data, "Texture WE\n");
	get_texture_adress(data);
}

void	init_texture(t_mdata *data)
{
	if (data->ray.side == 0 && data->ray.raydirx < 0)
		data->tex.texdir = 0;
	if (data->ray.side == 0 && data->ray.raydirx >= 0)
		data->tex.texdir = 1;
	if (data->ray.side == 1 && data->ray.raydiry < 0)
		data->tex.texdir = 2;
	if (data->ray.side == 1 && data->ray.raydiry >= 0)
		data->tex.texdir = 3;
	if (data->ray.side == 0)
		data->tex.wallx = data->ray.posy + data->ray.perpwalldist \
						* data->ray.raydiry;
	else
		data->tex.wallx = data->ray.posx + data->ray.perpwalldist \
						* data->ray.raydirx;
	/*calculates the largest integer that is less than or equal to wallX,
	effectively truncating the decimal part of wallX and keeping only the
	integer part. first take the real number and then bring in into the
	-1,1 range of the screen*/
	data->tex.wallx -= floor((data->tex.wallx));
}

void draw_texture_pixel(int x, int y, t_mdata *data)
{
	data->main_data.addr[y * data->main_data.line_length / 4 + x] =
		data->textures[data->tex.texdir].addr[data->tex.texy *
			data->textures[data->tex.texdir].line_length /
			4 + data->tex.texx];
}

void	draw_texture(t_mdata *data, int x, int y)
{
	y = data->ray.drawstart - 1;
	init_texture(data);
	data->tex.step = 1.0 * data->textures[0].height / data->ray.lineheight;
	data->tex.texx = (int)(data->tex.wallx * (double)data->textures
			[data->tex.texdir].width);
	data->tex.texpos = (data->ray.drawstart - data->wy / 2 +
			data->ray.lineheight / 2) * data->tex.step;
	while (++y <= data->ray.drawend)
	{
		data->tex.texy = (int)data->tex.texpos &
			(data->textures[data->tex.texdir].height - 1);
		data->tex.texpos += data->tex.step;
		if (y < data->wy && x < data->wx)
			draw_texture_pixel(x, y, data);
	}
}