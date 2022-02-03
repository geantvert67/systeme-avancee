#!/bin/bash

docker-compose build

docker-compose up

#docker run --name jenkins-service -p 8080:8080 -p 50000:50000 -v ~/jenkins:/var/jenkins_home -v /var/run/docker.sock:/var/run/docker.sock -v /usr/local/bin/docker:/usr/local/bin/docker jenkins/jenkins