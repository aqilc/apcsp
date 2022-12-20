

double start;
typeface* font;
img img1;
img img2;
img mainmap;
spritesheet *imgp;
spritesheet *terrain;

int scene;
void (*scenes[4])();

// union vec p

void init() {

  // Initializes text shaders and context
  glinitgraphics();

  // Loads all images and text files
  start = glfwGetTime();
  font = loadfont("./Roboto-Medium.ttf");
  doneloadingfonts();
  img1 = loadpixelart("./opengameart/DawnLike/Characters/Player0.png");
  img2 = loadpixelart("./opengameart/DawnLike/Objects/Floor.png");
  mainmap = loadpixelart("./maps/Main Town.png");
  printf("%.3fs to load images\n", glfwGetTime() - start);

  // Sets the coordinate system to screen 1:1 pixel mapping
  coords_screen();

  // GLFW input callbacks
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  glfwSetCursorPosCallback(window, cursor_position_callback);
  glfwSetKeyCallback(window, key_callback);

  imgp = createss(img1, 16, 16);
  terrain = createss(img2, 16, 16);
}

void drawgame() {
  fill(0, 0, 0, 0);
  image(mainmap, -500, -900, imgd(mainmap)->size.w * 4, imgd(mainmap)->size.h * 4);
  sprite(imgp, 0, 0, 50, 50, 64, 64);
  // image(img2, 0, 0, 200, 200);
  sprite(terrain, 2, 6, 100, 50, 32, 32);

  fill(.5f, .5f, .5f, 1.0f);
  tsiz(20);
  text(framerate, g.width - 130, g.height - 10);
}





void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
  // if (action == GLFW_PRESS)
  //   if(button == GLFW_MOUSE_BUTTON_RIGHT)
  //     glfwSetWindowShouldClose(window, 1);
  //   else { pressed = true; glfwGetCursorPos(window, &pressplace.x, &pressplace.y); }
  // else pressed = false;
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


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  
}

