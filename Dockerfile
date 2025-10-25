FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# Instalar dependencias necesarias y repositorio oficial de Kitware
RUN apt-get update && apt-get install -y \
    software-properties-common \
    build-essential \
    wget \
    gnupg && \
    wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor -o /usr/share/keyrings/kitware-archive-keyring.gpg && \
    echo 'deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ jammy main' | tee /etc/apt/sources.list.d/kitware.list >/dev/null && \
    apt-get update && \
    apt-get install -y cmake && \
    apt-get clean

WORKDIR /app

COPY . .

RUN cmake . && make

ENTRYPOINT ["./TP_UTN_Campus"]
