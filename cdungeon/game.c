#include <2dgraphics.h>
#include <GLFW/glfw3.h>
#include <stddef.h>
#include "collisions.c"
#include <stdarg.h>
#define PLAYERSPEED 4



bool pressed = false;
pvec pressplace;
struct { double x, y; bool pressed; } mouse;


int blocksize = 64;

int scene;
void (*scenes[4])();

struct {
	int x, y, w, h; int vx, vy;
	int dir, state;
	spritesheet* sprite;
} player = {.x = 15 * 64, .y = 5 * 64, .w = 58, .h = 62};
union vec camera = {0, 0};
// camera width and height are the window width and height defined in g.width and g.height

struct {
	img mainvil;
	img startvil;
	img map;
	img dungeon1;
} images = {0};

struct {
	spritesheet* f;
	spritesheet* s;
	typeface* font;
} ui;


struct {
	int x, y, w, h;
} bounds;

u8* curcol = NULL;
int collen = 0;
int colw = 0;

typeface* font;


bool hovering = false;

void draw_map(img map);
void draw_player();
void main_town();
void starting_town();
void main_map();
void dungeon1();
void killplayer();

void init() {

	// Initializes text shaders and context
	loadglgraphics();

	// Loads all images and text files
	double start = glfwGetTime();
//  font = loadfont("./Roboto-Medium.ttf");
	font = loadfont("./DawnLike/GUI/SDS_8x8.ttf");
	doneloadingfonts();
	// player.img = loadpixelart("./opengameart/DawnLike/Characters/Player0.png");
	images.mainvil = loadpixelart("./maps/Main Town.png");
	images.startvil = loadpixelart("./maps/Starting Town.png");
	images.map = loadpixelart("./maps/Main Map.png");
	// images.dungeon1 = loadpixelart("./maps/Dungeon1.png");
	
	player.sprite = createss(loadpixelart("./DawnLike/Commissions/Warrior.png"), 16, 16);
	ui.f = createss(loadpixelart("./DawnLike/GUI/GUI0.png"), 16, 16);
	ui.s = createss(loadpixelart("./DawnLike/GUI/GUI1.png"), 16, 16);
	printf("%.3fs to load images\n", glfwGetTime() - start);

	scenes[0] = starting_town;
	scenes[1] = main_town;
	scenes[2] = main_map;
	scenes[3] = dungeon1;
}

void drawgame() {
	hovering = false;
	fill(0, 0, 0, 0);

	scenes[scene]();
	draw_player();

	// fill(1, 1, 1, 1);
	// tsiz(20);
	// text(framerate, g.width - 200, g.height - 10);
}

union xy {
	struct {
		u16 x, y;
	};
	u32 xy;
};
// Resolve X and Y according to blocksize
inline union xy rxy(u16 x, u16 y) { return (union xy) { x / blocksize, y / blocksize }; }
inline u8 getblock(u32 x, u32 y) {
	size_t ind = y * colw + x;
	if(ind > collen) return 1;
	return curcol[ind];
}

// --------------- DRAWS THE PLAYER + PHYSICS --------------- //

