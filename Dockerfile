FROM ubuntu:22.04 AS build
RUN apt-get update && apt-get install -y build-essential qtbase5-dev qt5-qmake libqt5charts5-dev libcurl4-openssl-dev
COPY . /src
WORKDIR /src
