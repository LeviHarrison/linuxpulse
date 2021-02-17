# LinuxPulse

When I switched over to Linux, the one program that I was missing was WhatPulse, an input statistics tracking application and my prefered metric of productivity. LinuxPulse aims to be replacement for Whatpulse, written for Linux.

Currently, LinuxPulse only records keypresses, put I plan to add more input methods in the feature.

## Viewing Statistics

Your total (all time) key count is stored in the `/linuxpulse-count.txt` file, and the program reads from that on startup.

Although it would be nice to have a GUI, I haven't got around to implementing one yet, and I don't really plan to. Instead, I've made LinuxPulse a [Prometheus exporter](https://prometheus.io/docs/introduction/overview/#architecture), and the statistics can be accessed at `localhost:9090/metrics`. From there you can direct a [Prometheus instance](https://prometheus.io/docs/introduction/first_steps/) at it, and query in something like [Grafana](https://grafana.com/oss/grafana/).

## Setup

- Download the latest release or clone the source code and build it yourself (`make build`).
- Move the binary to `/usr/bin` or your prefered executable location.
- Find what input buffer your keyboard writes to.
- Run `sudo linuxpulse event6`, `event6` being the input buffer my keyboard writes to. It defaults to `event0` if no buffer is specified.

### Running on Startup

- Clone the repository and open the `linuxpulse.service` file.
- Change the start command so that it specifies your input buffer (ex. `sudo /usr/bin/linuxpulse event2`).
- Run `make install-service` to install and start the service.

### Dependencies

- [libprom](https://github.com/digitalocean/prometheus-client-c/releases) and [libpromhttp](https://github.com/digitalocean/prometheus-client-c/releases).
