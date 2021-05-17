#ifndef FIELD_DEV_INTERACTIVEFIELD_H
#define FIELD_DEV_INTERACTIVEFIELD_H
#include <model/Field.h>

class InteractiveField : public Field {
protected:
    Interaction *interaction;
public:
    virtual ~InteractiveField();
    InteractiveField( int x, int y, char representation, bool enable_movement, Interaction *interaction);
    const std::string get_all_info ();
    Interaction* get_interaction() const override;
};


#endif //FIELD_DEV_INTERACTIVEFIELD_H
