#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
sem_t chopsticks[5];
int *philosopher(void *arg)
{
    int id=*(int*)arg;
    while(1)
    {
        sem_wait(&chopsticks[id%5]);
        sem_wait(&chopsticks[(id+1)%5]);
        printf("Philosopher %d is eating...",id);
        sem_post(&chopsticks[id%5]);
        sem_post(&chopsticks[(id+1)%5]);
        printf("Philosopher %d is thinking...",id);
        usleep(rand()%1000000);
    }
}
int main()
{
    pthread_t philosophers[5];
    for(int i=0;i<5;i++)
        sem_init(&chopsticks[i],0,1);
    for(int i=0;i<5;i++)
        pthread_create(&philosophers[i],NULL,philosopher,&i);
    for(int i=0;i<5;i++)
        pthread_join(philosophers[i],NULL);
    for(int i=0;i<5;i++)
        sem_destroy(&chopsticks[i]);
}
