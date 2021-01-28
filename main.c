#include <errno.h>
#include <fcntl.h>
#include <linux/input-event-codes.h>
#include <linux/input.h>
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>

int main() {
  printf("Starting\n");

  int input =
      open("/dev/input/by-id/usb-KBDfans_KBD8X-MKII_0-event-kbd", O_RDONLY);
  if (input == -1) {
    printf("Error opening input buffer with error code %d\n", errno);
    return 1;
  }

  int save = open("./count.txt", O_CREAT | O_RDWR);
  if (save == -1) {
    printf("Error opening save file with error code %d\n", errno);
    return 1;
  }

  int count;
  if (read(input, &count, sizeof(int)) == -1) {
    printf("Error doing initial read of count file with code %d\n", errno);
    return 1;
  }

  struct input_event event;
  suseconds_t last = 0;

  while (1) {
    if (read(input, &event, sizeof(event)) == -1) {
      printf("Error reading from input buffer error with code %d\n", errno);
      return 1;
    }

    if (event.type == EV_KEY) {
      printf("Key pressed %lu\n", last);
      count++;
    }
  }

  return 0;
}
