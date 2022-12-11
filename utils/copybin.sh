#!/bin/bash

cd $1
ip=$2
user=$3
pass=$4

pwd

ping -c2 $ip > /dev/null
if [ $? -ne 0 ]; then
  echo "Error - no target found $ip !"
  exit 1
fi

rsync -vr --rsh="sshpass -p $pass ssh -o StrictHostKeyChecking=no -l $user" include/* $ip:/usr/local/include
rsync -vr --rsh="sshpass -p $pass ssh -o StrictHostKeyChecking=no -l $user" bin/* $ip:/usr/local/bin
rsync -vr --rsh="sshpass -p $pass ssh -o StrictHostKeyChecking=no -l $user" lib/* $ip:/usr/local/lib
echo "install success on $ip!"