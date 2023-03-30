#!/bin/sh

# Note: this script only supports Ubuntu.

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
echo 'export PATH="${PATH}:/usr/local/go/bin"' >> ~/.bashrc

# Java 8:
apt-get -y install openjdk-8-jdk

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
echo 'export PATH="${PATH}:${HOME}/.nimble/bin"' >> ~/.bashrc

# Python 3:
apt-get -y install python3-pip

# Rust:
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs > rust_install.sh && sh rust_install.sh -y

# v:
git clone --depth 1 https://github.com/vlang/v && cd v && make && cd ..
