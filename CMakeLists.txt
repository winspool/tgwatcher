
cmake_minimum_required( VERSION 3.12 )


if ( NOT CMAKE_PROJECT_NAME )
    project( tgwatcher )
endif( )

set( DESCRIPTION "The Game Watcher: Checking remote system (game) ui status" )


#### The other stuff

add_executable(tgwatcher src/tgwatcher.c )


