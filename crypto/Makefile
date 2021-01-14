CC = clang
CFLAGS = -Wall -fPIC -shared -std = gnu17
LIBS = -L/usr/lib/quickjs/ -lssl -lcrypto -lquickjs 
DEFS = -DJS_SHARED_LIBRARY

all:
	$(CC) $(CFLAGS) $(DEFS) qjs-crypto.c -o qjs-crypto.so $(LIBS) 
