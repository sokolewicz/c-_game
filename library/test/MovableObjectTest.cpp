#include <boost/test/unit_test.hpp>
#include <model/MovableObject.h>
#include <model/MovableMonster.h>
#include <model/Player.h>
#include <model/InteractionWithMonster.h>

struct MovableObjectTestFixture
{
    int x=30;
    int y=20;
     char representation='&';
     bool enable_movement=false;
    const std::string name="Adam";
    unsigned int health;
     int stars;
    unsigned int id=1;
    bool turn;
    std::string message;
    InteractionWithMonster *interaction;
    MovableObjectTestFixture()
    {
        interaction=new InteractionWithMonster (message, nullptr);
    }
    ~MovableObjectTestFixture(){
        delete interaction;
    }

};
BOOST_FIXTURE_TEST_SUITE(MovableObjectTestSuite, MovableObjectTestFixture)


    BOOST_AUTO_TEST_CASE(PlayerConstructorTest)
    {
        Player player {x,y,representation,enable_movement,name, health, stars,id, turn};
        BOOST_TEST (player.get_x()==30);
        BOOST_TEST (player.get_y()==20);
        BOOST_TEST (player.get_representation()=='&');
        BOOST_TEST (player.is_enable_movement());
        BOOST_TEST (player.get_health()==100);
        BOOST_TEST (player.get_stars()==0);
    }
    BOOST_AUTO_TEST_CASE(PlayerGetObjectTypeTest)
    {
        Player player {x,y,representation,enable_movement,name,health,stars,id, turn};
        BOOST_TEST (player.get_object_type()=="Player");
    }
    BOOST_AUTO_TEST_CASE(PlayerSettersTest)
    {
        Player player {x,y,representation,enable_movement,name,health,stars,id, turn};
        player.set_health(-30);
        BOOST_TEST(player.get_health()==70);
        player.set_stars(30);
        BOOST_TEST(player.get_stars()==30);
        player.set_x(10);
        BOOST_TEST(player.get_x()==10);
        player.set_y(16);
        BOOST_TEST (player.get_y()==16);
    }
    BOOST_AUTO_TEST_CASE(MovableMonsterConstructorTest)
    {
        MovableMonster monster {x,y,representation,enable_movement,interaction};
        BOOST_TEST (monster.get_x()==30);
        BOOST_TEST (monster.get_y()==20);
        BOOST_TEST (monster.get_representation()=='&');
        BOOST_TEST (monster.is_enable_movement());
        BOOST_TEST (monster.get_interaction()==interaction);
    }

    BOOST_AUTO_TEST_CASE(MonsterGetObjectTypeTest)
    {
        MovableMonster monster {x,y,representation,enable_movement,interaction};
        BOOST_TEST (monster.get_object_type()=="Monster");
    }







BOOST_AUTO_TEST_SUITE_END()