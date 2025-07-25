/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:19:35 by edlucca           #+#    #+#             */
/*   Updated: 2025/04/23 19:02:25 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Check for printable character including space

int	ft_isprint(int c)
{
	if (c >= ' ' && c <= '~')
	{
		return (c);
	}
	return (0);
}
