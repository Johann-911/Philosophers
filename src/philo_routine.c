/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:46:44 by jtoumani          #+#    #+#             */
/*   Updated: 2025/08/01 16:26:23 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->infos->death_mutex);
		if (philo->infos->sim_end)
		{
			pthread_mutex_unlock(&philo->infos->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->infos->death_mutex);
		takes_fork(philo);
		print_status(philo, "is eating");
		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal_time = get_current_time(philo->infos);
		pthread_mutex_unlock(&philo->meal_mutex);
		philo->meal_counter++;
		custom_sleep(philo->infos->time_to_eat, philo);
		release_fork(philo);
		print_status(philo, "is sleeping");
		custom_sleep(philo->infos->time_to_sleep, philo);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

void	takes_fork(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken left fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken right fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken right fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken left fork");
	}
}

void	release_fork(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

void	*solo_mandem(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->left_fork);
	philo->last_meal_time = get_current_time(philo->infos);
	print_status(philo, "has taken left fork");
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}
// void enough_burger(t_philo *philo)
// {
// 	int i;
// 	i = 0;
// 	while(i != (philo[i]->infos->max_eat))
// 	{
// 		pthread_mutex_lock(&philo->infos->death_mutex);

// 		if(philo->infos->max_eat)
// 		{	
// 			philo->infos->sim_end = true;
// 			pthread_mutex_unlock(&philo->infos->death_mutex);
			
// 		}
// 		i++;

// 	}
// }
// int is_philo_dead(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->infos->death_mutex);
// 	if (philo->infos->sim_end)
// 	{
// 		pthread_mutex_unlock(&philo->infos->death_mutex);
// 		return ;
// 	}
// 	pthread_mutex_unlock(&philo->infos->death_mutex);
// 	rand
// }