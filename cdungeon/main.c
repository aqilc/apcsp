

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

gamestate g = { .width = 800, .height = 600 };


bool pressed = false;
pvec pressplace;
struct { double x, y; bool pressed; } mouse;

double frameaccum = 0;
char framerate[12];

GLFWwindow* window;

#include "game.c"

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
  window = glfwCreateWindow(g.width, g.height, "Hello World", NULL, NULL);
  if (!window) {
    puts("couldn't initialize window???");
    glfwTerminate(); return -1; }
    
  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  
  // Set the framerate to the framerate of the screen, basically 60fps.
  glfwSwapInterval(1);
  
  // Initialize GLEW so we can reference OpenGL functions.
  if(glewInit()/* != GLEW_OK */) {
    printf("error with initializing glew");
    glfwTerminate(); return -1; }

  // GLFW input callbacks
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  glfwSetCursorPosCallback(window, cursor_position_callback);
  glfwSetKeyCallback(window, key_callback);

  init();

  // Sets the coordinate system to screen 1:1 pixel mapping
  coords_screen();

  
  while(!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Framerate stuff
    g.delta = glfwGetTime() - g.last;
    g.last = glfwGetTime();
    g.frames ++;
    frameaccum += 1.0/g.delta;

    // If there have been more than 100 accumulated frames, reset the accumulation and update framecount
    #define FRAMERATE_ACCUMULATION 10
    if(g.frames % FRAMERATE_ACCUMULATION == 0) {
      snprintf(framerate, sizeof(framerate), "%.2f fps", frameaccum/FRAMERATE_ACCUMULATION);
      frameaccum = 0;
    }

    drawgame();
    
    draw();
    //glfwSetWindowShouldClose(window, 1);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  return 0;
}

