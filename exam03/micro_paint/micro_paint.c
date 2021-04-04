#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct	s_rec
{
	char type;
	float x;
	float y;
	float width;
	float height;
	char color;
}				t_rec;

typedef struct	s_area
{
	int width;
	int height;
	char bgc;
}				t_area;

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

	if ((ret = fscanf(fp, "%d %d %c\n", &area->width, &area->height, &area->bgc)) == 3)
	{
		if (area->width <= 0 || 300 < area->width
		  ||area->height <= 0 || 300 < area->height)
			return 0;
		return 1;
	}
	return 0;
}

char *store_bgc(t_area *area)
{
	char *ret_buf;
	if (!(ret_buf = (char *)malloc(sizeof(char) * area->width * area->height)))
		return NULL;
	for (int i = 0; i < area->width * area->height; i++)
		ret_buf[i] = area->bgc;
	return ret_buf;
}

int is_in_rectangle(float x, float y, t_rec *rec)
{
	if (x < rec->x || (rec->x + rec->width) < x ||
		y < rec->y || (rec->y + rec->height) < y)
		return 0;
	if (x - rec->x < 1. || (rec->x + rec->width) - x < 1. ||
		y - rec->y < 1. || (rec->y + rec->height) - y < 1. )
		return 2;
	return 1;
}

void	put_color_buf(char *buf, t_area *area, t_rec *rec)
{
	for (int y = 0; y < area->height; y++)
	{
		for (int x = 0; x < area->width; x++)
		{
			int ret = is_in_rectangle((float)x, (float)y, rec);
			if ((ret == 2 && rec->type == 'r') || 
				(ret && rec->type == 'R'))
				buf[y * area->width + x] = rec->color;
		}
	}
}
int store_shape(char *buf, FILE *fp, t_area *area)
{
	t_rec rec;
	int ret;

	while ((ret = fscanf(fp, "%c %f %f %f %f %c\n", &rec.type, &rec.x , &rec.y , &rec.width, &rec.height, &rec.color)) == 6)
	{
		#ifdef TEST
		printf("--- store_chape ---\n");
		printf("  type:%c\n", rec.type);
		printf("     x:%f\n", rec.x);
		printf("     y:%f\n", rec.y);
		printf(" width:%f\n", rec.width);
		printf("height:%f\n", rec.height);
		printf(" color:%c\n", rec.color);
		printf("ret:%d\n", ret);
		printf("-------------------\n");
		#endif
		if ((rec.type != 'r' && rec.type != 'R') ||
			rec.width <= 0. ||
			rec.height <= 0.)
			return 0;
		put_color_buf(buf, area, &rec);
	}
	#ifdef TEST
	printf("ret:%d\n", ret);
#endif
	if (ret != -1)
		return 0;
	return 1;
}
/*
int store_shape(char *buf, FILE *fp, t_area *area)
{
    t_rec rec;
    int ret;

    while ((ret = fscanf(fp, "%c %f %f %f %f %c\n", &rec.type, &rec.x, &rec.y, &rec.width, &rec.height, &rec.color)) == 6)
    {   
        #ifdef TEST
        printf("---store_shape---\n");
        printf("r      : %c\n", rec.type);
        printf("x      : %f\n", rec.x);
        printf("y      : %f\n", rec.y);
        printf("width  : %f\n", rec.width);
        printf("height : %f\n", rec.height);
        printf("c      : %c\n", rec.color);
        printf("---store_shape---\n");
        #endif
        if ((rec.type != 'r' && rec.type != 'R') || rec.width <= 0. || rec.height <= 0.)
            return 0;
		put_color_buf(buf, area, &rec);
    }   
    if (ret != -1) 
        return 0;
    return 1;
}

*/

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
	if (!get_area(fp, &area))
		return error_func("Error: Operation file corrupted\n", fp, buf);
	if (!(buf = store_bgc(&area)))
		return error_func("Error: Operation file corrupted\n", fp, buf);
	if (!(store_shape(buf, fp, &area)))
		return error_func("Error: Operation file corrupted\n", fp, buf);
			

	for (int i = 0; i < area.height; i++)
	{
		write(1, buf + (i * area.width), area.width);
		write(1, "\n", 1);
	}
	fclose(fp);
	free(buf);
	buf = NULL;
	return 0;
}
