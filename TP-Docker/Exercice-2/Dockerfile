FROM tomcat

EXPOSE  8080

RUN apt-get update

COPY ./jenkins.war /usr/local/tomcat/webapps

CMD ["catalina.sh", "run"]