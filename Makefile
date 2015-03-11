all: convert

convert: convert.o
	$(CC) -o $@ $^ $(LDFLAGS)
