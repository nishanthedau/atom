# atom
Atom Simulation to understand OpenGL

# to compile 
g++ main.cpp \
-I/opt/homebrew/include \
-L/opt/homebrew/lib \
-lglfw -lGLEW \
-framework OpenGL \
-framework Cocoa \
-framework IOKit \
-framework CoreVideo \
-o app