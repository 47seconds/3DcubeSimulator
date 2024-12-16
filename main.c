#include <SDL2/SDL.h>
#include <stdlib.h>
#include <math.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x00000000
#define POINT_SIZE 1
#define CUBE_SIDE 200
#define ALPHA 0.04
#define BETA 0.02
#define GAMMA 0.03

int X_OFFSET = SCREEN_WIDTH/2;
int Y_OFFSET = SCREEN_HEIGHT/2;

typedef struct Point {
  double x;
  double y;
  double z;
} Point;

void draw_point(SDL_Surface* surface, int x, int y) {
  SDL_Rect rect = (SDL_Rect){x, y, POINT_SIZE, POINT_SIZE};
  SDL_FillRect(surface, &rect, COLOR_WHITE);
}

void draw_point_3D(SDL_Surface* surface, Point p) {
  int x_2D = p.x + X_OFFSET;
  int y_2D = p.y + Y_OFFSET;
  draw_point(surface, x_2D, y_2D);
}

Point** generate_cube() {
  Point** cube = (Point**)malloc(sizeof(Point*) * 12);
  for(int i = 0; i < 12; i++) cube[i] = (Point*)malloc(sizeof(Point) * CUBE_SIDE);
  return cube;
}

void delete_cube(Point** cube) {
  for(int i = 0; i < 12; i++) free(cube[i]);
  free(cube);
}

void initialize_cube(Point** cube) {
  Point st = {((double)CUBE_SIDE/2)*(-1), ((double)CUBE_SIDE/2)*(-1), ((double)CUBE_SIDE/2)*(-1)};
  Point end = {(double)CUBE_SIDE/2, (double)CUBE_SIDE/2, (double)CUBE_SIDE/2};

  for (int j = 0; j < CUBE_SIDE; j++) cube[0][j] = (Point){st.x + j, st.y, st.z};
  for (int j = 0; j < CUBE_SIDE; j++) cube[1][j] = (Point){st.x, st.y + j, st.z};
  for (int j = 0; j < CUBE_SIDE; j++) cube[2][j] = (Point){st.x, st.y, st.z + j};

  for (int j = 0; j < CUBE_SIDE; j++) cube[3][j] = (Point){end.x - j, end.y, end.z};
  for (int j = 0; j < CUBE_SIDE; j++) cube[4][j] = (Point){end.x, end.y - j, end.z};
  for (int j = 0; j < CUBE_SIDE; j++) cube[5][j] = (Point){end.x, end.y, end.z - j};

  for (int j = 0; j < CUBE_SIDE; j++) cube[6][j] = (Point){st.x + CUBE_SIDE, st.y + j, st.z};
  for (int j = 0; j < CUBE_SIDE; j++) cube[7][j] = (Point){st.x + CUBE_SIDE, st.y, st.z + j};

  for (int j = 0; j < CUBE_SIDE; j++) cube[8][j] = (Point){st.x + j, st.y + CUBE_SIDE, st.z};
  for (int j = 0; j < CUBE_SIDE; j++) cube[9][j] = (Point){st.x, st.y + CUBE_SIDE, st.z + j};
  
  for (int j = 0; j < CUBE_SIDE; j++) cube[10][j] = (Point){st.x + j, st.y, st.z + CUBE_SIDE};
  for (int j = 0; j < CUBE_SIDE; j++) cube[11][j] = (Point){st.x, st.y + j, st.z + CUBE_SIDE};
}

void apply_rotation_to_point(Point* p, double alpha, double beta, double gamma) {
  double rotation_matrix[3][3] = {
                                  {cos(beta) * cos(gamma), (sin(alpha) * sin(beta) * cos(gamma)) - (cos(alpha) * sin(gamma)), (cos(alpha) * sin(beta) * cos(gamma)) + (sin(alpha) * sin(gamma))},
                                  {cos(beta) * sin(gamma), (sin(alpha) * sin(beta) * sin(gamma)) + (cos(alpha) * cos(gamma)), (cos(alpha) * sin(beta) * sin(gamma)) - (sin(alpha) * cos(gamma))},
                                  {-sin(beta), sin(alpha) * cos(beta), cos(alpha) * cos(beta)}
                                 };
  double vector[3] = {p->x, p->y, p->z};
  double result[3];

  for (int i = 0; i < 3; i++) {
    double dot_prod = 0;
    for (int j = 0; j < 3; j++) dot_prod += vector[j] * rotation_matrix[j][i];
    result[i] = dot_prod;
  }

  p->x = result[0], p->y = result[1], p->z = result[2];
}

void apply_rotation(Point** cube, double alpha, double beta, double gamma) {
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < CUBE_SIDE; j++) apply_rotation_to_point(&cube[i][j], alpha, beta, gamma);
  }
}

void draw_cube(Point** cube, SDL_Surface* surface) {
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < CUBE_SIDE; j++) draw_point_3D(surface, cube[i][j]);
  }
}

int main(int argc, char** argv) {
  
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window* main_window = SDL_CreateWindow("3D Rotating Cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  SDL_Surface* main_surface = SDL_GetWindowSurface(main_window);
  
  SDL_Rect background = (SDL_Rect){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  
  Point** cube = generate_cube();
  initialize_cube(cube);
  draw_cube(cube, main_surface);

  SDL_Event event;
  int simulation_running = 1;

  while (simulation_running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) simulation_running = 0;
    }

    apply_rotation(cube, ALPHA, BETA, GAMMA);
    SDL_FillRect(main_surface, &background, COLOR_BLACK);
    draw_cube(cube, main_surface);
    SDL_UpdateWindowSurface(main_window);

    SDL_Delay(10);

  }
  
  delete_cube(cube);
  SDL_DestroyWindow(main_window);
  SDL_Quit(); 

  return 0;
}

// gcc -o main main.c -lm `sdl2-config --cflags --libs`
