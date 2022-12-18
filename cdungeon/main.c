

// GLEW, for opengl functions
#define GLEW_STATIC
#include <GL/glew.h>

// Window management
#include <GLFW/glfw3.h>

// My custom graphics lib :3
#include "2dgraphics.h"

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

gamestate g = { .width = 640, .height = 480 };

bool pressed = false;
pvec pressplace;
struct { double x, y; bool pressed; } mouse;


double frameaccum = 0;
char framerate[12];

// struct player {
  
// };
// struct player p = {0};

struct button {
  bool finishedpressing;
  bool pressing;
  union vec size;
  union vec coords;
  char* text;
  int textsize;
};
struct button* buttons = NULL;

int main(void) {

  /* Initialize the library */
  if (!glfwInit())
    return -1;
  
  // GLFW hints
  // glfwWindowHint(GLFW_DECORATED, GL_FALSE);
  // glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GL_TRUE);
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
  
  /* Create a windowed mode window and its OpenGL context */
  GLFWwindow* window = glfwCreateWindow(g.width, g.height, "Hello World", NULL, NULL);
  if (!window) {
    puts("couldn't initialize window???");
    glfwTerminate(); return -1; }
    
  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  
  // Set the framerate to the framerate of the screen, basically 60fps.
  // glfwSwapInterval(1);
  
  // Initialize GLEW so we can reference OpenGL functions.
  if(glewInit()/* != GLEW_OK */) {
    printf("error with initializing glew");
    glfwTerminate(); return -1; }

  // Initializes text shaders and context
  glinitgraphics();
  double start = glfwGetTime();
#ifdef _DEBUG
  typeface* font = loadfont("D:\\projects\\rust\\apcsp\\cdungeon\\Roboto-Medium.ttf");
#else
  typeface* font = loadfont("./Roboto-Medium.ttf");
#endif
  printf("%.3fs to load fonts\n", glfwGetTime() - start);
  doneloadingfonts();

  // Sets the coordinate system to screen 1:1 pixel mapping
  coords_screen();

  // GLFW input callbacks
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  glfwSetCursorPosCallback(window, cursor_position_callback);
  glfwSetKeyCallback(window, key_callback);

#ifdef _DEBUG
  spritesheet* player = loadss("d:/rust/apcsp/cdungeon/opengameart/DawnLike/Characters/Player0.png", 16, 16);
  spritesheet* terrain = loadss("d:/rust/apcsp/cdungeon/opengameart/DawnLike/Objects/Floor.png", 16, 16);
#else
  spritesheet* player = loadss("./opengameart/DawnLike/Characters/Player0.png", 16, 16);
  spritesheet* terrain = loadss("./opengameart/DawnLike/Objects/Floor.png", 16, 16);
#endif

  
  while(!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Framerate stuff
    g.delta = glfwGetTime() - g.last;
    g.last = glfwGetTime();
    g.frames ++;
    frameaccum += 1.0/g.delta;

    // If there have been more than 100 accumulated frames, reset the accumulation and update framecount
    if(g.frames % 100 == 0) {
      snprintf(framerate, sizeof(framerate), "%.2f fps", frameaccum/100);
      frameaccum = 0;
    }

    sprite(player, 0, 0, 50, 50, 32, 32);
    sprite(terrain, 0, 0, 100, 50, 32, 32);

    fill(.5f, .5f, .5f, 1.0f);
    tsiz(20);
    text(framerate, g.width - 130, g.height - 10);
    
    draw();
    //glfwSetWindowShouldClose(window, 1);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  return 0;
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

