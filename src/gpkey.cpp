#include "gpkey.h"

#include <map>
#include <string>
#include <utility>
#include <vector>
#include <initializer_list>
#include <iostream>
#include <unordered_map>

#include "string_formatter.h"

// define unicode
// PS prompts
/*std::string gp_cross = "\u00D7";
std::string gp_square = "\u25A1";
std::string gp_triangle = "\u25B3";
std::string gp_circle = "\u25CB";
std::string gp_l1 = "L1";
std::string gp_l2 = "L2";
std::string gp_r1 = "R1";
std::string gp_r2 = "R2";
std::string l_mod = "L1+";
std::string l2_mod = "L2+";*/

// Big N prompts
/*std::string gp_cross = "\u0392";
std::string gp_circle = "\u0391";
std::string gp_square = "\u03A5";
std::string gp_triangle = "\u03A7";
std::string gp_l1 = "L";
std::string gp_l2 = "ZL";
std::string gp_r1 = "R";
std::string gp_r2 = "ZR";
std::string gp_lstick = "LS";
std::string gp_rstick = "RS";
std::string l_mod = "L+";
std::string l2_mod = "ZL+";*/

// Eckbok prompts
std::string gp_cross = "\u0391";    // A
std::string gp_circle = "\u0392";   // B
std::string gp_square = "\u03A7";   // X
std::string gp_triangle = "\u03A5"; // Y
std::string gp_l1 = "LB";
std::string gp_l2 = "LT";
std::string gp_r1 = "RB";
std::string gp_r2 = "RT";
std::string gp_lstick = "LS";
std::string gp_rstick = "RS";
std::string l_mod = "LB+";
std::string l2_mod = "LT+";

// shared prompts
std::string gp_select = "\u23F8";
std::string gp_start = "\u23F5";
std::string gp_hotkey = "\u25CD";
std::string gp_hotkey_mod = "\u23F8+";

std::string gp_up = "\u2191";
std::string gp_down = "\u2193";
std::string gp_left = "\u2190";
std::string gp_right = "\u2192";
std::string gp_up_left = "\u2196";
std::string gp_up_right = "\u2197";
std::string gp_down_left = "\u2199";
std::string gp_down_right = "\u2198";

std::string gp_lstick_up = "L\u2B89";
std::string gp_lstick_down = "L\u2B8B";
std::string gp_lstick_left = "L\u2B88";
std::string gp_lstick_right = "L\u2B8A";
std::string gp_rstick_up = "R\u2B89";
std::string gp_rstick_down = "R\u2B8B";
std::string gp_rstick_left = "R\u2B88";
std::string gp_rstick_right = "R\u2B8A";


