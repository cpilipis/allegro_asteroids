#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

ALLEGRO_SAMPLE * explosionSound;
ALLEGRO_SAMPLE * shotSound;
ALLEGRO_SAMPLE * thrustSound;
ALLEGRO_SAMPLE_ID thrustSoundID; //define some sound placeholders
void initSounds()
{ //reserve some sound samples to play sounds and register the different sound files.
  al_reserve_samples(8);
  explosionSound = al_load_sample_f(al_fopen("explosion.ogg", "r"), ".ogg");
  shotSound = al_load_sample_f(al_fopen("laser.wav", "r"), ".wav");
  thrustSound = al_load_sample_f(al_fopen("thrust.wav", "r"), ".wav");
}

//different functions for playing sounds
void playExplosion()
{
  al_play_sample(explosionSound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
}
void playShoot()
{
  al_play_sample(shotSound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
}
//start the thruster noise
void playThrust()
{
  al_play_sample(thrustSound, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, &thrustSoundID);
}
//stop it using an ID I set up
void stopThrustSound()
{
  al_stop_sample(&thrustSoundID);
}
