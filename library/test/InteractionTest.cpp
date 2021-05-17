#include <boost/test/unit_test.hpp>
#include <model/Interaction.h>
#include <model/RandomInteraction.h>
#include <model/InteractionWithMonster.h>
#include <model/PlayerRepository.h>
#include <iostream>
#include <model/WorldRepository.h>
#include <managers/GameManager.h>
struct InteractionTestFixture{
    PlayerRepository *playerRepository;
    WorldRepository *worldRepository;
    std::string message;
    std::vector<std::string> names={"Adam", "Tomek", "Kasia"};
    void (GameManager::*call_back_function)(bool moved);
    GameManager *gameManager;
    InteractionTestFixture()
    {

        worldRepository=new WorldRepository (20,20,5, &playerRepository);
        gameManager=new GameManager(nullptr, 2);
        playerRepository=new PlayerRepository (3, names, worldRepository, nullptr, nullptr);

    }
    ~InteractionTestFixture()
{
        delete playerRepository;
        delete worldRepository;
        delete gameManager;
}
};
BOOST_FIXTURE_TEST_SUITE(InteractionSuite, InteractionTestFixture)
BOOST_AUTO_TEST_CASE(RandomInteractionConstructorTest)
    {
        RandomInteraction randomInteraction {message, playerRepository};
        std::string m=randomInteraction.get_message();

        BOOST_TEST((m=="You found some stars "||m=="You got robbed and lost some stars :("
        ||m=="You lost a little bit of health level, better take care of yourself next time"
        || m=="You found magic cure, your health level increased"
        ||m=="We decided to teleport you, becasuse why not?"));

    }
    BOOST_AUTO_TEST_CASE(RandomInteractionInteractTest)
    {
        RandomInteraction randomInteraction {message, playerRepository};
        PlayerPtr p=playerRepository->get_current_player();
        BOOST_TEST  (p->get_health()==100);
        BOOST_TEST  (p->get_stars()==0);
        int x=p->get_x();
        int y=p->get_y();
        randomInteraction.set_valid_message(0);
        BOOST_TEST(randomInteraction.get_message()=="You found some stars ");
        randomInteraction.interact();
        BOOST_TEST(p->get_stars()>0);
         int a=p->get_stars();
        randomInteraction.set_valid_message(1);
        BOOST_TEST(randomInteraction.get_message()=="You got robbed and lost some stars :(");
        randomInteraction.interact();
        BOOST_TEST(p->get_stars()<a);
        randomInteraction.set_valid_message(2);
        randomInteraction.interact();
        BOOST_TEST(p->get_health()<100);
         int h=p->get_health();
        randomInteraction.set_valid_message(3);
        BOOST_TEST(randomInteraction.get_message()=="You found magic cure, your health level increased");
        randomInteraction.interact();
        BOOST_TEST(p->get_health()>h);
    }
    BOOST_AUTO_TEST_CASE(InteractionWithMonsterConstructorTest)
    {
       InteractionWithMonster im {message, playerRepository};
       BOOST_TEST(im.get_message()=="You meet monster");
    }
    BOOST_AUTO_TEST_CASE(InteractionWithMonsterInteractTest)
    {
        InteractionWithMonster im {message, playerRepository};
        PlayerPtr current_player=playerRepository->get_current_player();
        BOOST_TEST(current_player->get_health()==100);
        im.interact();
        BOOST_TEST(current_player->get_health()<100);
    }



BOOST_AUTO_TEST_SUITE_END()