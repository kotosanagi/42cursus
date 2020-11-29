/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_conversion_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 19:21:22 by skotoyor          #+#    #+#             */
/*   Updated: 2020/11/28 08:25:16 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


void	is_char(t_content *content)
{
	content->conv = E_CHAR;
}

void	is_string(t_content *content)
{
	content->conv = E_STRING;
}

void	is_pointer(t_content *content)
{
	content->conv = E_POINTER;
}

void	is_decimal(t_content *content)
{
	content->conv = E_DECIMAL;
}

void	is_integer(t_content *content)
{
	content->conv = E_INTEGER;
}
