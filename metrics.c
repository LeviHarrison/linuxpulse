#include "metrics.h"
#include "prom.h"
#include "promhttp.h"
#include <microhttpd.h>
#include <prom_collector_registry.h>
#include <prom_counter.h>
#include <stdio.h>

prom_counter_t *key_count;

int port = 9009;

void metrics_init(void) {
  if (prom_collector_registry_default_init() != 0) {
    printf("Error starting Prometheus collector\n");
    exit(1);
  }

  promhttp_set_active_collector_registry(NULL);
  if (promhttp_start_daemon(MHD_USE_SELECT_INTERNALLY, port, NULL, NULL) ==
      NULL) {
    printf("Error starting metrics daemon\n");
    exit(1);
  }
}

void key_count_init(int count) {
  key_count = prom_collector_registry_must_register_metric(
      prom_counter_new("key_count", "The number of keys pressed", 0, NULL));
  key_count_add(count);
}

void key_count_add(int count) {
  if (prom_counter_add(key_count, count, NULL) != 0) {
    printf("Error updating count\n");
    exit(1);
  }
}
