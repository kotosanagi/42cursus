/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_conversion_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skotoyor <skotoyor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 19:21:15 by skotoyor          #+#    #+#             */
/*   Updated: 2020/11/27 21:05:22 by skotoyor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	is_unsigned(t_content *content)
{
	content->conv = E_UNSIGNED;
}

void	is_x_small(t_content *content)
{
	content->conv = E_XDECIMAL_SMALL;

}

void	is_x_large(t_content *content)
{
	content->conv = E_XDECIMAL_LARGE;

}

void	is_percent(t_content *content)
{
	content->conv = E_PERCENT;

}
