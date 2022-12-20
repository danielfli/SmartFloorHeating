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

rsync -arv --update --rsh="sshpass -p $pass ssh -o StrictHostKeyChecking=no -l $user" include/* $ip:/usr/local/include
rsync -arv --update  --rsh="sshpass -p $pass ssh -o StrictHostKeyChecking=no -l $user" bin/* $ip:/usr/local/bin
rsync -arv --update  --rsh="sshpass -p $pass ssh -o StrictHostKeyChecking=no -l $user" lib/* $ip:/usr/local/lib
rsync -arv --update  --rsh="sshpass -p $pass ssh -o StrictHostKeyChecking=no -l $user" etc/* $ip:/usr/local/etc
echo "install success on $ip!"