CC = gcc

default:
	$(CC) -o screenwatcher screen-watcher.c -lX11