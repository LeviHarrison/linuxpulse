#include <errno.h>
#include <fcntl.h>
#include <linux/input-event-codes.h>
#include <linux/input.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <time.h>
#include <unistd.h>

int main() {
  printf("Starting\n");

  int input =
      open("/dev/input/by-id/usb-KBDfans_KBD8X-MKII_0-event-kbd", O_RDONLY);
  if (input == -1) {
    printf("Error opening input buffer with error code %d\n", errno);
    return 1;
  }

  FILE *save = fopen("./count.txt", "r");

  int count = 0;
  if (fscanf(save, "%d", &count) == -1) {
    printf("Error doing initial read of count file with code %d\n", errno);
    return 1;
  }

  struct input_event event;
  time_t last = 0;

  while (1) {
    if (read(input, &event, sizeof(event)) == -1) {
      printf("Error reading from input buffer error with code %d\n", errno);
      return 1;
    }

    if (event.type == EV_KEY && event.value == 1) {
      printf("Key pressed %i %lu\n", count, event.time.tv_sec - last);
      last = event.time.tv_sec;
      count++;
    }
  }

  return 0;
}
