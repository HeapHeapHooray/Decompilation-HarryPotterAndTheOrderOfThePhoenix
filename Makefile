CXX = zig c++
TARGET = harry.potter.exe
SRC = harry-potter.cpp
# Target 32-bit Windows (x86) and use the Windows GUI subsystem
CXXFLAGS = -target x86-windows -mwindows -lgdi32 -luser32 -lkernel32 -lwinmm -L. -lmsvcr80

all: $(TARGET)

$(TARGET): $(SRC) msvcr80.lib
	$(CXX) $(CXXFLAGS) -o $@ $<

msvcr80.lib: msvcr80.def
	zig dlltool -m i386 -d msvcr80.def -l msvcr80.lib

clean:
	rm -f $(TARGET)
