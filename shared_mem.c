#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

void change_data(char* data) {
  printf("Would you like to change the data in the segment? (y/n)\t");
  char* response = calloc(sizeof(char), 201);
  fgets(response, 200, stdin);
  if (response[0] == 'y') {
    printf("Enter your new data below, then press enter:\n");
    fgets(data, 200, stdin);
  }
  free(response);
}

void delete_mem_segment(int shmid) {
  printf("Would you like to delete the memory segment? (y/n)\t");
  char* response = calloc(sizeof(char), 201);
  fgets(response, 200, stdin);
  if (response[0] == 'y') {
    int status = shmctl(shmid, IPC_RMID, NULL);
    if (status == -1) {
      printf("Error: %s\n", strerror(errno));
    }
    else {
      printf("Deleted!\n");
    }
  }
  free(response);
}

int main() {

  key_t key = 0x42069;

  int shmid;
  char* data;

  //  get mem segment
  //  shmget(key_t key, size_t size, int shmflg)
  //    ftok() key, or whatever tbh; size in bytes; 0 OR IPC_CREAT
  shmid = shmget(key, 201, 0644);
  if (shmid == -1) {
    printf("Segment not found. Will create mem segment at key %x\n", key);
    shmid = shmget(key, 201, 0644 | IPC_CREAT);
  }
  else {
    //  get pointer to segment
    //  shmat(shmid, void*, shmflg)
    //    void* should be 0; shmflg could be 0 OR SHM_RDONLY
    data = shmat(shmid, (void*)0, 0);
    printf("Data in segment:\n%s\n", data);
  }
  change_data(data);
  delete_mem_segment(shmid);
}
