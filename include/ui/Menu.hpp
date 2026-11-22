#ifndef MENU_HPP
#define MENU_HPP

enum class MenuChoice {
    NewGame,
    LoadGame,
    Exit, 
    Invalid
};

class Menu {
public:
    MenuChoice ShowMainMenu() const;
};

#endif