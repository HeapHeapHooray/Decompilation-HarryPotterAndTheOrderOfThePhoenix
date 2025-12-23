CXX = zig c++
TARGET = harry.potter.exe
SRC = harry-potter.cpp
# Target 32-bit Windows (x86) and use the Windows GUI subsystem
CXXFLAGS = -target x86-windows -mwindows -lgdi32 -luser32 -lkernel32

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)
