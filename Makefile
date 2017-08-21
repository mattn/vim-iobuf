all : iobuf.dll iobuf_inject.dll

iobuf.dll : iobuf.c
	gcc -shared -o iobuf.dll iobuf.c

iobuf_inject.dll : iobuf_inject.c
	gcc -shared -o iobuf_inject.dll iobuf_inject.c

clean:
	-del iobuf_inject.dll iobuf.dll
