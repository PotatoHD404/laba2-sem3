#!/usr/bin/env bash

# Installing cmake, gtest and valgrind with other dependencies
sudo apt update && \
sudo apt install -y software-properties-common lsb-release wget && \
sudo apt install -y tzdata ssh git && \
sudo apt clean all

mkdir "$HOME"/gtest_build && cd "$HOME"/gtest_build || exit

wget --no-check-certificate -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | \
gpg --dearmor - | \
sudo tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null && \
sudo apt-add-repository "deb https://apt.kitware.com/ubuntu/ $(lsb_release -cs) main" && \
sudo apt install -y kitware-archive-keyring && \
sudo apt update

sudo apt install -y cmake build-essential gdb libgtest-dev libboost-dev libboost-program-options-dev valgrind lcov

# Setting up emscripten for compiling to webassembly

cd "$HOME" && git clone https://github.com/emscripten-core/emsdk.git && cd "$HOME"/emsdk || exit

git pull && \
./emsdk install latest && \
./emsdk activate latest && \
source ./emsdk_env.sh && \
echo 'source "$HOME/emsdk/emsdk_env.sh"' >> $HOME/.bash_profile

#sudo useradd -m user && \
#yes password | passwd user
#
#sudo usermod -s /bin/bash user && usermod -a -G sudo user

#(echo 'LogLevel DEBUG2'; \
#echo 'PermitRootLogin yes'; \
#echo 'PasswordAuthentication yes'; \
#echo 'Subsystem sftp /usr/lib/openssh/sftp-server'; \
#) > /etc/ssh/sshd_config_test && \
#mkdir /run/sshd

# /usr/sbin/sshd -D -e -f /etc/ssh/sshd_config_test



