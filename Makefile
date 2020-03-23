###
### Conpad Makefile
###

default:
	gcc -Wall -o conpad -O2 main.c

install:
	cp conpad /usr/local/bin/

uninstall:
	rm -i /usr/local/bin/conpad

clean:
	rm conpad
