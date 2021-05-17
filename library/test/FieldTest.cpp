#include <boost/test/unit_test.hpp>
#include <model/Field.h>
#include <model/InteractiveField.h>
#include <managers/GameManager.h>
#include <model/RandomInteraction.h>
#include <model/WorldRepository.h>

struct FieldTestFixture{
    RandomInteraction *interaction;
    PlayerRepository *playerRepository;
    WorldRepository *worldRepository;
    std::string message;
    std::vector<std::string> names={"Adan", "Tomek", "Kasia"};
    FieldTestFixture()
    {
        worldRepository=new WorldRepository(20,20,5,&playerRepository);
        playerRepository=new PlayerRepository(3, names,worldRepository, nullptr,nullptr);
        interaction=new RandomInteraction(message,playerRepository);
    }
    ~FieldTestFixture()
    {   delete worldRepository;
        delete interaction;
        delete playerRepository;
    }

};
    BOOST_FIXTURE_TEST_SUITE(FieldSuite, FieldTestFixture)


    BOOST_AUTO_TEST_CASE(FieldConstructorTest)
    {
    Field field {2,3,'*', true};
        BOOST_TEST (field.get_x()==2);
        BOOST_TEST (field.get_y()==3);
        BOOST_TEST (field.get_representation()=='*');
        BOOST_TEST (field.get_coordinates()=="(2, 3)");
        BOOST_TEST (field.is_enable_movement()==true);
    }
    BOOST_AUTO_TEST_CASE(FieldGetAllInfoTest)
    {
        Field field {2,3,'*', true};
        BOOST_TEST (field.get_all_info()=="Field (2, 3) * enable movement= 1");

    }


    BOOST_AUTO_TEST_CASE(InteractiveFieldConstructorTest)
    {
        InteractiveField interactivefield (3,4,'&',true,interaction);
        BOOST_TEST (interactivefield.get_interaction()==interaction);

    }




BOOST_AUTO_TEST_SUITE_END()