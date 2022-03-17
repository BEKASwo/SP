FROM ubuntu:latest

RUN apt-get update && apt-get install -y g++

WORKDIR /home

COPY ./main_prog.cpp ./
COPY ./sum.s ./

RUN g++ ./main_prog.cpp -c -o main_prog.o
RUN as sum.s -o sum.o
RUN g++ main_prog.o sum.o -o prog

RUN rm sum.o main_prog.o
