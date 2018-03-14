#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

ALLEGRO_SAMPLE * explosionSound;
ALLEGRO_SAMPLE * shotSound;
ALLEGRO_SAMPLE * thrustSound;
ALLEGRO_SAMPLE_ID thrustSoundID;
void initSounds()
{
  al_reserve_samples(8);
  explosionSound = al_load_sample_f(al_fopen("explosion.ogg", "r"), ".ogg");
  shotSound = al_load_sample_f(al_fopen("laser.wav", "r"), ".wav");
  thrustSound = al_load_sample_f(al_fopen("thrust.wav", "r"), ".wav");
}

void playExplosion()
{
  al_play_sample(explosionSound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
}
void playShoot()
{
  al_play_sample(shotSound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
}
void playThrust()
{
  al_play_sample(thrustSound, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, &thrustSoundID);
}
void stopThrustSound()
{
  al_stop_sample(&thrustSoundID);
}
