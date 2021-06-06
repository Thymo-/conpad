###
### Conpad Makefile
###

.PHONY: install uninstall clean

conpad: conpad.c
	gcc -Wall -o conpad -O2 conpad.c

install:
	cp conpad /usr/local/bin/

uninstall:
	rm -i /usr/local/bin/conpad

clean:
	rm -f conpad
