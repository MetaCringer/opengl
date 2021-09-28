#!/bin/bash
envfile=$1
shift 1
count=0
args=
while [ $count -lt $# ]
    do
        (( count++ ))
        args="${args} ${!count}"
    done
echo ${args}
env $(cat ${envfile}) make -e ${args}
# TODO set up optional to specify file of environments