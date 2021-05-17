

#ifndef INTERACTION_DEV_INTERACTION_H
#define INTERACTION_DEV_INTERACTION_H
#include <map>
#include <string>
#include <exception>


class PlayerRepository;
class InteractionException: public std::logic_error
{
public:
    explicit InteractionException(const std::string& what_arg) : std::logic_error(what_arg) {}
};
class Interaction {
private:

    std::string message;


public:
    Interaction(const std::string &message, PlayerRepository *playerRepository);

    virtual ~Interaction();
    PlayerRepository *playerRepository;
    virtual std::string interact() = 0;
    const std::string &get_message() const;
    void set_valid_message(unsigned int num);
};


#endif //INTERACTION_DEV_INTERACTION_H
