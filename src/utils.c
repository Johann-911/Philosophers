/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:53:03 by jtoumani          #+#    #+#             */
/*   Updated: 2025/08/01 16:32:05 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool watchdog(t_infos *infos)
{
    int i = 0;
    long current_time;
    long time_since_meal;
    
    while (i < infos->number_of_philos)
    {
        pthread_mutex_lock(&infos->death_mutex);
        current_time = get_current_time(infos);
        time_since_meal = current_time - infos->philos[i].last_meal_time;
        if (time_since_meal > infos->time_to_die && !infos->sim_end)
        {
            infos->sim_end = true;
            pthread_mutex_unlock(&infos->death_mutex);

            printf("%ld %d died\n", get_current_time(infos), i+1);
            return (true);
        }
        pthread_mutex_unlock(&infos->death_mutex);
        i++;
    }
    return (false);
}


void print_status(t_philo *philo, char *status)
{
    long current_time;
    
    current_time = get_current_time(philo->infos);
    pthread_mutex_lock(&philo->infos->death_mutex);
    if (philo->infos->sim_end)
    {
        pthread_mutex_unlock(&philo->infos->death_mutex);
        return;
    }
    pthread_mutex_unlock(&philo->infos->death_mutex);
    pthread_mutex_lock(&philo->infos->print_mutex);
    printf("%ld %d %s\n", current_time, philo->philo_id, status);
    pthread_mutex_unlock(&philo->infos->print_mutex); 
}
   
void cleanup(t_infos *infos)
{
	int i;
	i = 0;
	while (i < infos->number_of_philos)
    {
        pthread_join(infos->philos[i].thread, NULL);
        i++;
    }
	i = 0;
	while (i < infos->number_of_philos)
    {
        pthread_mutex_destroy(&infos->forks[i]);
        i++;
    }
	pthread_mutex_destroy(&infos->print_mutex);
    pthread_mutex_destroy(&infos->death_mutex);
	free(infos->forks);
    free(infos->philos);
}
long get_current_time(t_infos *infos)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL))
        return(printf("byebye\n"), -1);
    return((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000) - infos->start_time);
}

void custom_sleep(long ms, t_philo *philo)
{
    long start;
	start = get_current_time(philo->infos);
    while (get_current_time(philo->infos) - start < ms)
    {
        usleep(100);
        pthread_mutex_lock(&philo->infos->death_mutex);
        if(philo->infos->sim_end)
        {
            pthread_mutex_unlock(&philo->infos->death_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->infos->death_mutex);    
    }
}


//START MUTEX???