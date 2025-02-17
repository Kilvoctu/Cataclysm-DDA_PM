#pragma once
#ifndef GPKEY_H
#define GPKEY_H

#include <string>

std::string convert_to_gamepad( std::string keybind_in_pre );
std::string convert_joy_string( std::string joy_in );
std::string character_set( int int_in );

#endif // GPKEY_H