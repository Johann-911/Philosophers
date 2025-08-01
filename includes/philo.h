/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:53:37 by jtoumani          #+#    #+#             */
/*   Updated: 2025/08/01 16:26:12 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
#include <stdint.h>

typedef struct s_infos
{
	int				number_of_philos;
	int             dead_philo_id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long			start_time;
	int				max_eat;
	bool            sim_end;
	pthread_mutex_t print_mutex;     
    pthread_mutex_t death_mutex;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
}					t_infos;

typedef struct s_philo
{
	int				philo_id;
	long			meal_counter;
	int				last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t  meal_mutex;
	pthread_mutex_t	*right_fork;
	t_infos			*infos;
}					t_philo;

//src
int main(int argc, char **argv);

//error_handling
void	wrong_input();
//philo
void	*philo_routine(void *arg);
void	takes_fork(t_philo *philo);
void	release_fork(t_philo *philo);
bool watchdog(t_infos *infos);
void print_status(t_philo *philo, char *status);
void cleanup(t_infos *infos);
long get_current_time(t_infos *infos);
void custom_sleep(long ms, t_philo *philo);
void *solo_mandem(void *arg);
int is_philo_dead(t_philo *philo);
//init
void init_infos(int argc, char **argv, t_infos *infos);
void create_threads(t_infos *infos);
void create_mutex(t_infos *infos);
int main(int argc, char **argv);
//parsing
int ft_atol(const char *str);
bool	is_valid_nbr(char *str);
bool	parsing(int argc, char **argv);

#endif