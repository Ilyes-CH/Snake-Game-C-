#include <deque>
#include <iostream>
#include <ostream>
#include <raylib.h>
#include <raymath.h>

using namespace std;

// Colors
Color green = {173, 204, 96, 255};
Color dark_green = {43, 51, 24, 255};

int cell_size = 30;
int cell_count = 25;
int offset = 75;
int area = cell_count * cell_size;

double last_update_time = 0;

bool eventTriggered(double interval) {
  double current_time = GetTime();
  if (current_time - last_update_time >= interval) {
    last_update_time = current_time;
    return true;
  }
  return false;
}

// Food Class

class Food {

public:
  Vector2 position; // Vector2 holds {x,y} in cells not px

  Texture2D
      texture; // better for faster gpu rendering uses optimization techniques

  Food(deque<Vector2> snakeBody) // constructor
  {
    Image image = LoadImage("../../resources/apple.png"); // using raylib
    texture = LoadTextureFromImage(image);
    UnloadImage(image); // to free memory
    position = GenerateRandomPos(snakeBody);
    // to account for the inital pos of snake
  }
  ~Food() // destructor to remove any resources when they go out of scope or the
          // obj is destroyed for better performance and to avoid memory leaks
  {
    UnloadTexture(texture);
  }

  void Draw() {
    // DrawRectangle(position.x * cell_size, position.y * cell_size,
    // cell_size,cell_size, dark_green);
    DrawTexture(texture, offset + position.x * cell_size,
                offset + position.y * cell_size, WHITE);
  }

  Vector2 GenerateRandomPos(deque<Vector2> snakeBody) {
    float x = GetRandomValue(0, cell_count - 1);
    float y = GetRandomValue(0, cell_count - 1);
    // this measure to make sure that the new position of food does not get
    // created in or on the snake
    for (unsigned i = 0; i < snakeBody.size(); i++) {
      if (Vector2Equals(snakeBody[i], (Vector2){x, y})) {
        GenerateRandomPos(snakeBody);
      }
    }
    return Vector2{x, y};
  }
};

// Snake Class

class Snake {

public:
  deque<Vector2> body = {Vector2{6, 4}, Vector2{7, 4},
                         Vector2{8, 4}}; // deque to push pop from both ends

  Vector2 direction = {1, 0};

  void Draw() {
    for (unsigned int i = 0; i < body.size();
         ++i) { // the DrawRectangleRounded needs Rectangle type and float
                // values we used type casting in two ways in cpp
      Rectangle rect = Rectangle{offset + (float)body[i].x * cell_size,
                                 offset + (float)body[i].y * cell_size,
                                 static_cast<float>(cell_size),
                                 static_cast<float>(cell_size)};
      DrawRectangleRounded(rect, 0.5, 6, dark_green);
    }
  }

  void Update() {
    body.pop_back();
    body.push_front(Vector2Add(body[0], direction));
  }
  void Increase() { body.push_back(Vector2Add(body[0], direction)); }

  void Reset() {
    body = {Vector2{6, 4}, Vector2{7, 4}, Vector2{8, 4}};
    direction = {1, 0};
  }
};

class Game {
public:
  Snake snake = Snake();
  Food food = Food(snake.body);
  bool running = false;
  int score = 0;
  int bestScore = 0;
  Sound eatSound;
  Sound wallSound;
  Music backgroundMusic;

  Game() {
    InitAudioDevice(); // setup audio system for the game
    eatSound = LoadSound("../../resources/Sounds_eat.mp3");
    wallSound = LoadSound("../../resources/Sounds_wall.mp3");
    backgroundMusic = LoadMusicStream("../../resources/bg.mp3");
  }

  ~Game() {
    // free the memory from the sounds
    UnloadSound(eatSound);
    UnloadSound(wallSound);
    UnloadMusicStream(backgroundMusic);
    CloseAudioDevice();
  }
  void Draw() {
    food.Draw();
    snake.Draw();
  }

