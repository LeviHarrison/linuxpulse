default: build run

build:
	clang main.c -o linuxpulse

run:
	sudo ./linuxpulse
