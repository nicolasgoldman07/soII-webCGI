CC=gcc
CFLAGS=-Werror​ -Wall -pedantic

all:
	$(CC) recursos.c -o recursos.cgi
	$(CC) goes16.c -o goes16.cgi
	$(CC) modules.c -o modules.cgi
	$(CC) newModule.c -o newModule.cgi
	$(CC) removeModule.c -o removeModule.cgi

clean:
	rm *.cgi
	# rm *.ko
cppcheck:
	cppcheck --enable=all  --suppress=missingIncludeSystem *.c 2>cpp_check.txt
