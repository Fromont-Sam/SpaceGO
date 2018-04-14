# Set a minimum CMake vversion
cmake_minimum_required(VERSION 3.0.2)

# Define our project name
project(SpaceGO)

# Look for the SFML components we're interested in
find_package(SFML 2.4 COMPONENTS audio graphics window system REQUIRED)

# Define a list of our source files
set(SOURCES
    Account.cpp
    Account.h
    Bonus.cpp
    Bonus.h
    Config.cpp
    Config.h
    Credits.cpp
    Credits.h
    Ennemy.cpp
    Ennemy.h
    Game.cpp
    Game.h
    Laser.cpp
    Laser.h
    Menu.cpp
    Menu.h
    Meteor.cpp
    Meteor.h
    MyButton.cpp
    MyButton.h
    MyCheckbox.cpp
    MyCheckbox.h
    MyProgressBar.cpp
    MyProgressBar.h
    MyWindow.cpp
    MyWindow.h
    Obstacle.cpp
    Obstacle.h
    Panel.cpp
    Panel.h
    Score.cpp
    Score.h
    Settings.cpp
    Settings.h
    Shop.cpp
    Shop.h
    Spaceship.cpp
    Spaceship.h
    Splashscreen.cpp
    Splashscreen.h
    Star.cpp
    Star.h
    main.cpp
    resource.rc
)

# Define our target executable based on the source files above
add_executable(SpaceGO ${SOURCES})

# Link our executable to SFML and its dependencies
target_link_libraries(SpaceGO sfml-audio sfml-graphics sfml-window sfml-system)

# Set our source directory as the startup directory for debugging
set_target_properties(SpaceGO PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