void draw_player() {
	bool xv = false;
	bool yv = false;

	if (player.vx) {
		player.dir = player.vx > 0 ? 2 : 1;
		player.x += player.vx;
		xv = true;

		int pbx = (player.x / blocksize);
		int pby = (player.y / blocksize);
		int pbax = pbx * blocksize;

		if(getblock(pbx, pby) == 1 || getblock(pbx, (player.y + player.h) / blocksize) == 1)
			player.x = pbax + blocksize + 1, xv = false;
		else if(getblock((player.x + player.w) / blocksize, pby) == 1 || getblock((player.x + player.w) / blocksize, (player.y + player.h) / blocksize) == 1)
			player.x = pbax + blocksize - player.w - 1, xv = false;
	}

	if (player.vy) {
		player.dir = player.vy > 0 ? 0 : 3;
		player.y += player.vy;
		yv = true;

		int pbx = (player.x / blocksize);
		int pby = (player.y / blocksize);
		int pbay = pby * blocksize;

		if(getblock(pbx, pby) == 1 || getblock((player.x + player.w) / blocksize, pby) == 1)
			player.y = pbay + blocksize + 1, yv = false;
		else if(getblock(pbx, (player.y + player.h) / blocksize) == 1 || getblock((player.x + player.w) / blocksize, (player.y + player.h) / blocksize) == 1)
			player.y = pbay + blocksize - player.h - 1, yv = false;
	}

	// Player movement
	if((xv || yv) && g.frames % 8 == 0) {
		if (player.state == 3) player.state = -1;
		player.state ++;
	}
	
	fill(1, 1, 1, 1);
	for(int i = 0; i < 3; i ++)
	  for(int j = 0; j < 3; j++){
			int x = player.x / blocksize + i;
			int y = player.y / blocksize + j;
			fill(0, 0, 0, .2);
			if(getblock(x, y) == 1) {
				rect(x * blocksize + camera.x, y * blocksize + camera.y, blocksize, blocksize);
			}
			rect(blocksize * x + camera.x + blocksize, blocksize * y + camera.y + blocksize, -20, 2);
			rect(blocksize * x + camera.x + blocksize, blocksize * y + camera.y + blocksize, 2, -20);
	    char str[6] = {0};
			char str2[15] = {0};
	    snprintf(str, 6, "%d", x + y * colw);
			sprintf(str2, "X:%d\nY:%d", x, y);
			tsiz(12);
			fill(0, 0, 0, .6);
			text(str, blocksize * x + camera.x - 10 + blocksize / 2, blocksize * y + camera.y + blocksize / 2 - 10);
			text(getblock(x, y) == 1 ? "1" : "0", blocksize * x + camera.x - 10 + blocksize / 2, blocksize * y + camera.y + blocksize / 2 + 5);
			text(str2, blocksize * x + camera.x - 10 + blocksize / 2, blocksize * y + camera.y + blocksize / 2 + 17);
		}

	// Shorthands for the player bounds
	int x = bounds.x;
	int y = bounds.y;
	int w = bounds.w;
	int h = bounds.h;

	// Player bounds according to the scene/map
	if(player.x < x) player.x = x;
	if(player.y < y) player.y = y;
	if(player.x + player.w > w) player.x = w - player.w;
	if(player.y + player.h > h) player.y = h - player.h;

	// Determines where the background(the map) and the player are on the screen
	int width = g.width;
	int height = g.height;
	int middlex = width / 2;
	int middley = height / 2;
	camera.x = min(0, min(x, -player.x + middlex));
	camera.y = min(0, min(y, -player.y + middley));
	if(camera.x - player.x < middlex)
		middlex = player.x + camera.x;
	if(camera.y - player.y < middley)
		middley = player.y + camera.y;

	fill(0, 0, 0, 0);
	sprite(player.sprite, player.state, player.dir, middlex - (blocksize - player.w) / 2,
		middley - (blocksize - player.h) / 2, blocksize, blocksize);
}


// --------------- UTILITY FUNCS --------------- //

void draw_map(img map) {
	image(map, camera.x, camera.y, imgd(map)->size.w * blocksize / 16, imgd(map)->size.h * blocksize / 16); }
void setbounds(int x, int y, int w, int h) { bounds.x = x; bounds.y = y; bounds.w = w; bounds.h = h; }


// bool includes(u32* arr, u32 len, u32 val) {
//   for(int i = 0; i < len; i ++)
//     if(arr[i] == val) return true;
//   return false;
// }

bool playeristouching(u32* arr, u32 len) {
	int x = player.x;
	int y = player.y;
	int w = player.w;
	int h = player.h;
	int dir = player.dir;
	for(int i = 0; i < len; i ++) {
		int bx = arr[i] % colw;
		int by = arr[i] / colw;
		int pbx = x / blocksize;
		int pby = y / blocksize;

		if     (dir == 2 && bx == pbx + 1 && by == pby) return true; // right dir
		else if(dir == 1 && bx == pbx - 1 && by == pby && player.x - pbx * blocksize < blocksize - player.w) return true; // left dir
		else if(dir == 3 && bx == pbx && by == pby - 1 && player.y - pby * blocksize < blocksize - player.h) return true; // up dir
		else if(dir == 0 && bx == pbx && by == pby + 1) return true; // down dir
	}
	return false;
}

// --------------- PROMPT STUFF --------------- //

struct {
	bool frameimg;
	bool closed;
	
