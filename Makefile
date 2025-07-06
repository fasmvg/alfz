all:
	gcc main.c -o alfz

install:
	gcc main.c -o alfz
	sudo mv alfz /usr/bin/

uninstall:
	sudo rm -rf /usr/bin/alfz

clean:
	rm -rf alfz
