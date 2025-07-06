default:
	g++ src/*.cpp -o PointStick.exe -O2 -Wall -Wno-missing-braces -I include/ lib/libraylib.a -lwinmm -lgdi32 -lopengl32  && PointStick