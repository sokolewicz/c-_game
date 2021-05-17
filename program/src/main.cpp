#include <iostream>
#include <managers/GameManager.h>
#include <managers/InputManager.h>
#include <managers/OutputManager.h>
#include <model/RandomInteraction.h>
#include <model/WorldRepository.h>

int main()
{
    PtrTemplate <InputManager> input_manager (new InputManager()) ;
    GameManager* game_manager;
    std::stringstream s1;
    char option;
    s1 << "[1] Load game\n[2] New game\n[3] Exit\n";

    while (true)
    {
        input_manager->clear();
        input_manager->show_message(s1.str());
        option = input_manager->show_message_and_get_char("Choose: ");

        if (option == '1' || option == '2')
            GameManager* game_manager = new GameManager(input_manager.get(), option);
        else if (option == '3')
            break;

        if (game_manager != nullptr)
            delete game_manager;
   }



}