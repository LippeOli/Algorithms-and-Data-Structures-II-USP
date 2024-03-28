CC = gcc
CFLAGS = -Wall -Wextra

SRCS = main.c graph.c
OBJS = $(SRCS:.c=.o)
EXEC = graphos

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(EXEC)
