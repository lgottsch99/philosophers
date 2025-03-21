/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:23:03 by lgottsch          #+#    #+#             */
/*   Updated: 2025/03/21 17:56:39 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>	//printf
#include <stdlib.h> //malloc, free
#include <unistd.h> //write, usleep
#include <string.h> //memset
#include <sys/time.h> //gettimeofday

//STRUCTS
typedef struct s_philo
{
	pthread_t	thread;
	int			num;//same as index in array
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			times_to_eat; //-1 if not given as cl arg
	int			fork; //1 if not used and available
	int			dead;//1 if philo died
	int			times_eaten;
	int			*dead_flag; //pointer to dead flag
//...
}	t_philo;

typedef struct s_program
{
	int					dead_flag;//0 if all alive, 1 once sb died
	t_philo 			**philos;//array of ptrs to philo structs
	// pthread_mutex_t		fork_right;
	// pthread_mutex_t		fork_left;

	
}	t_program;

//main
void *function();
void	*routine(void *arg);
//input
int	check_input_valid(int argc, char *argv[]);

//init
// void	init_threads(t_philo **philos, int num_philos);
void	init_threads(t_program *program, int num_philos);

void	init_program(t_program *program, char *argv[]);


//utils
int		ft_atoi(const char *nptr);

//free
void	free_philos(t_philo **array, int i);
