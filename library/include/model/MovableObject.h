
#ifndef FIELD_DEV_MOVABLEOBJECT_H
#define FIELD_DEV_MOVABLEOBJECT_H
#include "Field.h"


class MovableObject : public Field {
public:
    MovableObject ( int x, int y, char representation, bool enable_movement);

virtual ~MovableObject();
    void set_x ( int offsetX);
    void set_y( int offsetY);
    virtual std::string get_object_type ()=0;
};


#endif //FIELD_DEV_MOVABLEOBJECT_H