std::string convert_to_gamepad( const std::string keybind_in_pre )
{ // legacy keyboard replacements
    std::string keybind_out;

	std::string keybind_in = keybind_in_pre;
	if( ( keybind_in_pre.rfind( "CTRL+", 0 ) == 0 ) || ( keybind_in_pre.rfind("Ctrl+", 0 ) == 0 ) ) {
		keybind_in.erase( 0, 5 );
		l_mod = "LT+";
	}

    if( keybind_in == "d" ) {
        keybind_out = gp_triangle;
    } else if( keybind_in == "e" ) {
        keybind_out = gp_square;
    } else if( keybind_in == "c" ) { //replace references of examine terrain/furnish to examine all
        keybind_out = gp_square;
    } else if( keybind_in == "f" ) {
        keybind_out = gp_r1;
    } else if( keybind_in == "g" ) {
        keybind_out = gp_r2;
    } else if( keybind_in == "l" ) {
        keybind_out = gp_lstick;
    } else if( keybind_in == "m" ) {
        keybind_out = gp_start;
    } else if( keybind_in == "p" ) {
        keybind_out = gp_select;
    } else if( keybind_in == "r" ) {
        keybind_out = gp_rstick;
    } else if( keybind_in == "u" ) {
        keybind_out = string_format( "%s", gp_lstick_left );
    } else if( keybind_in == "v" ) {
        keybind_out = string_format( "%s", gp_lstick_right );
    } else if( keybind_in == "w" ) {
        keybind_out = string_format( "%s", gp_rstick_up );
    } else if( keybind_in == "x" ) {
        keybind_out = string_format( "%s", gp_rstick_down );
    } else if( keybind_in == "y" ) {
        keybind_out = string_format( "%s", gp_rstick_left );
    } else if( keybind_in == "z" ) {
        keybind_out = string_format( "%s", gp_rstick_right );
    } else if( keybind_in == "D" ) {
        keybind_out = string_format( "%s%s", l_mod, gp_triangle );
    } else if( keybind_in == "B" ) { //replace references of drop to multidrop
        keybind_out = string_format( "%s%s", l_mod, gp_triangle );
    } else if( keybind_in == "E" ) {
        keybind_out = string_format( "%s%s", l_mod, gp_square );
    } else if( keybind_in == "N" ) { //replace references of pickup adjacent to pickup nearby
        keybind_out = string_format( "%s%s", l_mod, gp_square );
    } else if( keybind_in == "F" ) {
        keybind_out = string_format( "%s%s", l_mod, gp_r1 );
    } else if( keybind_in == "G" ) {
        keybind_out = string_format( "%s%s", l_mod, gp_r2 );
    } else if( keybind_in == "L" ) {
        keybind_out = string_format( "%s%s", l_mod, gp_lstick );
    } else if( keybind_in == "M" ) {
        keybind_out = string_format( "%s%s", l_mod, gp_start );
    } else if( keybind_in == "P" ) {
        keybind_out = string_format( "%s%s", l_mod, gp_select );
    } else if( keybind_in == "R" ) {
        keybind_out = string_format( "%s%s", l_mod, gp_rstick );
    } else if( keybind_in == "U" ) {
        keybind_out = string_format( "%s%s", l_mod, gp_lstick_left );
    } else if( keybind_in == "V" ) {
        keybind_out = string_format( "%s%s", l_mod, gp_lstick_right );
    } else if( keybind_in == "W" ) {
        keybind_out = string_format( "%s%s", l_mod, gp_rstick_up );
    } else if( keybind_in == "X" ) {
        keybind_out = string_format( "%s%s", l_mod, gp_rstick_down );
    } else if( keybind_in == "Y" ) {
        keybind_out = string_format( "%s%s", l_mod, gp_rstick_left );
    } else if( keybind_in == "Z" ) {
        keybind_out = string_format( "%s%s", l_mod, gp_rstick_right );
    } else if( keybind_in == "F1" ) {
        keybind_out = gp_hotkey;
    } else if( keybind_in == "&" ) {
        keybind_out = string_format( "%s%s", gp_hotkey_mod, gp_cross );
    } else if( keybind_in == "*" ) {
        keybind_out = string_format( "%s%s", gp_hotkey_mod, gp_triangle );
    } else if( keybind_in == "\\" ) {
        keybind_out = string_format( "%s%s", gp_hotkey_mod, gp_circle );
    } else if( keybind_in == "/" ) {
        keybind_out = string_format( "%s%s", gp_hotkey_mod, gp_square );
    } else if( keybind_in == "?" ) {
        keybind_out = string_format( "%s%s", gp_hotkey_mod, gp_l1 );
    } else if( keybind_in == "[" ) {
        keybind_out = string_format( "%s", gp_lstick_up );
    } else if( keybind_in == "]" ) {
        keybind_out = string_format( "%s", gp_lstick_down );
    } else if( keybind_in == "{" ) {
        keybind_out = string_format( "%s%s", l_mod, gp_lstick_up );
    } else if( keybind_in == "}" ) {
        keybind_out = string_format( "%s%s", l_mod, gp_lstick_down );
    } else if( keybind_in == "-" ) {
        keybind_out = string_format( "%s%s", gp_hotkey_mod, gp_r1 );
    } else if( keybind_in == "+" ) {
        keybind_out = string_format( "%s%s", gp_hotkey_mod, gp_r2 );
    } else if( keybind_in == "=" ) {
        keybind_out = string_format( "%s%s", gp_hotkey_mod, gp_l1 );
    } else if( keybind_in == "UP" ) {
        keybind_out = gp_up;
    } else if( keybind_in == "DOWN" ) {
        keybind_out = gp_down;
    } else if( keybind_in == "LEFT" ) {
        keybind_out = gp_left;
    } else if( keybind_in == "RIGHT" ) {
        keybind_out = gp_right;
	//handle diagonals
    } else if( keybind_in == "HOME" ) { //NW
        keybind_out = string_format( "%s%s", l_mod, gp_up_left );
	} else if( keybind_in == "PPAGE" ) { //NE
        keybind_out = string_format( "%s%s", l_mod, gp_up_right );
	} else if( keybind_in == "END" ) { //SW
        keybind_out = string_format( "%s%s", l_mod, gp_down_left );
	} else if( keybind_in == "NPAGE" ) { //SE
        keybind_out = string_format( "%s%s", l_mod, gp_down_right );
    } else if( keybind_in == "ESC" ) {
        keybind_out = gp_circle;
    } else if( keybind_in == "S" ) { //replace references of save to main menu (where save exists)
        keybind_out = gp_circle;
    } else if( keybind_in == "RETURN" ) {
        keybind_out = gp_cross;
    } else {
        keybind_out = keybind_in;
    }
    return keybind_out;
}

