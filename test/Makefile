target = test

LDFLAGS += -lpthread

all: $(target)

test : test.o
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm ioctl_test
