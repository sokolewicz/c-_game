#include <boost/test/unit_test.hpp>
#include <model/InteractiveFieldAndMonsterRepository.h>

struct WorldRepositoryFixture{

    InteractiveFieldAndMonsterRepository* repo1;

    PlayerRepository* playerRepo;
    WorldRepository* worldRepo1;
    WorldRepository* worldRepo2;

    WorldRepositoryFixture()
    {

        worldRepo1 = new WorldRepository(15,15,0,&playerRepo);
        worldRepo2 = new WorldRepository(&playerRepo);
        playerRepo = new PlayerRepository(nullptr, nullptr,worldRepo1);
        repo1 = new InteractiveFieldAndMonsterRepository(worldRepo1,playerRepo);
    }
    ~WorldRepositoryFixture ()
    {
        delete worldRepo1, worldRepo2, playerRepo, repo1;
    }
};

BOOST_FIXTURE_TEST_SUITE(WorldRepositorySuite, WorldRepositoryFixture)

    BOOST_AUTO_TEST_CASE(RepoConstructorTest)
    {
        BOOST_TEST_REQUIRE(worldRepo1->get_world_size_x() == 15);
        BOOST_TEST_REQUIRE(worldRepo1->get_world_size_y() == 15);
        BOOST_TEST_REQUIRE(worldRepo1->get_number_of_fields() == 225);

        BOOST_TEST_REQUIRE(worldRepo2->get_world_size_x() == 0);
        BOOST_TEST_REQUIRE(worldRepo2->get_world_size_y() == 0);
        BOOST_TEST_REQUIRE(worldRepo2->get_number_of_fields() == 0);


    }

    BOOST_AUTO_TEST_CASE(RepoSetAndCreateMethodsTest)
    {
        worldRepo2->set_new_world_size(15,15);
        BOOST_TEST_REQUIRE(worldRepo2->create_field(5,5,'_', true));
        BOOST_TEST_REQUIRE(worldRepo2->create_field(6,6,'#', false));
        BOOST_TEST_REQUIRE(worldRepo2->get_number_of_fields() == 2);
        BOOST_TEST_REQUIRE(worldRepo2->get_world_size_x() == 15);
        BOOST_TEST_REQUIRE(worldRepo2->get_world_size_y() == 15);
        BOOST_TEST_REQUIRE(worldRepo2->get_field(0)->get_x() == 5);
    }

    BOOST_AUTO_TEST_CASE(RepoOtherMethodsTest)
    {
        worldRepo2->create_field(7,7,'_', true);
        worldRepo2->create_field(8,8,'#', false);
        BOOST_TEST_REQUIRE(!worldRepo2->is_field_empty(88,68));
        BOOST_TEST_REQUIRE(worldRepo2->is_field_empty(7,7));
        BOOST_TEST_REQUIRE(!worldRepo2->is_field_empty(8,8));
    }

BOOST_AUTO_TEST_SUITE_END()