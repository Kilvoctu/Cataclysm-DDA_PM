#pragma once
#ifndef GPKEY_H
#define GPKEY_H

#include <map>
#include <string>
#include <utility>
#include <vector>
#include <initializer_list>

void gamepad( );

std::vector<tripoint> display_gamepad_menu( );
std::vector<std::string> registered_buttons = { 
	"Button:", "Command",
	"Dpad:", "Movement",
	"LStick:", "Mouse Movement",
	"L3:", "Left-click",
	"RStick X-axis:", "Left/Right Tab Through Menus",
	"RStick Y-axis:", "Move Up/Down Z-Levels",
	"R3:", "Walk/Run/Crouch",
	"Cross (Tap):", "Actions Menu",
	"Cross (Hold):", "Smash",
	"Square (Tap):", "Examine",
	"Square (Hold):", "Get Items",
	"Triangle (Tap):", "Inventory",
	"Triangle (Hold):", "Execute Action",
	"Circle (Tap):", "Main Menu",
	"Circle (Hold):", "Close",
	"L1:", "Modifier 1",
	"L2:", "Modifier 2",
	"R1 (Tap):", "Look",
	"R1 (Hold):", "Peek",
	"R2:", "Pass Turn (hold to keep passing)",
	"Select (Tap):", "Player Info",
	"Select (Hold):", "Message Log",
	"Start (Tap):", "Overmap / (Vehicle) Repair",
	"Start (Hold):", "List Nearby Items",

	"L1+Dpad:", "Diagonal Movement",
	"L1+LStick:", "Full Numpad",
	"L1+L3:", "Numpad 5",
	"L1+RStick X-axis:", "Unknown",
	"L1+RStick Y-axis:", "Page Up/Page Down",
	"L1+R3:", "Sidebar Options",
	"L1+Cross:", "Unused",
	"L1+Square (Tap):", "Craft",
	"L1+Square (Hold):", "Construction",
	"L1+Triangle (Tap):", "Consume Item",
	"L1+Triangle (Hold):", "Read Item",
	"L1+Circle (Tap):", "Wait",
	"L1+Circle (Hold):", "Sleep",
	"L1+L2:", "Unused",
	"L1+R1 (Tap):", "Drop Item",
	"L1+R1 (Hold):", "Haul Item",
	"L1+R2 (Tap):", "Ignore Monster",
	"L1+R2 (Hold):", "Toggle Safe Mode",
	"L1+Select (Tap):", "Morale",
	"L1+Select (Hold):", "Scores",
	"L1+Start (Tap):", "Zoom In",
	"L1+Start (Hold):", "Zoom Out",

	"L2+Dpad Down:", "Sort Armor",
	"L2+Dpad Left:", "Zones Manager",
	"L2+Dpad Up (Tap):", "Wear Item / (Overmap) Fast Travel",
	"L2+Dpad Up (Hold):", "Take Off Item",
	"L2+Dpad Right:", "Unused",
	"L2+LStick:", "Move View",
	"L2+L3:", "Reset View",
	"L2+RStick X-axis:", "Unused",
	"L2+RStick Y-axis:", "Mousewheel Scroll",
	"L2+R3:", "Keybindind",
	"L2+Cross (Tap):", "Aim Weapon / (While Aiming) Current Aim",
	"L2+Cross (Hold):", "Wield Item",
	"L2+Square (Tap):", "Use Item / (While Aiming) Regular Aim",
	"L2+Square (Hold):", "Grab",
	"L2+Triangle (Tap):", "Bionics / (While Aiming) Precise Aim",
	"L2+Triangle (Hold):", "Talk",
	"L2+Circle (Tap):", "(While Aiming) Careful Aim",
	"L2+Circle (Hold):", "(Vehicle) Remove",
	"L2+L1:", "Unused",
	"L2+R1 (Tap):", "Reload Item",
	"L2+R1 (Hold):", "Unload Item",
	"L2+R2:", "Pass Turn (hold to keep passing)",
	"L2+Select:", "Advanced Inventory",
	"L2+Start:", "Unused",
};
#endif