std::string convert_joy_string( const std::string joy_in )
{ // gamepad "JOY_" replacements
	std::string joy_out;

	std::unordered_map< std::string, std::string > j;
	//j["JOY_0"] = gp_cross;
	//j["JOY_1"] = gp_circle;
	j["JOY_2"] = gp_square;
	j["JOY_3"] = gp_triangle;
	j["JOY_4"] = gp_select;
	j["JOY_6"] = gp_start;
	j["JOY_7"] = gp_lstick;
	j["JOY_8"] = gp_rstick;
	j["JOY_10"] = gp_r1;
	j["JOY_21"] = gp_rstick_up;
	j["JOY_22"] = gp_rstick_right;
	j["JOY_23"] = gp_rstick_down;
	j["JOY_24"] = gp_rstick_left;
	j["JOY_30"] = gp_r2;
	j["JOY_257"] = gp_lstick_up;
	j["JOY_258"] = gp_lstick_right;
	j["JOY_259"] = gp_lstick_down;
	j["JOY_260"] = gp_lstick_left;
    // L1 modifier
	j["JOY_300"] = l_mod + gp_cross;
	j["JOY_301"] = l_mod + gp_circle;
	j["JOY_302"] = l_mod + gp_square;
	j["JOY_303"] = l_mod + gp_triangle;
	j["JOY_304"] = l_mod + gp_select;
	j["JOY_306"] = l_mod + gp_start;
	j["JOY_307"] = l_mod + gp_lstick;
	j["JOY_308"] = l_mod + gp_rstick;
	j["JOY_310"] = l_mod + gp_r1;
	j["JOY_321"] = l_mod + gp_rstick_up;
	j["JOY_322"] = l_mod + gp_rstick_right;
	j["JOY_323"] = l_mod + gp_rstick_down;
	j["JOY_324"] = l_mod + gp_rstick_left;
	j["JOY_330"] = l_mod + gp_r2;
	j["JOY_557"] = l_mod + gp_lstick_up;
	j["JOY_558"] = l_mod + gp_lstick_right;
	j["JOY_559"] = l_mod + gp_lstick_down;
	j["JOY_560"] = l_mod + gp_lstick_left;
	// L2 modifier
	j["JOY_400"] = l2_mod + gp_cross;
	j["JOY_401"] = l2_mod + gp_circle;
	j["JOY_402"] = l2_mod + gp_square;
	j["JOY_403"] = l2_mod + gp_triangle;
	j["JOY_404"] = l2_mod + gp_select;
	j["JOY_406"] = l2_mod + gp_start;
	j["JOY_407"] = l2_mod + gp_lstick;
	j["JOY_408"] = l2_mod + gp_rstick;
	j["JOY_410"] = l2_mod + gp_r1;
	j["JOY_421"] = l2_mod + gp_rstick_up;
	j["JOY_422"] = l2_mod + gp_rstick_right;
	j["JOY_423"] = l2_mod + gp_rstick_down;
	j["JOY_424"] = l2_mod + gp_rstick_left;
	j["JOY_430"] = l2_mod + gp_r2;
	j["JOY_657"] = l2_mod + gp_lstick_up;
	j["JOY_658"] = l2_mod + gp_lstick_right;
	j["JOY_659"] = l2_mod + gp_lstick_down;
	j["JOY_660"] = l2_mod + gp_lstick_left;
	// L1+L2 modifier
	j["JOY_500"] = l_mod + l2_mod + gp_cross;
	j["JOY_501"] = l_mod + l2_mod + gp_circle;
	j["JOY_502"] = l_mod + l2_mod + gp_square;
	j["JOY_503"] = l_mod + l2_mod + gp_triangle;
	j["JOY_504"] = l_mod + l2_mod + gp_select;
	j["JOY_506"] = l_mod + l2_mod + gp_start;
	j["JOY_507"] = l_mod + l2_mod + gp_lstick;
	j["JOY_508"] = l_mod + l2_mod + gp_rstick;
	j["JOY_510"] = l_mod + l2_mod + gp_r1;
	j["JOY_521"] = l_mod + l2_mod + gp_rstick_up;
	j["JOY_522"] = l_mod + l2_mod + gp_rstick_right;
	j["JOY_523"] = l_mod + l2_mod + gp_rstick_down;
	j["JOY_524"] = l_mod + l2_mod + gp_rstick_left;
	j["JOY_530"] = l_mod + l2_mod + gp_r2;
	j["JOY_757"] = l_mod + l2_mod + gp_lstick_up;
	j["JOY_758"] = l_mod + l2_mod + gp_lstick_right;
	j["JOY_759"] = l_mod + l2_mod + gp_lstick_down;
	j["JOY_760"] = l_mod + l2_mod + gp_lstick_left;
	// diagonals
	j["JOY_797"] = l2_mod + gp_up_left;
	j["JOY_799"] = l2_mod + gp_up_right;
	j["JOY_791"] = l2_mod + gp_down_left;
	j["JOY_793"] = l2_mod + gp_down_right;

	joy_out = j[joy_in];
	if ( joy_out != "" ) {
		return joy_out;
	} else {
		return joy_in;
	}
}