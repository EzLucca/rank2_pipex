/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:18:17 by edlucca           #+#    #+#             */
/*   Updated: 2025/04/23 19:01:54 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Check for an alphabetic character
//The return c is a non zero 

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return (c);
	}
	return (0);
}
