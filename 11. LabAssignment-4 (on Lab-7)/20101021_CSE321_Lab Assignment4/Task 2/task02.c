#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h> // extra add korsi
#include <time.h> // extra add korsi

/*
This program provides a possible solution using mutex and semaphore.
use 5 Farmers and 5 ShopOwners to demonstrate the solution.
*/

#define MaxCrops 5 // Maximum crops a Farmer can produce or a Shpoowner can take
#define warehouseSize 5 // Size of the warehouse

sem_t empty;
sem_t full;
int in = 0;
int out = 0;

char crops[warehouseSize]={'R','W','P','S','M'}; //indicating room for different crops
char warehouse[warehouseSize]={'N','N','N','N','N'}; //initially all the room is empty
pthread_mutex_t mutex;

void *Farmer(void *far)
{
   /*
   1.Farmer harvest crops and put them in particular room. For example, room 0 for Rice(R).
   2.use mutex and semaphore for critical section.
   3.print which Farmer is keeping which crops in which room inside the critical section.
   4.print the whole warehouse buffer outside of the critical section
   */

    // farmer mane task01 er producer
    for(int i = 0; i < MaxCrops; i++){
        sem_wait(&empty); //wait korbo warehouse (buffer) jodi full thake
        pthread_mutex_lock(&mutex); // mutex ta lock korte

        // buffer e crops (item) insert korte
        warehouse[in]=crops[in];
        printf("Farmer %d: Insert crops %c at %d\n", *((int *)far), warehouse[in], in); 

        // insert index update aar dorkare wrap around korte 
        in = (in + 1) % warehouseSize;

        pthread_mutex_unlock(&mutex); // mutex ta unlock korte
        sem_post(&full); // warehouse (buffer) je aar empty na sheta signal korte
    }
    
    printf("Farmer%d:", *((int *)far));
    for(int g=0; g<warehouseSize; g++){
        printf(" %c", warehouse[g]);
    }
    printf("\n");
}

void *ShopOwner(void *sho){
    /*
    1.Shop owner takes crops and makes that particular room empty.
    2.use mutex and semaphore for critical section.
    3.print which shop owner is taking which crops from which room inside the critical section.
    4.print the whole warehouse buffer outside of the critical section
    */

   // Shopowner mane task01 er consumer
    for(int i = 0; i < MaxCrops; i++){
        sem_wait(&full); //wait korbo warehouse (buffer) jodi empty thake
        pthread_mutex_lock(&mutex); // mutex ta lock korte

         // buffer e crops (item) remove korte
        char item = warehouse[out];
        printf("Shop Owner %d: Remove crops %c from %d\n", *((int *)sho), item, out);
        warehouse[out] = 'N'; // slot ta N e reset korte
        
        // out index update aar dorkare wrap around korte 
        out = (out + 1) % warehouseSize;
        
        pthread_mutex_unlock(&mutex); // mutex ta unlock korte
        sem_post(&empty); // warehouse (buffer) je aar full na sheta signal korte
    }
    
    printf("ShopOwner%d:", *((int *)sho));
    for(int w=0; w<warehouseSize; w++){
        printf(" %c", warehouse[w]);
    }
    
    printf("\n");
}

int main()
{   
    /*initializing thread,mutex,semaphore
    */
    pthread_t Far[5], Sho[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, warehouseSize); //when the warehouse is full thread will wait
    sem_init(&full, 0, 0); //when the warehouse is empty thread will wait
    int a[5] = {1, 2, 3, 4, 5}; //Just used for numbering the Farmer and ShopOwner

    /*create 5 thread for Farmer 5 thread for ShopOwner
    -------------------------------------------------
    -------------------------------------------------
    */

   // Farmer (producer) thread create korte 
    for(int i=0; i<5; i++){
        pthread_create(&Far[i], NULL, (void *)Farmer, (void *)&a[i]);
    }
    
    // ShopOwner (consumer) thread create korte
    for(int i=0; i<5; i++){
        pthread_create(&Sho[i], NULL, (void *)ShopOwner, (void *)&a[i]);
    }
    
    // shob Farmer thread jate shesh hoi shejonno wait kora hochche
    for(int i=0; i<5; i++){
        pthread_join(Far[i], NULL);
    }
    
    // shob ShopOwnner(producer) thread jate shesh hoi shejonno wait kora hochche
    for(int i=0; i<5; i++){
        pthread_join(Sho[i], NULL);
    }
    
    //  Closing or destroying mutex and semaphore
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    
    return 0;
}

// 20101021 // Rodsy