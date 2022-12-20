

double start;
typeface* font;
spritesheet *imgp;
spritesheet *terrain;

int scene;
void (*scenes[4])();

struct {
  int x, y; int vx, vy;
  int dir, state;
  spritesheet* sprite;
} player = {0};
bool playermoving = false;
union vec camera = {0, 0};
// camera width and height are the window width and height defined in g.width and g.height

struct {
  img mainvil;
  img startvil;
  img map;
} images = {0};



int blocksize = 64;

bool hovering = false;

draw_map(img map);
draw_player();
main_town();
starting_town();
main_map();

init() {

  // Initializes text shaders and context
  glinitgraphics();

  // Loads all images and text files
  start = glfwGetTime();
  // font = loadfont("./Roboto-Medium.ttf");
  doneloadingfonts();
  // player.img = loadpixelart("./opengameart/DawnLike/Characters/Player0.png");
  images.mainvil = loadpixelart("./maps/Main Town.png");
  images.startvil = loadpixelart("./maps/Starting Town.png");
  images.map = loadpixelart("./maps/Main Map.png");
  player.sprite = createss(loadpixelart("./opengameart/DawnLike/Commissions/Warrior.png"), 16, 16);
  printf("%.3fs to load images\n", glfwGetTime() - start);

  scenes[0] = main_town;
}

drawgame() {
  hovering = false;
  fill(0, 0, 0, 0);

  scenes[scene]();
  draw_player();

  if(playermoving && g.frames % 8 == 0) {
    if (player.state == 3) player.state = -1; 
    player.state ++; player.x += player.vx; player.y += player.vy; }
  
  // fill(.5f, .5f, .5f, 1.0f);
  // tsiz(20);
  // text(framerate, g.width - 130, g.height - 10);
}



draw_player() {
  sprite(player.sprite, player.state, player.dir, player.x, player.y, blocksize, blocksize); }
draw_map(img map) {
  image(map, camera.x, camera.y, imgd(map)->size.w * blocksize / 16, imgd(map)->size.h * blocksize / 16); }




starting_town() {
  draw_map(images.startvil);
}

main_town() {
  draw_map(images.mainvil);
}

main_map() {
  draw_map(images.map);
}



button(int x, int y, int w, int h) {
  
}



void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
  if (action == GLFW_PRESS)
    if(button == GLFW_MOUSE_BUTTON_RIGHT)
      glfwSetWindowShouldClose(window, 1);
    else { pressed = true; glfwGetCursorPos(window, &pressplace.x, &pressplace.y); }
  else pressed = false;
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
#define PLAYERSPEED 20
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if(action == GLFW_RELEASE) { playermoving = false; player.state = player.vx = player.vy = 0; return; }
  if(key == GLFW_KEY_ESCAPE) glfwWindowShouldClose(1);
  if (mods) return;
  playermoving = true;
  switch (key) {
    case GLFW_KEY_RIGHT:
      player.vx = PLAYERSPEED;
      player.dir = 2;
      break;
    case GLFW_KEY_LEFT:
      player.vx = -PLAYERSPEED;
      player.dir = 1;
      break;
    case GLFW_KEY_DOWN:
      player.vy = PLAYERSPEED;
      player.dir = 0;
      break;
    case GLFW_KEY_UP:
      player.vy = -PLAYERSPEED;
      player.dir = 3;
      break;
    default: playermoving = false; player.state = 0;
  }
  if(player.dir != lastdir) player.state = 0;
  lastdir = player.dir;
}

