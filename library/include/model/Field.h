

#ifndef FIELD_DEV_FIELD_H
#define FIELD_DEV_FIELD_H
#include <string>
#include "Interaction.h"


class Field {
protected:
    int x, y;
private:
    char representation;
    bool enable_movement;
public:
    Field(int x, int y,char representation, bool enable_movement);
    virtual ~Field ();
   const int get_x() const;
   const int get_y() const;
    std::string get_coordinates () const;
   bool is_enable_movement() const;
   void set_enable_movement (bool enable);
   void set_representation (char representation);
   virtual Interaction* get_interaction() const;
   const char get_representation() const;
 std::string get_all_info () const;
};


#endif //FIELD_DEV_FIELD_H
