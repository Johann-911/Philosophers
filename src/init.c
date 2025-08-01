/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:57:48 by jtoumani          #+#    #+#             */
/*   Updated: 2025/08/01 15:33:07 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_infos(int argc, char **argv, t_infos *infos)
{
	infos->number_of_philos = ft_atol(argv[1]);
	infos->time_to_die = ft_atol(argv[2]);
	infos->time_to_eat = ft_atol(argv[3]);
	infos->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		infos->max_eat = ft_atol(argv[5]);
	else
		infos->max_eat = 9999999;
	infos->forks = malloc(sizeof(pthread_mutex_t) * infos->number_of_philos);
	infos->philos = malloc(sizeof(t_philo) * infos->number_of_philos);
    pthread_mutex_init(&infos->print_mutex, NULL);
    pthread_mutex_init(&infos->death_mutex, NULL);
    infos->sim_end = false;
    infos->start_time = 0;
    infos->start_time = get_current_time(infos);
}

void create_threads(t_infos *infos)
{
    int i;
	i = 0;
    while (i < infos->number_of_philos) 
    {
        infos->philos[i].philo_id = i + 1;
        infos->philos[i].last_meal_time = get_current_time(infos);
        infos->philos[i].meal_counter = 0;
        infos->philos[i].left_fork = &infos->forks[i];
        infos->philos[i].right_fork = &infos->forks[(i + 1) % infos->number_of_philos];
        infos->philos[i].infos = infos;
        if(infos->number_of_philos == 1)
        {
            pthread_create(&infos->philos[i].thread, NULL, solo_mandem, &infos->philos[i]);
            break;
        }
        else
        {
            pthread_create(&infos->philos[i].thread, NULL, philo_routine, &infos->philos[i]);
        }
        i++;
    }
}

void create_mutex(t_infos *infos)
{
    int i;
    i = 0;
    while(i < infos->number_of_philos)
    {
        pthread_mutex_init(&infos->forks[i], NULL);
        i++;
    }	
}
