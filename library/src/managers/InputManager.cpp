#include "managers/InputManager.h"


using namespace std;


std::string InputManager::get_string(const string& message)
{

    string s;
    cout<<message<<endl;
    fflush(stdin);
    cin>>s;

    return s;

}

void InputManager::show_message(const string& text) {

    cout<<text<<endl;

}


char InputManager::show_message_and_get_char(const string& text) {

    cout<<text<<endl;

    char c;

    fflush(stdin);

    cin>>c;

    return c;
}

void InputManager::clear() {
    system ("clear");
}
