/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:54:34 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/25 11:54:39 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>

int main()
{
	if (access("example.txt", R_OK) != -1)
		printf("I have permission\n");
	else
		printf("I don't have permission\n");

	return (0);
}
