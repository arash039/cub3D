#include "cub3D.h"

int		newline_check(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*join_and_free(char *s1, char *s2)
{
	char *temp = s1;
	s1 = ft_strjoin(s1, s2);
	free(temp);
	return s1;
}

void	copy_buff_to_line(char **line, char **buff, int start)
{
	char *temp = ft_substr(*buff, 0, start);
	*line = join_and_free(*line, temp);
	free(temp);
	*buff = ft_subbuff(*buff, start + 1, (ft_strlen(*buff) - start));
}

int		ft_copy(char **line, char **buff)
{
	int	start = newline_check(*buff);

	if (start >= 0)
	{
		copy_buff_to_line(line, buff, start);
		return 0;
	}
	*line = join_and_free(*line, *buff);
	return 1;
}

int		ft_eof(int ret, char **buff, char **line)
{
	if (ret == -1)
		return (-1);
	free(*buff);
	*buff = NULL;
	if (*line == NULL)
	{
		*line = malloc(sizeof(char) * 1);
		*line[0] = 0;
	}
	return (0);
}

int		gnl_exit(char **buff, t_mdata *data)
{
	if (data->err_msg != NULL && *buff)
	{
		free(*buff);
		error_handle(data, data->err_msg);
	}
	return (0);
}

int		check_buff(char **buff, char **line)
{
	int ret;
	
	ret = 1;
	if (*buff)
		ret = ft_copy(line, buff);
	return ret;
}

int		allocate_buff(char **buff)
{
	if (!*buff)
	{
		*buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!*buff)
			return (-1);
	}
	return (1);
}

int		read_file(int fd, char **buff, char **line)
{
	int	ret;
	
	ret = read(fd, *buff, BUFFER_SIZE);
	while (ret > 0)
	{
		(*buff)[ret] = '\0';
		if (!ft_copy(line, buff))
			return (1);
		ret = read(fd, *buff, BUFFER_SIZE);
	}
	return ret;
}

int		get_next_line(int fd, char **line, t_mdata *data)
{
	static char	*buff = NULL;
	int			ret;

	if (gnl_exit(&buff, data) == 1)
		return (0);
	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	*line = NULL;
	ret = check_buff(&buff, line);
	if (ret == 0)
		return (1);
	if (allocate_buff(&buff) == -1)
		return (-1);
	ret = read_file(fd, &buff, line);
	if (ret <= 0)
		return ft_eof(ret, &buff, line);
	return (1);
}

