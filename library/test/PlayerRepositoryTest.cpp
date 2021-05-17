#include <boost/test/unit_test.hpp>
#include <model/PlayerRepository.h>
#include <model/WorldRepository.h>
#include <managers/GameManager.h>

struct PlayerRepositoryTestFixture
{
     int x=30;
     int y=20;
     char representation='&';
     const std::string name="Adam";
     bool current_player;
     int health,stars,id;
    std::vector<std::string> names={"Adam", "Tomek", "Kasia"};
    WorldRepository *worldRepository;

    PlayerRepositoryTestFixture()
    {
        worldRepository=new WorldRepository (20,20,5, nullptr);
    }
    ~PlayerRepositoryTestFixture()
    {
        delete worldRepository;
    }
};
BOOST_FIXTURE_TEST_SUITE(PlayerRepositoryTestSuite, PlayerRepositoryTestFixture)

    BOOST_AUTO_TEST_CASE (PlayerRepositoryConstructorTest)
    {
        PlayerRepository playerrepository (3,names, worldRepository, nullptr, nullptr);
        BOOST_TEST(playerrepository.get_players_number()==3);
        BOOST_TEST(playerrepository.get_current_player()->get_id()==0);
        BOOST_TEST(playerrepository.get_current_player()->get_name()=="Adam");
        BOOST_TEST(playerrepository.get_current_player()->get_coordinates()=="(18, 3)");
        BOOST_TEST(playerrepository.get_player(0)->is_turn());
        BOOST_TEST(playerrepository.get_player(0)->get_name()=="Adam");
        BOOST_TEST(!playerrepository.get_player(1)->is_turn());
    }
    BOOST_AUTO_TEST_CASE (PlayerRepositoryChangeToNextPlayerTest)
    {
        PlayerRepository playerrepository (3,names,worldRepository, nullptr, nullptr);
        BOOST_TEST(playerrepository.get_current_player()->get_id()==0);
        BOOST_TEST(playerrepository.get_player(0)->is_turn());
        BOOST_TEST(!playerrepository.get_player(1)->is_turn());
        playerrepository.change_to_next_player();
        BOOST_TEST(playerrepository.get_current_player()->get_id()==1);
        BOOST_TEST(!playerrepository.get_player(0)->is_turn());
        BOOST_TEST(playerrepository.get_player(1)->is_turn());

    }
    BOOST_AUTO_TEST_CASE (CreatePlayerTest)
    {
        PlayerRepository playerrepository (3,names,worldRepository,nullptr, nullptr);
        BOOST_CHECK(playerrepository.create_player(x,y,representation,name, current_player,health,stars,id)); //sprawdzamy, czy create_player zwróciło true
        PlayerPtr player1= playerrepository.get_players().back();
        BOOST_TEST(player1->get_name()=="Adam");
        BOOST_TEST(player1->get_id()==3);
        std::string name2="Kasia";
        playerrepository.create_player(x+1,y+1,representation,name2, current_player,health,stars,id);
        PlayerPtr player2= playerrepository.get_players().back();
        BOOST_TEST(playerrepository.get_players_number()==5);
        BOOST_TEST(player2->get_name()=="Kasia");
        BOOST_TEST(player2->get_id()==4);
        BOOST_TEST(playerrepository.get_player(4)->get_name()=="Kasia");
    }
    BOOST_AUTO_TEST_CASE (RemovePlayerTest)
    {
    PlayerRepository pr (2, names, worldRepository,nullptr, nullptr);
    BOOST_TEST (pr.get_players_number()==2);
    BOOST_TEST(pr.get_current_player()->get_id()==0);
    PlayerPtr p=pr.get_current_player();
    pr.remove_current_player();
    BOOST_TEST(pr.get_players_number()==1);
    BOOST_TEST(pr.get_current_player()!=p);
    }




BOOST_AUTO_TEST_SUITE_END()