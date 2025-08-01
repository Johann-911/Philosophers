/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:43:08 by jtoumani          #+#    #+#             */
/*   Updated: 2025/07/31 18:21:08 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int main(int argc, char **argv)
{
	t_infos infos;
    // t_philo philos;
	if(!parsing(argc, argv))
		return 1;
			
	init_infos(argc, argv, &infos);
	create_mutex(&infos);
    create_threads(&infos);
    while (1)
    {
        if (watchdog(&infos))
        {
            // printf("Simulation ended: philosopher died\n");
            break;
        }
        // if (infos.max_eat != -1 && enough_burger(&infos))
        // {
        //     printf("Simulation ended: all philosophers ate enough\n");
        //     break;
        // }
        usleep(500);
    }
	cleanup(&infos);
	return 0;
}
