#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

typedef struct	s_area
{
	int width;
	int height;
	char bgc;
}				t_area;

typedef struct	s_circle
{
	char type;
	float x;
	float y;
	float r;
	char color;
}				t_circle;

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return i;
}

int error_func(char *msg, FILE *fp, char *buf)
{
	if (fp)
		fclose(fp);
	if (buf)
		free(buf);
	buf = NULL;
	write(1, msg, ft_strlen(msg));
	return 1;
}

int get_area(FILE *fp, t_area *area)
{
	int ret;

	if ((ret = fscanf(fp, "%d %d %c\n", &area->width, &area->height, &area->bgc)) != 3)
		return 0;
	if (area->width <= 0 || 300 < area->width
	 || area->height <= 0 || 300 < area->height)
		return 0;
	return 1;
}

char *store_buf(t_area *area)
{
	char *tmp_buf;

	if (!(tmp_buf = (char *)malloc(sizeof(char) * area->width * area->height)))
		return NULL;
	for (int i = 0; i < area->width * area->height; i++)
		tmp_buf[i] = area->bgc;
	return tmp_buf;
}

int is_in_circle(float x, float y, t_circle *circle)
{
	float distance = sqrtf(powf(x - circle->x, 2.) + powf(y - circle->y, 2.));

	if (distance <= circle->r)
	{
		if (circle->r - distance < 1.)
			return 2;
		return 1;
	}
	return 0;
}

void put_color_buf(char *buf, t_area *area, t_circle *circle)
{
	for (int y = 0; y < area->height; y++)
	{
		for (int x = 0; x < area->width; x++)
		{
			int ret = is_in_circle((float)x, (float)y, circle);
			if ((ret == 2 && circle->type == 'c') ||
				(ret && circle->type == 'C'))
				buf[y * area->width + x] = circle->color;
		}
	}
}
		
int store_shape(FILE *fp, char *buf, t_area *area)
{
	int ret;
	t_circle circle;

	while ((ret = fscanf(fp, "%c %f %f %f %c\n", &circle.type, &circle.x, &circle.y, &circle.r, &circle.color)) == 5)
	{
		if ((circle.type != 'c' && circle.type != 'C') ||
			circle.r <= 0)
			return 0;

		#ifdef TEST
		printf("==========\n");
		printf(" type:%c\n", circle.type);
		printf(" x:%f\n", circle.x);
		printf(" y:%f\n", circle.y);
		printf(" r:%f\n", circle.r);
		printf(" color:%c\n", circle.color);
		printf(" ret:%d\n", ret);
		#endif
		put_color_buf(buf, area, &circle);
	}
	if (ret != -1)
		return 0;
	return 1;
}

int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	char *buf = NULL;
	t_area area;

	if (argc != 2)
		return error_func("Error: argument\n", fp, buf);
	if (!(fp = fopen(argv[1], "r")))
		return error_func("Error: Operation file corrupted\n", fp, buf);
	area.width = 0;
	area.height = 0;
	area.bgc = '\0';
	if (!(get_area(fp, &area)))
		return error_func("Error: Operation file corrupted\n", fp, buf);
	if (!(buf = store_buf(&area)))
		return error_func("Error: Operation file corrupted\n", fp, buf);
	if (!(store_shape(fp, buf, &area)))
		return error_func("Error: Operation file corrupted\n", fp, buf);


	

	for (int y = 0; y < area.height; y++)
	{
		write(1, buf + y * area.width, area.width);
		write(1, "\n", 1);
	}
	fclose(fp);
	free(buf);
	buf = NULL;
	return 0;
}
