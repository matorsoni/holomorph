# Direct compiler invocation
# Expects libglfw3.a static build in the -L path
clang ../src/main.c ../src/window.c ../deps/glad/src/gl.c -I../deps/glfw/include -I../deps/glad/include -L/home/msoni/dev/gamath/purebuild/ -lglfw3 -lm