	u32 lastframe;
	u32 startframe;
	u32 curtext;
	u32 textnum;
	u32 triy; // triangle for space, the animation where it goes up and down
	short* newlines;
	char** texts;
} pst = {0}; // prompt state
void prompt(char* txt, ...) {
	
	// If you turn away from the prompt no matter when, it automatically closes/resets
	if (g.frames != pst.lastframe + 1) {

		// Free every string used before:
		for(int t = 0; t < pst.textnum; t ++) free(pst.texts[t]);
		
		pst.startframe = g.frames;
		pst.curtext = 0;
		pst.frameimg = false;
		pst.closed = false;

		// We max out argument number at like 12 so we don't think spaces or anything are actually the number of arguments we specify
		char numargs = *txt;
		if (numargs > 12) numargs = 0;
		char** texts;
		short* newlines;

		// Malloc if first prompt, else realloc
		if(pst.lastframe == 0) {
			texts = malloc((numargs + 1) * sizeof(char*));
			newlines = malloc(sizeof(short) * (numargs + 1));
		} else {
			texts = realloc(pst.texts, (numargs + 1) * sizeof(char*));
			newlines = realloc(pst.newlines, sizeof(short) * (numargs + 1));
		}

		// Sets all ints to 0
		memset(newlines, 0, sizeof(short) * (numargs + 1));
		u32 textsind = 1;
		u32 i = 0;
		if (numargs > 0) {
			txt ++;
			
			// Goes through the rest of the strings and determines newline count and puts them in the heap
			va_list args;
			va_start(args, txt);
			for(int j = 0; j < numargs; j ++) {
				char* str = va_arg(args, char*);
				for(; str[i]; i ++) if(str[i] == '\n') newlines[textsind] ++;
				texts[textsind] = malloc(i + 1);
				strcpy(texts[textsind], str);
				i = 0;
				textsind ++;
			}
			va_end(args);
		}
		// Determines lengths and newline count, while putting the first arg in the heap
		for(;txt[i]; i++) if (txt[i] == '\n') newlines[0] ++;
		texts[0] = malloc(i + 1);
		strcpy(texts[0], txt);
		i = 0;

		pst.texts = texts;
		pst.newlines = newlines;
		pst.textnum = textsind;

		// printf("Prompt loaded: numtexts = %d\ntext: %s\n", textsind, pst.texts[0]);
	}
	pst.lastframe = g.frames;
	if (pst.closed) return;

	#define ANIMLEN 50
	#define PROMPTUPLEN 20

	// Switches the prompt ui image every 5 frames
	if(g.frames % 20 == 0) pst.frameimg = !pst.frameimg;
	spritesheet* ui_img = pst.frameimg ? ui.f : ui.s;

	// Prompt up animation
	int prompt_y = 20;
	if(g.frames - pst.startframe < PROMPTUPLEN)
		prompt_y -= blocksize * 4 - ((float) blocksize * 4 * ((float) (g.frames - pst.startframe) / PROMPTUPLEN));

	// Corners
	sprite(ui_img, 1, 7, 48, g.height - prompt_y - blocksize * 2, blocksize, blocksize);
	sprite(ui_img, 1, 9, 48, g.height - prompt_y - blocksize, blocksize, blocksize);
	sprite(ui_img, 3, 7, g.width - 48 - blocksize, g.height - prompt_y - blocksize * 2, blocksize, blocksize);
	sprite(ui_img, 3, 9, g.width - 48 - blocksize, g.height - prompt_y - blocksize, blocksize, blocksize);

	// Bottom and top
	sprite(ui_img, 2, 7, 48 + blocksize, g.height - prompt_y - blocksize * 2, blocksize * 9, blocksize);
	sprite(ui_img, 2, 9, 48 + blocksize, g.height - prompt_y - blocksize, blocksize * 9, blocksize);

	// Truncates the text so it looks like it's being typed out
	if(g.frames - pst.startframe <= PROMPTUPLEN) return;

	// Info for the text we're using for this prompt
	char* curtex = pst.texts[pst.curtext];
	u32 origlen = strlen(curtex);

	// Calculates the stage of the typing animation
	int framesintoanim = min(ANIMLEN - PROMPTUPLEN, g.frames - pst.startframe - PROMPTUPLEN);
	float animstage = (float) framesintoanim / ((float) ANIMLEN - (float) PROMPTUPLEN);

	// Clips off the text(by inserting nullchar), and stores the character that was taken out
	u32 texlen = origlen * animstage;
	char deletedletter = curtex[texlen];
	curtex[texlen] = '\0';

	// Draws the text
	fill(1, 1, 1, 1);
	tsiz(16);
	text(curtex, 48 + 24, g.height - 20 - blocksize * 2 + 18 + 24);

	// "SPACE" + triangle vvvvvvvvvvvvvvvv
	tsiz(12);
	text("SPACE", g.width - 48 - 120, g.height - 20 - 10 - 12);

	if(g.frames % 20 == 0) pst.triy ++;
	rect(g.width - 48 - 50,          g.height - 20 - 12 - 24 + (pst.triy % 3) * 2,     7 * 3, 12 / 4);
	rect(g.width - 48 - 50 + 10 - 7, g.height - 20 - 12 - 24 + (pst.triy % 3) * 2 + 3, 5 * 3, 12 / 4);
	rect(g.width - 48 - 50 + 10 - 4, g.height - 20 - 12 - 24 + (pst.triy % 3) * 2 + 6, 3 * 3, 12 / 4);
	rect(g.width - 48 - 50 + 10 - 1, g.height - 20 - 12 - 24 + (pst.triy % 3) * 2 + 8, 1 * 3, 12 / 4);
	
	// Subs the character back in
	if(texlen != origlen) curtex[texlen] = deletedletter;
}


