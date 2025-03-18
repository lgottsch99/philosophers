/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:23:14 by lgottsch          #+#    #+#             */
/*   Updated: 2025/03/18 13:45:45 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void *function()
{
	printf("Hello\n");
	return NULL;
}


int main (int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	
	pthread_t t1;

	pthread_create(&t1, NULL, &function, NULL);

	pthread_join(t1, NULL);
	
	return (0);
}