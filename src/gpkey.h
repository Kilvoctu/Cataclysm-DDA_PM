#pragma once
#ifndef GPKEY_H
#define GPKEY_H

#include <string>

std::string convert_to_gamepad( const std::string keybind_in );
std::string convert_joy_string( const std::string joy_in );
std::string character_set( const int int_in );

#endif