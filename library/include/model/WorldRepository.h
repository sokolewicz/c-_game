//
// Created by student on 06.06.2020.
//

#ifndef WORLDREPOSITORY_DEV_WORLDREPOSITORY_H
#define WORLDREPOSITORY_DEV_WORLDREPOSITORY_H

#include <model/Field.h>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <model/PlayerRepository.h>

typedef std::shared_ptr<Field> FieldPtr;
typedef std::shared_ptr<Player> PlayerPtr;

class WorldRepository {

private:
    std::vector<FieldPtr> fields;
    unsigned int finish_x;
    unsigned int finish_y;
    unsigned int world_size_x;
    unsigned int world_size_y;

    PlayerRepository** player_repository;
    bool moved;
    void player_has_been_moved (bool moved);
public:
    WorldRepository(PlayerRepository** player_repo);

    WorldRepository(unsigned int world_size_x, unsigned int world_size_y, unsigned int number_of_obstacles, PlayerRepository** player_repo);
    ~WorldRepository();

    template <typename T> typename std::vector<T>::const_iterator find_field_ (int x, int y, const std::vector<T> &vec) const
    {
        typename std::vector<T>::const_iterator i = (find_if(vec.begin(), vec.end(), [&x, &y](const T &ptr)
        { return (ptr.get()->get_x() == x && ptr.get()->get_y() == y);}));
        return  i;
    }
    bool set_new_world_size(unsigned int world_size_x, unsigned int world_size_y);
    bool is_field_empty (unsigned int destination_x, unsigned int destination_y) const;

    bool create_field(unsigned int x, unsigned int y, char representation, bool enable_movement);

    bool is_end ();

    unsigned int get_world_size_x () const ;
    unsigned int get_world_size_y () const ;
    unsigned int get_number_of_fields() const;
    FieldPtr get_field (unsigned int i) const ;
    const std::vector<FieldPtr> &get_fields () const;
};


#endif //WORLDREPOSITORY_DEV_WORLDREPOSITORY_H
