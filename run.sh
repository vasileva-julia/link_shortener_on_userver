#!/bin/bash

BDIR="build_release"
DIR="$PWD/$BDIR"

groupadd --gid 2000 node && useradd --uid 2000 --gid node --shell /bin/bash --create-home node
usermod -u $1 node groupmod -g $1 node

usermod -u 1000 node && groupmod -g 1000 node

if [[ -d "$DIR" ]]
then
    echo "The directory $DIR exists."
else
    su node --command "mkdir $BDIR"
fi
cd $BDIR

su node --command "cmake -DCMAKE_BUILD_TYPE=Release .."
su node --command "make start-link_shortener"