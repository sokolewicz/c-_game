

#ifndef OUTPUT_DEV_OUTPUTMANAGER_H
#define OUTPUT_DEV_OUTPUTMANAGER_H

class PlayerRepository;
class WorldRepository;
class InteractiveFieldAndMonsterRepository;
class OutputManager
{
private:
    PlayerRepository *playerRepository;
    WorldRepository *worldRepository;
    InteractiveFieldAndMonsterRepository* monstersRepository;
public:
    OutputManager(PlayerRepository *playerRepository, WorldRepository *worldRepository, InteractiveFieldAndMonsterRepository *monsters);
virtual ~ OutputManager();
    void clear_screen ();
    void show_board();
};
#endif //OUTPUT_DEV_OUTPUTMANAGER_H
