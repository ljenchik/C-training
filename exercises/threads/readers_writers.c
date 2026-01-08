// Readers Writers Problem
// Suppose that a database is to be shared among several concurrent processes.
// Some of these processes may want only to read the database,
// whereas others may want to update (that is, to read and write) the database.
// We distinguish between these two types of processes by referring to the former
// as readers and to the latter as writers.
// Obviously, if two readers access the shared data simultaneously, no adverse effects will result.
// However, if a writer and some other process
// (either a reader or a writer) access the database simultaneously, chaos may ensue.
// To ensure that these difficulties do not arise, we require that the writers
// have exclusive access to the shared database while writing to the database.

#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NUM_READERS 2
#define NUM_WRITERS 2
#define FILE_NAME "text.txt"

sem_t writer_lock;             // Blocks readers when writer is waiting/writing
pthread_mutex_t reader_mutex;  // Protects reader_count

int reader_count = 0;

// Function to check if a file is empty
int is_file_empty(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    // Move the file pointer to the end to check its size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fclose(file);

    return (file_size == 0) ? 1 : 0; // Return 1 if empty, 0 if not
}

// Function to read content from a file
int read_from_file(const char *filename)
{
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    char line[100];
    int line_count = 0;
    while (fgets(line, sizeof(line), fptr) != NULL)
    {
        printf("%s", line);
        line_count++;
    }

    fclose(fptr);
    return line_count;
}

// Function to append data to a file
int append_to_file(const char *filename, const char *data)
{
    FILE *fptr = fopen(filename, "a");
    if (fptr == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    fprintf(fptr, "%s\n", data); // Add new line after data
    fclose(fptr);
    return 0;
}

// Reader thread function
void *readers(void *args)
{
    int id = *((int *)args);
    free(args);

    sleep(2);

    while (1) {

    printf("[READER %d] Thread started\n", id);

    pthread_mutex_lock(&reader_mutex); 
    reader_count++;
    if (reader_count == 1) {  
        sem_wait(&writer_lock);         
    }
    pthread_mutex_unlock(&reader_mutex);

    if (is_file_empty(FILE_NAME) != 0) {
        printf("[READER %d] File is empty, nothing to read.\n", id);
    } else {
        printf("[READER %d] Reading from file...\n", id);
        printf("===============================\n");
        
        int lines_read = read_from_file(FILE_NAME);
        
        printf("===============================\n");
        
        if (lines_read > 0) {
            printf("[READER %d] ✓ Successfully read %d lines from file\n", id, lines_read);
        } else if (lines_read == 0) {
            printf("[READER %d] ⚠️  File became empty during read\n", id);
        } else {
            printf("[READER %d] ✗ Error reading file\n", id);
        }
    }

    pthread_mutex_lock(&reader_mutex);  // Lock before modifying reader_count
    reader_count--;
    if (reader_count == 0) {
        sem_post(&writer_lock);          // Last reader unlocks writers
    }
    pthread_mutex_unlock(&reader_mutex);
    sleep(3);
}
    return NULL;
}

// Writer thread function
void *writers(void *args) {
    int id = *((int *)args);
    free(args);

    while(1) {
    printf("[WRITER %d] Thread started\n", id);
    sem_wait(&writer_lock);  
        
    printf("[WRITER %d] ✍️  Writing...\n", id);

    time_t now = time(NULL);
    
    char *time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0'; 

    char text[100];
    sprintf(text, "Writer %d wrote this at time %s", id, time_str);
    append_to_file(FILE_NAME, text);  
    printf("[WRITER %d] ✓ Done writing: %s\n", id, text);
        
    sem_post(&writer_lock);
        
    sleep(5);
    }
    return NULL;
}

int main(void)
{
    pthread_t readers_threads[NUM_READERS];
    pthread_t writers_threads[NUM_WRITERS];

    sem_init(&writer_lock, 0, 1);
    pthread_mutex_init(&reader_mutex, NULL);

    for (int i = 0; i < NUM_WRITERS; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&writers_threads[i], NULL, writers, id);
    }

    for (int i = 0; i < NUM_READERS; i++) {
            int *id = malloc(sizeof(int));
            *id = i + 1;
            pthread_create(&readers_threads[i], NULL, readers, id);
        }

    for (int i = 0; i < NUM_WRITERS; i++) {
            pthread_join(writers_threads[i], NULL);
        }

    for (int i = 0; i < NUM_READERS; i++) {
            pthread_join(readers_threads[i], NULL);
        }

    


    // Destroy the semaphore and mutex
    sem_destroy(&writer_lock);
    pthread_mutex_destroy(&reader_mutex);

    return 0;
}