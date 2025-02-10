/*******************************************************************************************
zlib License

(C) 2025 Dimitri Jordan

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
********************************************************************************************/

#include "raylib.h"
#include "stdlib.h"
#include "math.h"

int main(void)
{
    //Initalization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera with hills");
    DisableCursor();
    SetTargetFPS(60);
    
    // Setup player camera
    Camera camera = { 0 };
    camera.fovy = 60.0f;
    camera.up.y = 1.0f;
    camera.target.y = 1.0f;
    camera.position.z = -3.0f;
    camera.position.y = 1.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    
    RenderTexture screenPlayer = LoadRenderTexture(screenWidth, screenHeight);
    Rectangle splitScreenRect = { 0.0f, 0.0f, (float)screenPlayer.texture.width, (float)-screenPlayer.texture.height };
    
    // Grid data
    int count = 20;
    float spacing = 4;

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);
        
        // Draw Player view to the render texture
        BeginTextureMode(screenPlayer);
            ClearBackground(SKYBLUE);
            
            BeginMode3D(camera);
            
                // Draw scene: hills using a sine wave for smooth terrain
                for (float x = -count * spacing; x <= count * spacing; x += spacing)
                {
                    for (float z = -count * spacing; z <= count * spacing; z += spacing)
                    {
                        float height = sinf(x * 0.1f) * cosf(z * 0.1f) * 3.0f; // Hill height
                        DrawCube((Vector3) { x, height - 1.0f, z }, spacing, 1, spacing, GREEN);
                    }
                }
                
                // Draw a cube at player's position
                DrawCube(camera.position, 1, 1, 1, RED);
                
            EndMode3D();
            
        EndTextureMode();

        // Draw both views render textures to the screen
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTextureRec(screenPlayer.texture, splitScreenRect, (Vector2){ 0, 0 }, WHITE);
        EndDrawing();
    }

    // De-Initialization
    UnloadRenderTexture(screenPlayer);
    CloseWindow(); 

    return 0;
}
