#!/bin/sh

# Note: this script only supports Ubuntu 20.04.

mkdir -p install && cd install

# Useful packages:
apt-get -y install \
	curl \
	wget \
	git \
	make \
	cmake \
	xz-utils \
	time \
	bc

# Ada
apt-get -y install gnat

# C
apt-get -y install gcc clang

# C++
apt-get -y install g++

# Go:
GO_VERSION=1.20.2
wget https://go.dev/dl/go$GO_VERSION.linux-amd64.tar.gz
rm -rf /usr/local/go && tar -C /usr/local -xzf go$GO_VERSION.linux-amd64.tar.gz
rm go$GO_VERSION.linux-amd64.tar.gz
echo "export PATH=${PATH}:/usr/local/go/bin" >> ~/.bashrc && . ~/.bashrc

# # Java 8:
# apt-get -y install openjdk-8-jdk

# Java 17:
apt-get -y install openjdk-17-jdk

# Node via nvm:
NVM_VERSION=0.39.3
wget -qO- https://raw.githubusercontent.com/nvm-sh/nvm/v$NVM_VERSION/install.sh | bash
. ~/.bashrc
# To be installed node versions:
nvm install v12.22.12
nvm install v18.14.2

# Nim:
curl https://nim-lang.org/choosenim/init.sh > nim_init.sh && sh nim_init.sh -y
rm -rf $(ls -d /tmp/choosenim-*) # cleanups
echo "export PATH=${PATH}:${HOME}/.nimble/bin" >> ~/.bashrc && . ~/.bashrc

# OCaml:
apt-get -y install ocaml

# Python 3:
apt-get -y install python3-pip

# Rust:
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs > rust_install.sh && sh rust_install.sh -y

# Swift:
SWIFT_VERSION=5.8
apt-get -y install wget clang libicu-dev build-essential pkg-config libxml2 tzdata zlib1g-dev
wget https://download.swift.org/swift-$SWIFT_VERSION-release/ubuntu2004/swift-$SWIFT_VERSION-RELEASE/swift-$SWIFT_VERSION-RELEASE-ubuntu20.04.tar.gz
mkdir -p swift
tar -xvzf swift-$SWIFT_VERSION-RELEASE-ubuntu20.04.tar.gz -C swift
rm swift-$SWIFT_VERSION-RELEASE-ubuntu20.04.tar.gz
echo "export PATH=${PATH}:${PWD}/swift/swift-${SWIFT_VERSION}-RELEASE-ubuntu20.04/usr/bin" >> ~/.bashrc && . ~/.bashrc

# v:
git clone --depth 1 https://github.com/vlang/v && cd v && make && cd ..
