cmake_minimum_required(VERSION 3.4)
project(Library)

set(SOURCE_FILES
        src/managers/GameManager.cpp
        src/model/Field.cpp
        src/model/Interaction.cpp
        src/model/MovableObject.cpp
        src/model/Player.cpp
        src/model/MovableMonster.cpp
        src/model/InteractionWithMonster.cpp
        src/model/InteractiveField.cpp
        src/model/PlayerRepository.cpp
        src/managers/OutputManager.cpp
        src/model/WorldRepository.cpp
        src/managers/InputManager.cpp
        src/model/InteractiveFieldAndMonsterRepository.cpp
        src/model/PlayerRepository.cpp
        src/model/InteractiveField.cpp
        src/managers/SaveLoadManager.cpp
        src/managers/InputManager.cpp
        src/model/RandomInteraction.cpp

        )

add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include)



enable_testing()

set(Boost_USE_MULTITHREADED ON)
find_package (Boost COMPONENTS "unit_test_framework" REQUIRED)

include_directories(

        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)


set(SOURCE_TEST_FILES
        test/master.cpp
        test/FieldTest.cpp
        test/InteractionTest.cpp
        test/MovableObjectTest.cpp
        test/PlayerRepositoryTest.cpp
        test/InteractiveFieldAndMonsterRepositoryTest.cpp
        test/WorldRepositoryTest.cpp
        test/SaveLoadManagerTest
        ${SOURCE_FILES}
        )

add_executable (LibraryTest ${SOURCE_TEST_FILES})

#dołącz bibliotekę z testowanymi klasami oraz bibliotekę boost.test do programu testów
target_link_libraries (
        LibraryTest
        Library
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )

#dodaj test TestBiblioteki1. Instrukcji cmake add_test może być wiele.
#Dodatkowe parametry wpływają na szczegółowość generowanego raportu. Standardowo znajduje się on w Testing/Temporary.
add_test(LibraryTest LibraryTest
        --report_level=detailed
        --log_level=all
        --color_output=yes
        )

add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 11)