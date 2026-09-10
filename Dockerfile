FROM ubuntu:18.04

ENV DEBIAN_FRONTEND=noninteractive

RUN sed -i 's/archive.ubuntu.com/mirrors.tuna.tsinghua.edu.cn/g' /etc/apt/sources.list && \
    sed -i 's/security.ubuntu.com/mirrors.tuna.tsinghua.edu.cn/g' /etc/apt/sources.list

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gdb \
    wget \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

COPY cmake-3.24.4-linux-x86_64.tar.gz /tmp/
RUN tar -xzf /tmp/cmake-3.24.4-linux-x86_64.tar.gz -C /opt \
    && ln -sf /opt/cmake-3.24.4-linux-x86_64/bin/cmake /usr/local/bin/cmake \
    && ln -sf /opt/cmake-3.24.4-linux-x86_64/bin/ctest /usr/local/bin/ctest \
    && ln -sf /opt/cmake-3.24.4-linux-x86_64/bin/cpack /usr/local/bin/cpack \
    && rm -f /tmp/cmake-3.24.4-linux-x86_64.tar.gz

RUN cmake --version