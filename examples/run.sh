#!/bin/bash
cp $1 temp.c
of="${1%.c}"
../bin/ktc --enable-ext0 --link $1 -w --verbose -lpthread
mv a.out ${of}
if [ $? = 0 ]; then
    mv temp.c $1
    sudo ./${of}
fi
rm *.dot
