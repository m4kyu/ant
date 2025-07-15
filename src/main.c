#include <inttypes.h>
#include <raylib.h>
#include "chunk.h"

#define MAX_BUILDINGS   32
#define CELL_SIZE     20





Vector2 player = {0, 0};


void drawChunk(Chunk *chunk, Color color);
int isVisible(Chunk *chunk, float zoom);

int main(void) {
  const int screenWidth = 800;
  const int screenHeight = 450;
    

  InitWindow(screenWidth, screenHeight, "ant");
  SetTargetFPS(60);       



  Camera2D camera = {0};
  camera.target = (Vector2){ player.x, player.y};
  camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;


  Chunk *chunk = getChunk(0, 0);

  const int DOUBLE_CELL = (CELL_SIZE * CHUNK_SIZE) * 10;
  while (!WindowShouldClose()) {
    if (IsKeyDown(KEY_RIGHT)) player.x += 2;
    else if (IsKeyDown(KEY_LEFT)) player.x -= 2;

    if (IsKeyDown(KEY_UP)) player.y += 2;
    else if (IsKeyDown(KEY_DOWN)) player.y -= 2;

    // Camera target follows player
    camera.target = (Vector2){ player.x, player.y};

    // Camera rotation controls
    if (IsKeyDown(KEY_A)) camera.rotation--;
    else if (IsKeyDown(KEY_S)) camera.rotation++;


    if (camera.rotation > 40) camera.rotation = 40;
    else if (camera.rotation < -40) camera.rotation = -40;


    if (IsKeyDown(KEY_EQUAL)) camera.zoom += 0.1;
    else if (IsKeyDown(KEY_MINUS)) camera.zoom -= 0.1;
 
    if (camera.zoom > 3.0f) camera.zoom = 3.0f;
    else if (camera.zoom < 0.1f) camera.zoom = 0.1f;


    if (IsKeyPressed(KEY_R)) {
      camera.zoom = 1.0f;
      camera.rotation = 0.0f;
    }





    BeginDrawing();
      ClearBackground(RAYWHITE);

      BeginMode2D(camera);  
      int start_pos = player.x - DOUBLE_CELL;
        int x = start_pos;
        int y = player.y - DOUBLE_CELL;
        for (int i = 0; i < 20; i++) {
          for (int j = 0; j < 20; j++) {
            chunk = getChunk(x, y);
            if (!isVisible(chunk,  camera.zoom)) {
               x += CELL_SIZE * CHUNK_SIZE;
               continue;
            }
            drawChunk(chunk, GREEN);
            x += CELL_SIZE * CHUNK_SIZE;
          }  
          x = start_pos;
          y += CELL_SIZE * CHUNK_SIZE;
        }

        chunk = getChunk(0,  0);
        drawChunk(chunk, RED);

        DrawLine((int)camera.target.x, -screenHeight*10, (int)camera.target.x, screenHeight*10, RED);
        DrawLine(-screenWidth*10, (int)camera.target.y, screenWidth*10, (int)camera.target.y, RED);

      EndMode2D();
    EndDrawing();
  }

  CloseWindow();    
  return 0;
}

void drawChunk(Chunk *chunk, Color color) {
  const float X_POS = chunk->x - ((CHUNK_SIZE >> 1)  * CELL_SIZE);
  Vector2 pos = {X_POS, (float)chunk->y - ((CHUNK_SIZE >> 1) * CELL_SIZE)};


  Vector2 size = {CELL_SIZE, CELL_SIZE};
  for (int i = 0; i < CHUNK_SIZE; i++) {
    for (int j = 0; j < CHUNK_SIZE; j++) {
      if (chunk->data[i][j] == 0)   
        DrawRectangleV(pos, size, color);
      
      pos.x += CELL_SIZE;
    }
    pos.x = X_POS;
    pos.y += CELL_SIZE;
  } 
}


int isVisible(Chunk *chunk, float zoom) {
  const float WIDTH = GetScreenWidth() / zoom;
  const float HIGHT = GetScreenHeight() / zoom;


  

  if (chunk->x - ((CHUNK_SIZE >> 1) * CELL_SIZE) + (CHUNK_SIZE * CELL_SIZE) >= player.x - ((int)WIDTH >> 1) &&   
      chunk->x - ((CHUNK_SIZE >> 1) * CELL_SIZE) <= player.x + ((int)WIDTH >> 1)  &&   
      chunk->y - ((CHUNK_SIZE >> 1) * CELL_SIZE) + (CHUNK_SIZE * CELL_SIZE) >= player.y - ((int)HIGHT >> 1) &&    
      chunk->y - ((CHUNK_SIZE >> 1) * CELL_SIZE) <= player.y + ((int)HIGHT >> 1)) {
    return 1;
  }
  
  return 0;
}

