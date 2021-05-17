#include <managers/GameManager.h>
#include <managers/SaveLoadManager.h>
#include <model/WorldRepository.h>
#include <model/InteractiveFieldAndMonsterRepository.h>
#include <managers/InputManager.h>
#include <model/PlayerRepository.h>
#include <sstream>

using namespace std;


GameManager::GameManager (InputManager *input_manager, int option) : input_manager(input_manager)
{
    menu(option);
}

GameManager::~GameManager()
{

}

void GameManager::menu(int option)
{
    stringstream s2, s3;

    s2 << "Choose number of players: [2,5]"<<endl;

    string number_of_players;
    vector<string> player_names;
    string name = " ";
    unsigned int n;


    if (option == '1')
    {

        PlayerRepository* p;
        world_repository = make_shared<WorldRepository>(WorldRepository(&p));


        player_repository = make_shared<PlayerRepository>(PlayerRepository(&GameManager::set_player_has_been_moved, this, world_repository.get()));
        p = player_repository.get();

        monster_and_interactive_field_repository = make_shared<InteractiveFieldAndMonsterRepository>(InteractiveFieldAndMonsterRepository(world_repository.get(), player_repository.get()));

        save_load_manager = make_shared<SaveLoadManager>(SaveLoadManager(world_repository.get(),player_repository.get(), monster_and_interactive_field_repository.get(), input_manager.get()));


        if (save_load_manager->is_loading_game_available())
        {
            if (save_load_manager->load_game())
                play();

            else
            {
                input_manager->show_message("Loading game is not available :(");

            }

        }
        else
        {
            input_manager->show_message("Loading game is not available :(");

        }
    }
    else if (option == '2')
    {
        number_of_players = input_manager->show_message_and_get_char(s2.str().c_str());
        try{
            n = stoi(number_of_players);

            if (n > 1 && n < 5)
            {
                input_manager->show_message("Max length of player name is 10 chars");
                for (int i=0;i<n;)
                {
                    s3.str("");
                    s3 << "Type name of player number: " << (i+1) <<endl;
                    name = input_manager->get_string(s3.str());

                    if (name != " " && name.length() <= 10)
                    {
                        player_names.push_back(name);
                        i++;
                    }
                    else
                    {
                        input_manager->show_message("Invalid player name!");
                    }

                }

                PlayerRepository* p;
                world_repository = make_shared<WorldRepository>(WorldRepository(15, 15, 15 * 15 * 0.1, &p));

                player_repository = make_shared<PlayerRepository>(PlayerRepository(n, player_names, world_repository.get(),
                        &GameManager::set_player_has_been_moved, this));

                p = player_repository.get();

                monster_and_interactive_field_repository = make_shared<InteractiveFieldAndMonsterRepository>
                        (InteractiveFieldAndMonsterRepository(world_repository.get(),player_repository.get(),
                                12,15*15*0.1,'M','?'));

                save_load_manager = make_shared<SaveLoadManager>(SaveLoadManager(world_repository.get(),player_repository.get(),monster_and_interactive_field_repository.get(), input_manager.get()));



                play();
            }
            else
            {
                input_manager->show_message("Invalid number of players :(");
            }
        }
        catch (std::invalid_argument const &argument)
        {
            string m = "Error: ";
            m += argument.what();
            input_manager->show_message(m);
        }
        catch (std::out_of_range const &argument)
        {
            string m = "Error: ";
            m += argument.what();
            input_manager->show_message(m);
        }
    }

}

void GameManager::end_game()
{

    save_load_manager->clear_all();


}


void GameManager::play()
{
    output_manager = make_shared<OutputManager>(OutputManager(player_repository.get(), world_repository.get(), monster_and_interactive_field_repository.get()));

    save_load_manager->save_starting_time();

    stringstream directions_text, player_text, player_info_text, interaction_text;
    directions_text << "Directions/Options:\n[W] Up\n[D] Right\n[S] Down\n[A] Left\n[1] Save game\n[2] Exit to menu\n";
    char direction;
    int x=0, y=0;
    bool b;
    const Field* current_field;
    Interaction* interaction;
    string interaction_message;
    bool end = false;



    while (!end)
    {

        output_manager->clear_screen();
        input_manager ->show_message(save_load_manager->load_starting_time());
        output_manager->show_board();


        player_info_text.str("");
        for (const auto &i: player_repository->get_players())
        {
            player_info_text<<i->info();
        }

        input_manager->show_message(interaction_text.str());

        input_manager->show_message(player_info_text.str());

        player_text.str("");
        player_text << "Ruch gracza: " << player_repository->get_current_player()->get_name() << "["<<player_repository->get_current_player()->get_representation()<<"]"<<endl;

        b = false;

        input_manager -> show_message(player_text.str());
        input_manager->show_message(directions_text.str());

        while (!b) {

            direction = input_manager->show_message_and_get_char("Choose:\n");

            cout<<direction<<endl;
            switch (direction) {
                case 'W':
                    x = 1;
                    y = 0;
                    break;

                case 'S':
                    x = -1;
                    y = 0;
                    break;
                case 'D':
                    x = 0;
                    y = 1;
                    break;
                case 'A':
                    x = 0;
                    y = -1;
                    break;

                case '1':

                    if (save_load_manager->save_game())
                    {
                        input_manager->show_message("Game has been saved");
                    } else
                        input_manager->show_message("Something goes wrong ;(");

                    break;

                case '2':

                    return;
                    break;

                default:
                    input_manager->show_message("Invalid option!");
                    break;
            }

            if (x != 0 || y != 0) {
                if (player_repository->move_current_player(-x, y)) {
                    x = y = 0;
                    b = true;
                } else {
                    input_manager->show_message("You can not move in this direction!");

                }
            }
        }

        interaction_text.str("");
        interaction_text << "Interaction (Player: " << player_repository->get_current_player()->get_name()<<")"<<endl;



        while (player_has_been_moved)
        {
            set_player_has_been_moved(false);


            current_field = monster_and_interactive_field_repository->get_current_monster_or_interactive_field();

            monster_and_interactive_field_repository->move_monsters_randomly();

            if (current_field != nullptr)
            {
                interaction = current_field->get_interaction();

                interaction_message = interaction->interact();
                interaction_text << interaction_message;

                if (player_repository->current_player_is_dead())
                {
                    player_text.clear();
                    player_text << "Player: "<<player_repository->get_current_player()->get_name()<< " is dead";
                    input_manager->show_message(player_text.str());
                    player_repository->remove_current_player();

                    break;
                }

            }
            else
            {
                interaction_text << "<no interaction>"<<endl;
            }

            if (world_repository->is_end())
            {
                end = true;

            }

        }

        if (!end)
        player_repository->change_to_next_player();


    }


    win();
    end_game();
}

void GameManager::set_player_has_been_moved(bool moved) {


    player_has_been_moved = moved;
}

void GameManager::win() {
    stringstream s;
    s << "Player: "<<player_repository->get_current_player()->get_name()<< " is the winner!!!"<<endl << " Starting time: "<<save_load_manager->load_starting_time()
      << "Ending time: "<<boost::posix_time::second_clock::local_time();
    input_manager->show_message(s.str());
}

