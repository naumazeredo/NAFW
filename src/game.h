/**
 *  Not Available Game Application Class
 *
 *  \brief Stores all main game structures
 *    Handle window and events
 *    Controls time flow and game state
 *
 */

#ifndef NAFW_GAME_H_
#define NAFW_GAME_H_

struct SDL_Window;

// Not Available Framework
namespace nafw
{
class Timer;

const unsigned int WINDOW_WIDTH = 640;
const unsigned int WINDOW_HEIGHT = 480;

/**
 *  Game Class
 *
 *  \brief Base game class, should be inherited
 */
// TODO Add Timer
// TODO Add Network
// TODO Add Renderer
// TODO Add Camera (on renderer?)
class Game
{
 public:
  // Constructor and Destructor
  Game();
  virtual ~Game();

  // Start window with WINDOW_WIDTH x WINDOW_HEIGHT
  // TODO Save and read settings file
  bool Start(const char* title, int argc, char** argv);

  // Resize Window
  void SetSize(unsigned int w, unsigned int h);

  // Set fullscreen mode
  void SetFullscreen(bool fullscreen, bool borderless);

  // Run game logic
  virtual bool Run();

 protected:
  // Handle inputs
  virtual bool HandleInputs();

  // Game Window
  SDL_Window* window_;
  int width_, height_;
  bool fullscreen_;

  // Physics
  int physics_dt;

  // Game Timer
  nafw::Timer *timer_;
};

// Not Available Framework
}

#endif//NAFW_GAME_H_
