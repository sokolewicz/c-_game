#include <boost/test/unit_test.hpp>
#include <model/InteractiveFieldAndMonsterRepository.h>

struct InteractiveFieldAndMonsterRepositoryFixture{

    InteractiveFieldAndMonsterRepository* repo1;
    InteractiveFieldAndMonsterRepository* repo2;

    PlayerRepository* playerRepo;
    WorldRepository* worldRepo;

    InteractiveFieldAndMonsterRepositoryFixture()
    {

        worldRepo = new WorldRepository(15,15,0,&playerRepo);
        playerRepo = new PlayerRepository(nullptr, nullptr,worldRepo);
        repo1 = new InteractiveFieldAndMonsterRepository(worldRepo,playerRepo);
        repo2 = new InteractiveFieldAndMonsterRepository(worldRepo,playerRepo,10,5,'M','?');
    }
    ~InteractiveFieldAndMonsterRepositoryFixture()
    {
        delete worldRepo, playerRepo, repo1, repo2;
    }
};


BOOST_FIXTURE_TEST_SUITE(InteractiveFieldAndMonsterRepositorySuite, InteractiveFieldAndMonsterRepositoryFixture)

    BOOST_AUTO_TEST_CASE(RepoConstructorTest)
    {
        BOOST_TEST_REQUIRE(repo2 -> get_interactive_fields().size() == 5);
        BOOST_TEST_REQUIRE(repo2 -> get_monsters().size() == 10);
        BOOST_TEST_REQUIRE(repo2 -> get_interactive_fields()[0]->get_representation() == '?');
        BOOST_TEST_REQUIRE(repo2 -> get_monsters()[0]->get_representation() == 'M');
    }

    BOOST_AUTO_TEST_CASE(RepoCreateMethodsTest)
    {
        BOOST_TEST_REQUIRE(repo1->create_interactive_field(5,5,'?'));
        BOOST_TEST_REQUIRE(repo1 -> get_interactive_fields().size() == 1);
        BOOST_TEST_REQUIRE(repo1->create_monster(6,6,'M'));
        BOOST_TEST_REQUIRE(repo1 -> get_monsters().size() == 1);
        int x = repo1->get_monsters()[0]->get_x();
        int y = repo1->get_monsters()[0]->get_y();

    }

BOOST_AUTO_TEST_SUITE_END()