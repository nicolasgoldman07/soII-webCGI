CC=gcc
CFLAGS=-Werror​ -Wall -pedantic

all:
	$(CC) recursos.c -o recursos.cgi
	$(CC) goes16.c -o goes16.cgi

clean:
	rm *.cgi
cppcheck:
	cppcheck --enable=all  --suppress=missingIncludeSystem *.c 2>cpp_check.txt
