//
// Created by student on 07.06.2020.
//

#ifndef INPUTMANAGER_GAMEMANAGER_DEV_INPUTMANAGER_H
#define INPUTMANAGER_GAMEMANAGER_DEV_INPUTMANAGER_H

#include <iostream>
#include <sstream>


class InputManager {

public:

    std::string get_string (const std::string& message);
    void show_message (const std::string& text);
    char show_message_and_get_char (const std::string& text);
    void clear ();
};



#endif //INPUTMANAGER_GAMEMANAGER_DEV_INPUTMANAGER_H