  void GameControls() {

    // Game Controls
    if (IsKeyPressed(KEY_UP) && snake.direction.y != 1) {
      snake.direction = {0, -1};
      std::cout << "key up pressed: " << snake.direction.y << "\n";
      running = true;
    }
    if (IsKeyPressed(KEY_DOWN) && snake.direction.y != -1) {

      snake.direction = {0, 1};
      std::cout << "key down pressed: " << snake.direction.y << "\n";
      running = true;
    }
    if (IsKeyPressed(KEY_LEFT) && snake.direction.x != 1) {
      snake.direction = {-1, 0};
      std::cout << "key left pressed: " << snake.direction.x << "\n";
      running = true;
    }
    if (IsKeyPressed(KEY_RIGHT) && snake.direction.x != -1) {
      snake.direction = {1, 0};
      std::cout << "key right pressed: " << snake.direction.x << "\n";
      running = true;
    }
  }

  void UpdateSnake(double time) {
    // update snake position every 200 mil seconds
    if (eventTriggered(time)) {
      snake.Update();
    }
  }
  bool CheckCollisionWithFood() {
    // if head of snake deque collides with the cell of the food,
    // remove food, place it randomly elsewhere,
    // increment score and increment length of snake
    if (food.position.x == snake.body[0].x &&
        food.position.y == snake.body[0].y) { // or use Vector2Equals
      std::cout << "collision with food detected" << "\n";
      PlaySound(eatSound);
      score++;
      return true;
    }
    return false;
  }
  void CheckCollisionWithBody() {
    for (unsigned i = 0; i < snake.body.size() - 1; i++) {
      if (snake.body[0] == snake.body[i + 1]) {
        PlaySound(wallSound);
        GameOver();
      }
    }
  }
  void CheckCollisionWithEdges() {
    int min_bound = offset / cell_size; // Convert pixel offset to grid units
    int max_bound = cell_count + min_bound - 1; // 25 + (75/30) - 1

    if (snake.body[0].x >= max_bound - 1 || snake.body[0].x < min_bound - 2 ||
        snake.body[0].y >= max_bound - 1 || snake.body[0].y < min_bound - 2) {

      PlaySound(wallSound);
      GameOver();
    }
  }

  void GameOver() {
    std::cout << "Game Over" << "\n";
    snake.Reset();
    food.GenerateRandomPos(snake.body);
    score > bestScore ? bestScore = score : 0;
    score = 0;
    running = false;
  }
};

int main() {
  cout << "Game Started ...\n" << endl;

  // blank canvas 750pxx750px
  InitWindow(2 * offset + area, 2 * offset + area, "Snake Game");

  SetTargetFPS(60); // FPS

  // Instanciate Game
  Game game = Game();
  PlayMusicStream(game.backgroundMusic);
  // game loop
  while (WindowShouldClose() ==
         false) // if the esc is pressed or X icon is pressed
  {
    BeginDrawing(); // create a blank canvas

    if (!game.running)
      DrawText("Press ENTER to Start", area / 2 - 130, area / 2 - 50, 30, RED);

    game.GameControls();
    if (game.running) {
      UpdateMusicStream(game.backgroundMusic);
      game.UpdateSnake(0.15);
      // check collision with edges of the window
      game.CheckCollisionWithEdges();
      game.CheckCollisionWithBody();
      if (game.CheckCollisionWithFood()) {
        // draw the food in another position
        game.food.position = game.food.GenerateRandomPos(game.snake.body);
        // increase size of snake
        game.snake.Increase();
      }
    } // Rendering
    ClearBackground(green); // print green on BG
    //
    DrawRectangleLinesEx(Rectangle{(float)offset - 5, (float)offset - 5,
                                   (float)cell_size * cell_count + 10,
                                   (float)cell_size * cell_count + 10},
                         5, dark_green);

    char buffer[50];
    sprintf(buffer, "Snake Game: %d | %d", game.score, game.bestScore);
    DrawText(buffer, offset - 5, 20, 40, dark_green);

    game.Draw();

    EndDrawing(); // end rendering
  }

  CloseWindow();
  return 0;
}
