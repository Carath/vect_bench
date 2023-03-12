FROM ubuntu:20.04

ARG http_proxy
ARG https_proxy
ENV http_proxy $http_proxy
ENV https_proxy $https_proxy

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get -y update
RUN apt-get -y upgrade

WORKDIR /app

COPY install.sh .

# This script only supports Ubuntu.
RUN sh install.sh

# Not using a volume for better isolation:
COPY . .
