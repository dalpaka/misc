/*
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
*/

#include "raylib.h"
#include "stdlib.h"
#include "math.h"

int main(void)
{
    //Initalization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera split screen");
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
    int count = 4;
    float spacing = 4;

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        float offsetThisFrame = 10.0f*GetFrameTime();
        Vector3 oldCamPos = camera.position;  

        UpdateCamera(&camera, CAMERA_FIRST_PERSON);
        
        // Draw Player view to the render texture
        BeginTextureMode(screenPlayer);
            ClearBackground(SKYBLUE);
            
            BeginMode3D(camera);
            
                // Draw scene: grid of cube trees on a plane to make a map
                DrawPlane((Vector3){ 0, 0, 0 }, (Vector2){ 1000, 1000 }, BEIGE); // Simple world plane

                for (float x = -count*spacing; x <= count*spacing; x += spacing)
                {
                    for (float z = -count*spacing; z <= count*spacing; z += spacing)
                    {
                        DrawCube((Vector3) { x, 1.5f, z }, 1, 1, 1, LIME);
                        DrawCube((Vector3) { x, 0.5f, z }, 0.25f, 1, 0.25f, BROWN);
                    }
                }

                // Draw a cube at player's position
                DrawCube(camera.position, 1, 1, 1, RED);
                
            EndMode3D();
            
        EndTextureMode();


        // Draw both views render textures to the screen side by side
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
