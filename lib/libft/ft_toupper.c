/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:22:33 by edlucca           #+#    #+#             */
/*   Updated: 2025/04/26 21:00:38 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// If c is a lowercase letter, toupper() returns its uppercase equivalent, 
// if an uppercase repre‐ sentation exists in the current locale.  
// Otherwise, it returns c.

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
