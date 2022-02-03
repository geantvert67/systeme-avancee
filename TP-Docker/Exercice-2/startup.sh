#!/bin/bash

docker build -t scratchjenkins .

docker run -it scratchjenkins