CC = g++

CXXFLAGS = -std=c++17 -Wall

SRCDIR = src
INCLUDEDIR = include
OBJDIR = obj
BINDIR = bin
INSTALLDIR = /usr/local/bin

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

PROJECT_NAME = CChat

OPENSSL_LIBRARIES = -lssl -lcrypto

$(shell mkdir -p $(OBJDIR) $(BINDIR))

$(BINDIR)/$(PROJECT_NAME): $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $^ $(OPENSSL_LIBRARIES)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CXXFLAGS) -I$(INCLUDEDIR) -c -o $@ $<

clean:
	rm -rf $(OBJDIR)/*.o $(BINDIR)/$(PROJECT_NAME)

install: $(BINDIR)/$(PROJECT_NAME)
	cp $< $(INSTALLDIR)

uninstall:
	rm -f $(INSTALLDIR)/$(PROJECT_NAME)