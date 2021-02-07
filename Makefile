default: run

build:
	clang main.c -o linuxpulse

start:
	sudo ./linuxpulse

run: build start
