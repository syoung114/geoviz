#!/bin/bash
git submodule update --init --recursive; cd lib/glad/; curl https://glad.dav1d.de/generated/tmpid3fabulglad/glad.zip -o "glad.zip"; unzip glad.zip; rm glad.zip