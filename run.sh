#!/bin/bash

groupadd --gid 2000 user && useradd --uid 2000 --gid user --shell /bin/bash --create-home user
usermod -u $1 user groupmod -g $1 user

usermod -u 1000 user && groupmod -g 1000 user

sleep infinity