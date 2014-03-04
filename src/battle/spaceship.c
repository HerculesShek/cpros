

typedef struct {
  float sx;
  float sy;
  float heading; // direction
  float speed;
  int gone; // Is it dead?
  ALLEGRO_COLOR color;
} Spaceship;

Spaceship s;
al_draw_line(-8, 9, 0, -11, s->color, 3.0f);
al_draw_line(0, -11, 8, 9, s->color, 3.0f);
al_draw_line(-6, 4, -1, 4, s->color, 3.0f);
al_draw_line(6, 4, 1, 4, s->color, 3.0f);


ALLEGRO_EVENT_QUEUE *queue;
queue = al_create_event_queue();
ALLEGRO_EVENT event;
al_wait_for_event(queue, &event);

if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
  switch(event.keyboard.keycode) {
  case ALLEGRO_KEY_LEFT:
	// turn the ship left
    break;
  case ALLEGRO_KEY_RIGHT:
	// turn the ship right
    break;
  case ALLEGRO_KEY_SPACE:
	// fire
    break;
  }
}


void draw_ship(Spaceship* s)
{
  ALLEGRO_TRANSFORM transform;
  al_identity_transform(&transform);
  al_rotate_transform(&transform, DEGREES(s->heading));
  al_translate_transform(&transform, s->sx, s->sy);
  al_use_transform(&transform);
  al_draw_line(-8, 9, 0, -11, s->color, 3.0f);
  al_draw_line(0, -11, 8, 9, s->color, 3.0f);
  al_draw_line(-6, 4, -1, 4, s->color, 3.0f);
  al_draw_line(6, 4, 1, 4, s->color, 3.0f);
}
