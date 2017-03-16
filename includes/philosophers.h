//
// Author: Marwane Khsime 
// Date: 2017-03-16 20:02:17 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-03-16 20:02:17
//

#ifndef _PHILOSOPHERS_H_
# define _PHILOSOPHERS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

typedef enum {
    UNDEFINED = (-true),
    EAT = 0,
    THINK = 1,
    SLEEP = 2
}      Action;

typedef struct      s_philo {
    size_t          id;
    Action          lastAction;
    pthread_t       thread;
    pthread_mutex_t chopstick;
}                   t_philo;

#endif /* _PHILOSOPHERS_H_ */