#include <errno.h>
#include <fcntl.h>
#include <linux/input-event-codes.h>
#include <linux/input.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <time.h>
#include <unistd.h>

const char default_input[] = "event0";

int main(int argc, char *argv[]) {
  char device[] = "/dev/input/";
  if (argc > 1) {
    strcat(device, argv[1]);
    printf("Using device %s\n", device);
  } else {
    strcat(device, default_input);
    printf("Using default device %s\n", device);
  }

  int input = open(device, O_RDONLY);
  if (input == -1) {
    printf("Error opening input buffer with error code %d\n", errno);
    return 1;
  }

  FILE *save = fopen("./count.txt", "a");

  fseek(save, 0, SEEK_END);
  long int size = ftell(save);
  if (size == -1) {
    printf("Error finding size of count file with code %d\n", errno);
    return 1;
  }

  int count = 0;
  if (size != 0) {
    if (fscanf(save, "%d", &count) == -1) {
      printf("Error doing initial read of count file with code %d\n", errno);
      return 1;
    }
  }

  struct input_event event;

  printf("Starting\n");
  while (1) {
    if (read(input, &event, sizeof(event)) == -1) {
      printf("Error reading from input buffer error with code %d\n", errno);
      return 1;
    }

    if (event.type == EV_KEY && event.value == 1) {
      count++;
      printf("Key pressed %i\n", count);
    }
  }

  return 0;
}
