# Using ubuntu:20.04 image as base of this container
FROM ubuntu:20.04

# Setting bash as default interpriter

SHELL ["/bin/bash", "-c"]

# Installing cmake, gtest and valgrind with other dependencies

RUN DEBIAN_FRONTEND="noninteractive" apt update && \
apt install -y software-properties-common lsb-release wget && \
apt install -y tzdata ssh git rsync grsync && \
apt clean all

WORKDIR /gtest_build

RUN wget --no-check-certificate -O - https://apt.kitware.com/values/kitware-archive-latest.asc 2>/dev/null | \
gpg --dearmor - | \
tee /etc/apt/trusted.gpg.d/kit^[[2~ware.gpg >/dev/null && \
apt-add-repository "deb https://apt.kitware.com/ubuntu/ $(lsb_release -cs) main" && \
apt install -y kitware-archive-keyring && \
DEBIAN_FRONTEND="noninteractive" apt update

RUN apt install -y cmake build-essential gdb libgtest-dev libboost-dev libboost-program-options-dev valgrind lcov

#docker buildx build --platform linux/amd64
#cmake -DCMAKE_BUILD_TYPE=Release /usr/src/gtest && \
#cmake --build .
# && \
#mv lib*.a /usr/lib


# Creating user and setting up ssh

RUN useradd -m user && \
yes password | passwd user

RUN ( \
echo 'LogLevel DEBUG2'; \
echo 'PermitRootLogin yes'; \
echo 'PasswordAuthentication yes'; \
echo 'Subsystem sftp /usr/lib/openssh/sftp-server'; \
) > /etc/ssh/sshd_config_test && \
mkdir /run/sshd

# Setting up emscripten for compiling to webassembly

WORKDIR /

RUN git clone https://github.com/emscripten-core/emsdk.git

WORKDIR /emsdk

RUN git pull && \
./emsdk install tot
RUN ./emsdk activate tot
RUN source ./emsdk_env.sh && \
echo 'source "/home/user/emsdk/emsdk_env.sh"' >> /home/user/.bash_profile


# Setting up working directory for app

WORKDIR /src

# Setting up entrypoint for connecting via ssh

CMD ["/usr/sbin/sshd", "-D", "-e", "-f", "/etc/ssh/sshd_config_test"]