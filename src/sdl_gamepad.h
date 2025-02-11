#pragma once
#ifndef CATA_SRC_SDL_GAMEPAD_H
#define CATA_SRC_SDL_GAMEPAD_H
#if defined(TILES)

#include "input.h"
#include "sdl_wrappers.h"

#define SDL_GAMEPAD_SCHEDULER (SDL_USEREVENT+1)

extern input_event last_input;

namespace gamepad
{

void init();
void quit();
void handle_axis_event( SDL_Event &event, int increment );
void handle_button_event( SDL_Event &event, int increment );
void handle_scheduler_event( SDL_Event &event, int increment );

void start_typing( SDL_Event &event );
void send_character( int current_character, int inc_keystate );
void dec_character( SDL_Event &event, int inc_keystate );
void inc_character( SDL_Event &event, int inc_keystate );
void handle_button_typing_event( SDL_Event &event, int inc_keystate );

SDL_GameController *get_controller();

} // namespace gamepad

#endif // TILES
#endif // CATA_SRC_SDL_GAMEPAD_H

