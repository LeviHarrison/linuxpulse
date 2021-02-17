default: build run

build:
	clang main.c metrics.c -o linuxpulse -lpthread -lprom -lpromhttp -lmicrohttpd

run:
	sudo ./linuxpulse

install:
	sudo cp ./linuxpulse /usr/bin/linuxpulse

install-service:
	sudo cp ./linuxpulse.service /etc/systemd/system/linuxpulse.service
	sudo systemctl daemon-reload
	sudo systemctl enable linuxpulse.service
	sudo systemctl start linuxpulse.service
	systemctl status linuxpulse.service
