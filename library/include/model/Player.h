
#ifndef FIELD_DEV_PLAYER_H
#define FIELD_DEV_PLAYER_H


#include <string>
#include "MovableObject.h"
#include <memory>

class Player;
typedef std::shared_ptr<Player> PlayerPtr;

class Player:public MovableObject {
private:

    std::string name;
    unsigned int health,  id;
    int stars;
    bool turn; //określa, czy jest aktualnie kolejka tego gracza
public:
    Player(int x,int y, char representation, bool enable_movement, const std::string &name, unsigned int health,  int stars,
           unsigned int id, bool turn);
    virtual ~Player();
    const unsigned int get_health() const;
    const  int get_stars()const ;
    const std::string get_name() const;
    virtual  std::string get_object_type() override;
    void set_health( int offset_health);
    void set_stars( int offset_stars);
     unsigned int get_id() const;
    bool is_turn();
    void set_turn(bool new_turn);
   std::string info () const;
};


#endif //FIELD_DEV_PLAYER_H
