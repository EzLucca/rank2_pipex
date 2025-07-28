/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 10:39:20 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/28 10:40:58 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

void	ft_error_exit(char *str)
{
	ft_printf("Error: %s\n", str);
	exit(EXIT_FAILURE);
}
