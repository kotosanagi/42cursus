/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 00:10:33 by skotoyor          #+#    #+#             */
/*   Updated: 2021/02/25 12:33:05 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	safe_free(void *p)
{
	free(p);
	p = NULL;
}

void	error_exit(char *message)
{
	printf("Error\n");
	printf("%s", message);
	exit(EXIT_FAILURE);
}

