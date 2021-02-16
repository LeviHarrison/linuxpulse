default: build run

build:
	clang main.c -o linuxpulse -lpthread

run:
	sudo ./linuxpulse

install:
	sudo cp ./linuxpulse /usr/bin/linuxpulse
