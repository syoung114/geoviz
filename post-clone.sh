#!/bin/bash
#go to https://glad.dav1d.de/ to generate the files and copy the link for glad.zip. That is what $1 is.
git submodule update --init --recursive; cd lib/glad/; curl $1 -o "glad.zip"; unzip glad.zip; rm glad.zip; cd ../../