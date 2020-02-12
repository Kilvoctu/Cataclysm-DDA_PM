#include "gpkey.h"

#include <map>
#include <string>
#include <utility>
#include <vector>
#include <initializer_list>

#include "string_formatter.h"

std::string convert_to_gamepad( const std::string keybind_in )
{
    std::string keybind_out;
    //define unicode
    std::string gp_cross = "\u00D7";
    std::string gp_square = "\u25A1";
    std::string gp_triangle = "\u25B3";
    std::string gp_circle = "\u25CB";
    std::string gp_up = "\u21D1";
    std::string gp_down = "\u21D3";
    std::string gp_left = "\u21D0";
    std::string gp_right = "\u21D2";
    std::string gp_up_left = "\u21D6";
    std::string gp_up_right = "\u21D7";
    std::string gp_down_left = "\u21D9";
    std::string gp_down_right = "\u21D8";

    if( keybind_in == "a" ) {
        keybind_out = string_format( "L2 + %s", gp_square );
    } else if( keybind_in == "b" ) {
        keybind_out = string_format( "L2 + R-STICK %s", gp_up_right );
    } else if( keybind_in == "c" ) {
        keybind_out = string_format( "{%s}", gp_circle );
    } else if( keybind_in == "d" ) {
        keybind_out = string_format( "L2 + R-STICK %s", gp_down_right );
    } else if( keybind_in == "e" ) {
        keybind_out = gp_square;
    } else if( keybind_in == "f" ) {
        keybind_out = string_format( "L2 + %s", gp_cross );
    } else if( keybind_in == "g" ) {
        keybind_out = string_format( "{%s}", gp_square );
    } else if( keybind_in == "h" ) {
        keybind_out = string_format( "L2 + %s", gp_circle );
    } else if( keybind_in == "i" ) {
        keybind_out = gp_triangle;
    } else if( keybind_in == "j" ) {
        keybind_out = keybind_in;
    } else if( keybind_in == "k" ) {
        keybind_out = keybind_in;
    } else if( keybind_in == "l" ) {
        keybind_out = keybind_in;
    } else if( keybind_in == "m" ) {
        keybind_out = "START";
    } else if( keybind_in == "n" ) {
        keybind_out = "L2 + Start";
    } else if( keybind_in == "o" ) {
        keybind_out = string_format( "{L2 + %s}", gp_circle );
    } else if( keybind_in == "p" ) {
        keybind_out = string_format( "L2 + %s", gp_triangle );
    } else if( keybind_in == "q" ) {
        keybind_out = keybind_in;
    } else if( keybind_in == "r" ) {
        keybind_out = "L2 + R1";
    } else if( keybind_in == "s" ) {
        keybind_out = string_format( "{%s}", gp_cross );
    } else if( keybind_in == "t" ) {
        keybind_out = string_format( "{L2 + R-STICK %s}", gp_up_left );
    } else if( keybind_in == "u" ) {
        keybind_out = keybind_in;
    } else if( keybind_in == "v" ) {
        keybind_out = "L1 + SELECT";
    } else if( keybind_in == "w" ) {
        keybind_out = string_format( "{L2 + %s}", gp_cross );
    } else if( keybind_in == "x" ) {
        keybind_out = "R1";
    } else if( keybind_in == "y" ) {
        keybind_out = keybind_in;
    } else if( keybind_in == "z" ) {
        keybind_out = "L1 + START";
    } else if( keybind_in == "A" ) {
        keybind_out = keybind_in;
    } else if( keybind_in == "B" ) {
        keybind_out = string_format( "{L2 + R-STICK %s}", gp_up_right );
    } else if( keybind_in == "C" ) {
        keybind_out = string_format( "{L2 + %s}", gp_triangle );
    } else if( keybind_in == "D" ) {
        keybind_out = "L1 + R1";
    } else if( keybind_in == "E" ) {
        keybind_out = string_format( "L1 + %s", gp_triangle );
    } else if( keybind_in == "F" ) {
        keybind_out = string_format( "L2 + R-STICK %s", gp_down_left );
    } else if( keybind_in == "G" ) {
        keybind_out = string_format( "{L2 + %s}", gp_square );
    } else if( keybind_in == "H" ) {
        keybind_out = string_format( "L2 + L-STICK %s", gp_left );
    } else if( keybind_in == "I" ) {
        keybind_out = string_format( "{L2 + %s}", gp_right );
    } else if( keybind_in == "J" ) {
        keybind_out = string_format( "L2 + L-STICK %s", gp_down );
    } else if( keybind_in == "K" ) {
        keybind_out = string_format( "L2 + L-STICK %s", gp_up );
    } else if( keybind_in == "L" ) {
        keybind_out = string_format( "L2 + L-STICK %s", gp_right );
    } else if( keybind_in == "M" ) {
        keybind_out = keybind_in;
    } else if( keybind_in == "N" ) {
        keybind_out = keybind_in;
    } else if( keybind_in == "O" ) {
        keybind_out = keybind_in;
    } else if( keybind_in == "P" ) {
        keybind_out = "{SELECT}";
    } else if( keybind_in == "Q" ) {
        keybind_out = keybind_in;
    } else if( keybind_in == "R" ) {
        keybind_out = string_format( "{L1 + %s}", gp_triangle );
    } else if( keybind_in == "S" ) {
        keybind_out = keybind_in;
    } else if( keybind_in == "T" ) {
        keybind_out = string_format( "{L2 + %s}", gp_up );
    } else if( keybind_in == "U" ) {
        keybind_out = "{L2 + R1}";
    } else if( keybind_in == "V" ) {
        keybind_out = "{START}";
    } else if( keybind_in == "W" ) {
        keybind_out = string_format( "L2 + %s", gp_up );
    } else if( keybind_in == "X" ) {
        keybind_out = "{R1}";
    } else if( keybind_in == "Y" ) {
        keybind_out = string_format( "L2 + %s", gp_left );
    } else if( keybind_in == "Z" ) {
        keybind_out = "{L1 + START}";
    } else if( keybind_in == "0" ) {
        keybind_out = "{L1 + L3}";
    } else if( keybind_in == "1" ) {
        keybind_out = string_format( "L2 + L-STICK %s", gp_down_left );
    } else if( keybind_in == "2" ) {
        keybind_out = string_format( "L2 + L-STICK %s", gp_down );
    } else if( keybind_in == "3" ) {
        keybind_out = string_format( "L2 + L-STICK %s", gp_down_right );
    } else if( keybind_in == "4" ) {
        keybind_out = string_format( "L2 + L-STICK %s", gp_left );
    } else if( keybind_in == "5" ) {
        keybind_out = "L2 + R3";
    } else if( keybind_in == "6" ) {
        keybind_out = string_format( "L2 + L-STICK %s", gp_right );
    } else if( keybind_in == "7" ) {
        keybind_out = string_format( "L2 + L-STICK %s", gp_up_left );
    } else if( keybind_in == "8" ) {
        keybind_out = string_format( "L2 + L-STICK %s", gp_up );
    } else if( keybind_in == "9" ) {
        keybind_out = string_format( "L2 + L-STICK %s", gp_up_right );
    } else if( keybind_in == ":" ) {
        keybind_out = "L2 + L3";
    } else if( keybind_in == ";" ) {
        keybind_out = keybind_in;
    } else if( keybind_in == "'" ) {
        keybind_out = "L1 + R2";
    } else if( keybind_in == "\\" ) {
        keybind_out = "{L1 + R1}";
    } else if( keybind_in == "\"" ) {
        keybind_out = "R3";
    } else if( keybind_in == "," ) {
        keybind_out = string_format( "{L2 + R-STICK %s}", gp_down_left );
    } else if( keybind_in == "." ) {
        keybind_out = "R2";
    } else if( keybind_in == "/" ) {
        keybind_out = "R3 + SELECT";
    } else if( keybind_in == "<" ) {
        keybind_out = string_format( "R-STICK %s", gp_up );
    } else if( keybind_in == ">" ) {
        keybind_out = string_format( "R-STICK %s", gp_down );
    } else if( keybind_in == "?" ) {
        keybind_out = "L2 + R3";
    } else if( keybind_in == "!" ) {
        keybind_out = "{L1 + R2}";
    } else if( keybind_in == "@" ) {
        keybind_out = "SELECT";
    } else if( keybind_in == "#" ) {
        keybind_out = keybind_in;
    } else if( keybind_in == "$" ) {
        keybind_out = string_format( "{L1 + %s}", gp_circle );
    } else if( keybind_in == "%" ) {
        keybind_out = string_format( "{%s}", gp_triangle );
    } else if( keybind_in == "^" ) {
        keybind_out = "{L2 + START}";
    } else if( keybind_in == "&" ) {
        keybind_out = string_format( "L1 + %s", gp_square );
    } else if( keybind_in == "*" ) {
        keybind_out = string_format( "{L1 + %s}", gp_square );
    } else if( keybind_in == "(" ) {
        keybind_out = "{L2 + SELECT}";
    } else if( keybind_in == ")" ) {
        keybind_out = "{L1 + SELECT}";
    } else if( keybind_in == "_" ) {
        keybind_out = "{L1 + L2}";
    } else if( keybind_in == "[" ) {
        keybind_out = string_format( "L1 + R-STICK %s", gp_left );
    } else if( keybind_in == "]" ) {
        keybind_out = string_format( "L1 + R-STICK %s", gp_right );
    } else if( keybind_in == "{" ) {
        keybind_out = "{L1 + R3}";
    } else if( keybind_in == "}" ) {
        keybind_out = "L1 + R3";
    } else if( keybind_in == "|" ) {
        keybind_out = string_format( "L1 + %s", gp_circle );
    } else if( keybind_in == "`" ) {
        keybind_out = "L2 + L1";
    } else if( keybind_in == "~" ) {
        keybind_out = "{L2 + L1}";
    } else if( keybind_in == "-" ) {
        keybind_out = string_format( "{L2 + %s}", gp_down );
    } else if( keybind_in == "+" ) {
        keybind_out = string_format( "L2 + %s", gp_down );
    } else if( keybind_in == "=" ) {
        keybind_out = "L1 + L2";
    } else if( keybind_in == "TAB" ) {
        keybind_out = string_format( "R-STICK %s", gp_right );
    } else if( keybind_in == "BACKTAB" ) {
        keybind_out = string_format( "R-STICK %s", gp_left );
    } else if( keybind_in == "SPACE" ) {
        keybind_out = string_format( "{R-STICK %s}", gp_right );
    } else if( keybind_in == "UP" ) {
        keybind_out = gp_up;
    } else if( keybind_in == "DOWN" ) {
        keybind_out = gp_down;
    } else if( keybind_in == "LEFT" ) {
        keybind_out = gp_left;
    } else if( keybind_in == "RIGHT" ) {
        keybind_out = gp_right;
    } else if( keybind_in == "NPAGE" ) {
        keybind_out = string_format( "L1 + R-STICK %s", gp_down );
    } else if( keybind_in == "PPAGE" ) {
        keybind_out = string_format( "L1 + R-STICK %s", gp_up );
    } else if( keybind_in == "ESC" ) {
        keybind_out = gp_circle;
    } else if( keybind_in == "BACKSPACE" ) {
        keybind_out = string_format( "{R-STICK %s}", gp_left );
    } else if( keybind_in == "HOME" ) {
        keybind_out = string_format( "{R-STICK %s}", gp_up );
    } else if( keybind_in == "BREAK" ) {
        keybind_out = keybind_in;
    } else if( keybind_in == "END" ) {
        keybind_out = string_format( "{R-STICK %s}", gp_down );
    } else if( keybind_in == "RETURN" ) {
        keybind_out = gp_cross;
    } else if( keybind_in == "MOUSE_LEFT" ) {
        keybind_out = "L3";
    } else if( keybind_in == "MOUSE_RIGHT" ) {
        keybind_out = "{L3}";
    } else if( keybind_in == "SCROLL_UP" ) {
        keybind_out = string_format( "L2 + R-STICK %s", gp_up );
    } else if( keybind_in == "SCROLL_DOWN" ) {
        keybind_out = string_format( "L2 + R-STICK %s", gp_down );
    } else if( keybind_in == "MOUSE_MOVE" ) {
        keybind_out = "L-STICK";
    } else {
        keybind_out = keybind_in;
    }
    return keybind_out;
}