// --------------- MAPS --------------- //


void starting_town() {
	// This code sets the bounds and sets the collision map for the current map, you'll see something like it at the start of every map function
	imagedata* img = imgd(images.startvil);
	setbounds(0, 0, img->size.w * blocksize / 16, img->size.h * blocksize / 16);
	curcol = (u8*) collisions.startvil; collen = 20 * 20; colw = 20;
	draw_map(images.startvil);

	if(playeristouching((u32[3]) { 273, 293, 313 }, 3))
		prompt("\4The world is in danger!", "There are 3 Evil Beings that might\ndestroy the world and kill millions!", "You must defeat them!",
		"Go to the main village, and talk to the\nguy in the house to the left of the\ntown hall.", "Good luck!");
	if(playeristouching((u32[5]) { 1, 2, 3, 4, 5 }, 5))
		scene = 2, player.x = 40 * blocksize, player.y = 30 * blocksize;
}

void main_town() {
	draw_map(images.mainvil);
}

void main_map() {
	imagedata* img = imgd(images.map);
	setbounds(0, 0, img->size.w * blocksize / 16, img->size.h * blocksize / 16);
	curcol = (u8*) collisions.mainmap; collen = 50 * 35; colw = 50;
	draw_map(images.map);
}

void dungeon1() {
	draw_map(images.dungeon1);
}

void button(int x, int y, int w, int h) {
	
}

void killplayer() {}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		pressed = true; glfwGetCursorPos(window, &pressplace.x, &pressplace.y);
	} else pressed = false;
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	mouse.x = xpos;
	mouse.y = ypos;
	if(pressed) {
		int wxpos, wypos;
		glfwGetWindowPos(window, &wxpos, &wypos);
		glfwSetWindowPos(window, (int) (xpos - pressplace.x) + wxpos, (int) (ypos - pressplace.y) + wypos);
	}
}

int lastdir;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if(action == GLFW_REPEAT) return;
	if(action == GLFW_RELEASE) {
		player.state = 0;
		if (key == GLFW_KEY_RIGHT && player.vx > 0)
			player.vx = 0;
		if (key == GLFW_KEY_LEFT && player.vx < 0)
			player.vx = 0;
		if (key == GLFW_KEY_DOWN && player.vy > 0)
			player.vy = 0;
		if (key == GLFW_KEY_UP && player.vy < 0)
			player.vy = 0;
		return;
	}
	if(key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, 1);
	if (mods) return;
	if(key == GLFW_KEY_SPACE && !pst.closed) {
		if(pst.curtext >= pst.textnum - 1) pst.closed = true;
		else pst.curtext ++, pst.startframe = g.frames - PROMPTUPLEN;
	}
	switch (key) {
		case GLFW_KEY_RIGHT:
			player.vx = PLAYERSPEED;
			break;
		case GLFW_KEY_LEFT:
			player.vx = -PLAYERSPEED;
			break;
		case GLFW_KEY_DOWN:
			player.vy = PLAYERSPEED;
			break;
		case GLFW_KEY_UP:
			player.vy = -PLAYERSPEED;
			break;
	}
	if(player.dir != lastdir) player.state = 0;
	lastdir = player.dir;
}

