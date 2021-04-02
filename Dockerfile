FROM ubuntu:latest

USER root

RUN  apt-get update \
  && apt-get install -y wget make clang libmicrohttpd-dev \
  && rm -rf /var/lib/apt/lists/*

RUN wget https://github.com/digitalocean/prometheus-client-c/releases/download/v0.1.3/libprom-dev-0.1.3-Linux.deb
RUN apt install ./libprom-dev-0.1.3-Linux.deb
RUN wget https://github.com/digitalocean/prometheus-client-c/releases/download/v0.1.3/libpromhttp-dev-0.1.3-Linux.deb
RUN apt install ./libpromhttp-dev-0.1.3-Linux.deb

COPY . .

RUN make build

ENTRYPOINT [ "./linuxpulse" ]
