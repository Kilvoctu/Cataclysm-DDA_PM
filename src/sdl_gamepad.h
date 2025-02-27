#pragma once
#ifndef CATA_SRC_SDL_GAMEPAD_H
#define CATA_SRC_SDL_GAMEPAD_H
#if defined(TILES)
#include "input_enums.h"
#include "sdl_wrappers.h"

#define SDL_GAMEPAD_SCHEDULER (SDL_USEREVENT+1)

// IWYU pragma: no_forward_declare input_event  // Is valid, but looks silly
extern input_event last_input;

namespace gamepad
{

void init();
void quit();
void handle_axis_event( SDL_Event &event, int inc_keystate );
void handle_button_event( SDL_Event &event, int inc_keystate, bool hold_u,
                          bool hold_d, bool hold_l, bool hold_r );
void handle_scheduler_event( SDL_Event &event, int inc_keystate );

void start_typing();
void send_character( int current_character, int inc_keystate );
void dec_character( int inc_keystate );
void inc_character( int inc_keystate );
void handle_button_typing_event( SDL_Event &event, int inc_keystate );

SDL_GameController *get_controller();

} // namespace gamepad

#endif // TILES
#endif // CATA_SRC_SDL_GAMEPAD_H

