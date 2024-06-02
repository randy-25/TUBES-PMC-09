# Compiler
CC := gcc

# Directories
INCDIR := header
OBJDIR := obj

# Flags
CFLAGS := -I$(INCDIR)
LDFLAGS := -lxlsxio_read -lxlsxio_write

# Source files
SRCS := $(wildcard *.c)
OBJS := $(patsubst /%.c, $(OBJDIR)/%.o, $(SRCS))

# Output file
output: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o main

# $(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
# 	$(CC) $(CFLAGS) -c $< -o $@ 

# $(OBJDIR):
# 	mkdir -p $(OBJDIR)

clean:
	rm -rf main

