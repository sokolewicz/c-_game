#include <boost/test/unit_test.hpp>
#include <managers/SaveLoadManager.h>
#include <model/WorldRepository.h>
#include <model/PlayerRepository.h>
#include <model/InteractiveFieldAndMonsterRepository.h>

struct SaveLoadManagerFixture{

    InteractiveFieldAndMonsterRepository* repo1;
    InteractiveFieldAndMonsterRepository* repo2;

    PlayerRepository* playerRepo1;
    PlayerRepository* playerRepo2;

    WorldRepository* worldRepo1;
    WorldRepository* worldRepo2;

    SaveLoadManager* slm1;
    SaveLoadManager* slm2;

    InputManager* input;

    SaveLoadManagerFixture()
    {


        worldRepo1 = new WorldRepository(&playerRepo1);
        worldRepo2 = new WorldRepository(&playerRepo1);
        playerRepo1 = new PlayerRepository(nullptr, nullptr,worldRepo1);
        playerRepo2 = new PlayerRepository(nullptr, nullptr,worldRepo2);
        repo1 = new InteractiveFieldAndMonsterRepository(worldRepo1,playerRepo1);
        repo2 = new InteractiveFieldAndMonsterRepository(worldRepo2,playerRepo2);

        worldRepo1->set_new_world_size(20,20);
        worldRepo1->create_field(5,5,'_', true);
        playerRepo1->create_player(6,6,'P',"Player", true,100,0,1);
        repo1->create_monster(9,9,'M');
        repo1->create_interactive_field(14,14,'?');
        input = new InputManager();
        slm1 = new SaveLoadManager(worldRepo1,playerRepo1,repo1,input);

    }
    ~SaveLoadManagerFixture()
    {
        delete worldRepo1, worldRepo2, playerRepo1, playerRepo2, repo1, repo2, input, slm2, slm1;
    }
};

BOOST_FIXTURE_TEST_SUITE(SaveLoadManagerSuite, SaveLoadManagerFixture)

    BOOST_AUTO_TEST_CASE(SaveTest)
    {
       BOOST_TEST_REQUIRE(slm1->save_game());
    }

    BOOST_AUTO_TEST_CASE(LoadingTest)
    {
        slm2 = new SaveLoadManager(worldRepo2, playerRepo2, repo2, input);

        BOOST_TEST_REQUIRE(slm2->load_game());

        BOOST_TEST_REQUIRE(worldRepo2->get_world_size_x() == 20);
        BOOST_TEST_REQUIRE(worldRepo2->get_world_size_y() == 20);
        BOOST_TEST_REQUIRE(worldRepo2->get_number_of_fields() == 1);
        BOOST_TEST_REQUIRE(worldRepo2->get_field(0)->get_x() == 5);
        BOOST_TEST_REQUIRE(worldRepo2->get_field(0)->get_y() == 5);
        BOOST_TEST_REQUIRE(worldRepo2->get_field(0)->get_representation() == '_');
        BOOST_TEST_REQUIRE(worldRepo2->get_field(0)->get_interaction() == nullptr);
        BOOST_TEST_REQUIRE(worldRepo2->get_field(0)->is_enable_movement());

        BOOST_TEST_REQUIRE(playerRepo2->get_players_number() == 1);
        BOOST_TEST_REQUIRE(playerRepo2->get_current_player()->get_x() == 6);
        BOOST_TEST_REQUIRE(playerRepo2->get_current_player()->get_y() == 6);
        BOOST_TEST_REQUIRE(playerRepo2->get_current_player()->get_representation() == 'P');
        BOOST_TEST_REQUIRE(playerRepo2->get_current_player()->get_health() == 100);
        BOOST_TEST_REQUIRE(playerRepo2->get_current_player()->get_stars() == 0);
    }

BOOST_AUTO_TEST_SUITE_END()