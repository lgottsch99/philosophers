/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:23:14 by lgottsch          #+#    #+#             */
/*   Updated: 2025/03/23 19:35:28 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

int	main(int argc, char *argv[])
{
	t_program	program;
	int			num_philos;
	int			dead_flag;

	dead_flag = 0;
	// program.philos = NULL;
	//1. check valid input
	if (check_input_valid(argc, argv) == 0)
	{
		printf("input valid\n");
		num_philos = ft_atoi(argv[1]);
		// printf("number philos: %i\n", ft_atoi(argv[1]));
		// printf("time to die: %i\n", ft_atoi(argv[2]));
		// printf("time to eat: %i\n", ft_atoi(argv[3]));
		// printf("time to sleep: %i\n", ft_atoi(argv[4]));
		// if (argv[5])
		// 	printf("times to eat: %i\n", ft_atoi(argv[5]));

	//2. initialize structs, threads etc
		init_program(&program, argv, &dead_flag);
		//TODO fork array and pass pointers to philos
		
		//init thread for each philo?
		init_threads(&program, num_philos);

		//init mutexes





	//3. run + monitor
		//simulation();//the sim. only starts once ALL threads are created!!!

		for (int y = 0; y < num_philos; y++)
		{
			pthread_join(program.philos[y]->thread, NULL);
		}
		//4. free if dead or error?

			
		// printf("freeing philos\n");
		// free_philos(program.philos, num_philos - 1);





	}
	
	return (0);
}