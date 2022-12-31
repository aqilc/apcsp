const p = new Project("cdungeon");
p.addIncludeDir("./deps/include");
p.addFiles("main.c");
p.addFiles(
	"deps/2dgraphics.c",
	"deps/futil.c",
	"deps/glapi.c",
	"deps/hash.c",
	"deps/hashfunc.c",
	"deps/spng.c",
	"deps/util.c",
);
p.addLib("deps/lib/BufferOverflowU");
p.addLib("deps/lib/freetype");
p.addLib("deps/lib/glew32s");
p.addLib("deps/lib/glfw3");
p.addLib("deps/lib/zlib");
p.addLib("shell32");
p.addLib("Gdi32");
p.addLib("user32");
p.addLib("opengl32");
resolve(p);