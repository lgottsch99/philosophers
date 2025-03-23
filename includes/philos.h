/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:23:03 by lgottsch          #+#    #+#             */
/*   Updated: 2025/03/23 19:06:06 by lgottsch         ###   ########.fr       */
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
	pthread_t		thread;
	int				num;//same as index in array
	int				time_die;
	int				time_eat;
	int				time_sleep;
	// int			times_to_eat; //-1 if not given as cl arg
	int				*own_fork; //1 if not used and available
	int				*fork_right;
	int				dead;//1 if philo died
	int				times_eaten;
	int				*dead_flag; //pointer to dead flag
	long			*start_time; //of program
	long			end_last_meal;
	pthread_mutex_t	*mutex_own_fork;
	pthread_mutex_t	*mutex_fork_right;
	pthread_mutex_t	mutex_times_eaten; //to lock times eaten variable
	pthread_mutex_t	mutex_end_last_meal;

	//...
}	t_philo;

typedef struct s_program
{
	int					num_philos;
	int					*dead_flag;//0 if all alive, 1 once sb died
	t_philo 			**philos;//array of ptrs to philo structs
	long				start_time; //saving start time of prorgram in millisec
	int					*forks;
	pthread_mutex_t		*fork_mutexes; //as many as forks, match by index?
	pthread_t			monitor;
	int					times_to_eat; //-1 if not given as cl arg

	// pthread_mutex_t		fork_right;
	// pthread_mutex_t		fork_left;

	
}	t_program;


//main
void	*function();
void	*routine(void *arg);
//input
int	check_input_valid(int argc, char *argv[]);

//init
// void	init_threads(t_philo **philos, int num_philos);
void	init_threads(t_program *program, int num_philos);

void	init_program(t_program *program, char *argv[], int *dead_flag);

//routine
void	eat(t_philo *philo);
void	go_sleep(t_philo *philo);

//moitor
void	*monitoring(void *arg);
void	did_sb_die(t_program *program);
void	did_all_eat(t_program *program);

//utils
int		ft_atoi(const char *nptr);
long	get_time_ms(void);
void	print_philo(t_philo *philo);

//free
void	free_philos(t_philo **array, int i);
