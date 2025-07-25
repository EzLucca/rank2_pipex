/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:22:37 by edlucca           #+#    #+#             */
/*   Updated: 2025/04/26 21:01:11 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// If c is an uppercase letter, tolower() returns its lowercase equivalent, 
// if a lowercase representation exists in the current locale. 
// Otherwise, it returns c.

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
