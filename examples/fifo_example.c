
#include<stdlib.h>
#include<stdio.h>
#include<cilktc.h>
#include<ktcpipe.h>

int fifochannel(fifo);

task reader() {
    int fifo_read;
    while (1) {
        cread(fifo, fifo_read);
        printf("Got fifo:%i\n", fifo_read);
    }
}

task writer() {
    int write = 0;
    while(1) {
        cwrite(fifo, write);
        write++;
        sdelay(100,ms);
    }
}

void main(){
    cinit(fifo,0);
    reader();
    writer();
}

