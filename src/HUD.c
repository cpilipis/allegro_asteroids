#include "drawing.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

ALLEGRO_FONT * scoreFont;
ALLEGRO_FONT * titleFont;
ALLEGRO_FONT * infoFont; //initialize some pointers to store fonts
void initHud()
{
  scoreFont = al_load_ttf_font("gameFont.otf", 36, 0);
  titleFont = al_load_ttf_font("gameFont.otf", 72, 0);
  infoFont = al_load_ttf_font("gameFont.otf", 20, 0); //it's all the same font, but in different sizes
}

void killHud()
{
  al_destroy_font(scoreFont);
  al_destroy_font(infoFont);
  al_destroy_font(titleFont);
}

void drawPlayerHud(int score, int lives)
{
  //create a placeholder string to store the "SCORE: insertnumberhere" thing we display
  //With 8 characters allocated for the "Score: " and null terminator in the string, we can store up to a 16 digit number for the player's score.
  char scoreText[24];
  sprintf(scoreText, "Score: %d", score);
  al_draw_text(scoreFont, al_map_rgb(255, 255, 255), 10, 10, 0, scoreText); //print the score thing
  al_draw_text(scoreFont, al_map_rgb(255, 255, 255), 10, 40, 0, "Lives: "); //we'll print that word and then show the player's lives.
  if (lives > 0)
  { //print the lives one by one as green triangles representing the player's ship
    for (int i = 0; i < lives; i++)
    {
      int startX = i * 20 + 95;
      al_draw_triangle(startX, 65, startX + 7, 40, startX + 15, 65, al_map_rgb(100, 255, 0), 0);
    }
  }
  else if (lives == -1)
  {
   //print the game over screen
    al_draw_text(scoreFont, al_map_rgb(255, 0, 0), SCREEN_W/2 - 50, SCREEN_H/2 - 18, 0, "Game Over");
  } //if the player has died with no lives left, it'll go to -1
  //that's how we know the player has died and lost the game
}
void menu()
{
  //print the instructions for the main menu
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
  //draw game paused text
  al_draw_text(scoreFont, al_map_rgb(255, 255, 255), SCREEN_W/2 - 50, SCREEN_H/2 - 18, 0, "Game paused...");
  al_draw_text(scoreFont, al_map_rgb(255, 255, 255), SCREEN_W/2 - 75, SCREEN_H/2 + 18, 0, "Push Escape to resume");
}
