#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "compute.h"

/* Number of hits */
unsigned int hits;

/* Mutex Semaphore */
pthread_mutex_t mutex ;

/* Thread function */
void *thread_function(void *data)
{
    /* The input variable contains the number of points that the thread must
     * calculate */
    double x;
    double y;
    struct drand48_data randBufferX;
    struct drand48_data randBufferY;
    int points = *((int *)data);
    int contador=0;
    /* TODO: Implement the loop that obtains the random points and counts how
     * many of those lay within the circumference of radius 1 */

    for (int i = 0; i < points; i++)
    {
        // srand49_r(time(NULL),&randBufferX);
       // srand49_r(time(NULL),&randBufferY);
        drand48_r(&randBufferX,&x);
        drand48_r(&randBufferY,&y);
        /*
        x = rand() % 1001;
        y = rand() % 1001;
        */
        //calculasmo si nuestro punto excede a nuestro radio, para ello utilizamos pitagoras
        int h = (x * x) + (y * y);
        if (h <1)
        {
            contador++;
    
        }
     
    }

        pthread_mutex_lock(&mutex);
            hits = hits + contador;
            pthread_mutex_unlock(&mutex);
    /* TODO: Add the count to the global variable hits in mutual exclusion 
    
            pthread_mutex_lock(&mutex);
            hits = hits + points;
            pthread_mutex_unlock(&mutex);*/
    return NULL;
}

void compute(int npoints, int nthreads)
{
    
    int np= npoints;    //se vincula (?)
    int nPasar= npoints/nthreads;
    int resto=npoints % nthreads;
    npoints=(npoints-resto)/nthreads;
    pthread_mutex_init(&mutex,NULL);
    /* TODO: Erase the following line: */
    printf("compute(%d, %d)\n", npoints, nthreads);
    pthread_t thread_id[nthreads];
    
    /* TODO: Launch the threads that will count the points */
    for (int i = 0; i < nthreads; i++)
    {
       
        if(nthreads-1==i){
        int puntosf= npoints+resto;
        printf("\nmake thread");
        pthread_create(&thread_id[i], NULL, thread_function, &puntosf);
          pthread_join(thread_id[i], NULL);
        }else{
        printf("\nmake thread");
        pthread_create(&thread_id[i], NULL, thread_function, &npoints);
        pthread_join(thread_id[i], NULL);
        }
 
    }
     /* TODO: Wait for all threads to finish */
     
   /* for (int i = 0; i < nthreads; i++)
    {   printf("\n wait thread");
        pthread_join(thread_id[i], NULL);
    }*/

  /* TODO: Wait for all threads to finish; es la funcion pthread_join */   



    /* TODO: print the ratio of points that meet the criteria */
    npoints=npoints*nthreads+resto;
    printf("\nsolucion (%d, %d)\n", hits, npoints);
    printf("\npi : ");
    int nsec= hits;
    float pi= 4*((float)nsec/(float)npoints);
    printf("%.8f\n", pi);
    /* The following print string can be used to print the calculated value:
     * printf("%.8f\n", VALUE_OF_PI);
     * where VALUE_OF_PI is the floating-point value to be printed.
     */
   
}
