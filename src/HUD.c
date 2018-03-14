#include "drawing.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

ALLEGRO_FONT * scoreFont;
ALLEGRO_FONT * titleFont;
ALLEGRO_FONT * infoFont;
void initHud()
{
  scoreFont = al_load_ttf_font("gameFont.otf", 36, 0);
  titleFont = al_load_ttf_font("gameFont.otf", 72, 0);
  infoFont = al_load_ttf_font("gameFont.otf", 20, 0);
}

void killHud()
{
  al_destroy_font(scoreFont);
}

//const ALLEGRO_FONT scoreFont = al_load_font("gameFont.otf", 14, 0);

void drawPlayerHud(int score, int lives)
{
  char scoreText[20];
  sprintf(scoreText, "Score: %d", score);
  al_draw_text(scoreFont, al_map_rgb(255, 255, 255), 10, 10, 0, scoreText);
  al_draw_text(scoreFont, al_map_rgb(255, 255, 255), 10, 40, 0, "Lives: ");
  if (lives > 0)
  {
    for (int i = 0; i < lives; i++)
    {
      int startX = i * 30 + 85;
      al_draw_triangle(startX, 65, startX + 7, 40, startX + 15, 65, al_map_rgb(100, 255, 0), 0);
    }
  }
  else if (lives == -1)
  {
    al_draw_text(scoreFont, al_map_rgb(255, 0, 0), SCREEN_W/2 - 50, SCREEN_H/2 - 18, 0, "Game Over");
  }
}
void menu()
{
  al_draw_text(titleFont, al_map_rgb(255, 255, 255), SCREEN_W/2, 100, ALLEGRO_ALIGN_CENTRE, "ASTEROIDS");
  al_draw_text(scoreFont, al_map_rgb(255, 255, 255), SCREEN_W/2, 300, ALLEGRO_ALIGN_CENTRE, "Press any key to begin");
  al_draw_text(infoFont, al_map_rgb(255, 255, 255), 20, 400, 0, "Controls:");
  al_draw_text(infoFont, al_map_rgb(255, 255, 255), 120, 400, 0, "Left and right arrow keys: rotate ship.");
  al_draw_text(infoFont, al_map_rgb(255, 255, 255), 120, 420, 0, "Up arrow key: accelerate ship");
  al_draw_text(infoFont, al_map_rgb(255, 255, 255), 120, 440, 0, "Space key: fire ship's laser");
  al_draw_text(infoFont, al_map_rgb(255, 255, 255), 120, 460, 0, "Shoot asteroids to score points and break them apart into smaller asteroids");
  al_draw_text(infoFont, al_map_rgb(255, 255, 255), 120, 480, 0, "Smaller asteroids will yield more points when destroyed");
  al_draw_text(infoFont, al_map_rgb(255, 255, 255), 120, 500, 0, "Clear all the asteroids to move on to the next level");
  al_draw_text(infoFont, al_map_rgb(255, 255, 255), 120, 520, 0, "Every 10,000 points scored awards a new life");
  al_draw_text(infoFont, al_map_rgb(255, 255, 255), 120, 540, 0, "Crashing into an asteroid loses a life");
  al_draw_text(infoFont, al_map_rgb(255, 255, 255), 120, 560, 0, "The game ends when the player has died and has no lives left to respawn");
}
void drawPaused()
{
  al_draw_text(scoreFont, al_map_rgb(255, 255, 255), SCREEN_W/2 - 50, SCREEN_H/2 - 18, 0, "Game paused...");
  al_draw_text(scoreFont, al_map_rgb(255, 255, 255), SCREEN_W/2 - 75, SCREEN_H/2 + 18, 0, "Push Escape to resume");
}
