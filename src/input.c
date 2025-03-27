/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:51:55 by lgottsch          #+#    #+#             */
/*   Updated: 2025/03/27 17:55:38 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

static int	check_digits(char *arg)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	//get len
	while (arg[len] != '\0')
		len++;
	//check digits
	while (i < len)
	{
		//printf("checking arg[i]: %c\n", arg[i]);
		if (arg[i] < '0' || arg[i] > '9')
			return (1); //not a digit
		i++;
	}
	return (0);
}

///all numeric (and > 0 except arg nr 5) args
	//for each arg:
		//check if only digits
		//if yes check atoi > 0? (excepils.c ./src/free.c ./src/init.c ./src/routine.c ./src/monitor.c -o philo
int	check_input_valid(int argc, char *argv[])
{
	int	i;

	i = 1;
	//4 or 5
	if (argc < 5 || argc > 6) //./philo is arg nr 1!
	{
		printf("Usage: <numberPhilos> <timeToDie> <timeToEat> <timeToSleep> [<numberOfTimesToEat>]\n");
		return(1);
	}
	while (i < argc)
	{
		if (check_digits(argv[i]) == 1)
		{
			printf("Input invalid: only positive numeric args allowed!\n");
			return(1);
		}
		if (i != 5)
		{//check if bigger 0
			if (!(argv[i][0] > '0' && argv[i][0] <= '9'))
			{
				printf("Input invalid: Arg nr 1-4 need to be bigger 0!\n");
				return(1);
			}
		}
		i++;
	}
	return (0);
}
