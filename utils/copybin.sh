#!/bin/bash

cd $1
ip_addr=$2
user=$3
pass=$4

pwd

ping -c2 $ip_addr > /dev/null
if [ $? -ne 0 ]; then
  echo "Error - no target found $ip_addr !"
  exit 1
fi

# rsync -vr --rsh="sshpass -p $pass ssh -o StrictHostKeyChecking=no -l $user" include/* $ip_addr:/usr/local/include
rsync -vr --rsh="sshpass -p $pass ssh -o StrictHostKeyChecking=no -l $user" bin/* $ip_addr:/usr/local/bin
rsync -vr --rsh="sshpass -p $pass ssh -o StrictHostKeyChecking=no -l $user" lib/* $ip_addr:/usr/local/lib
echo "install success!"