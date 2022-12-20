#!/bin/bash

cd $1
ip=$2
user=$3

pwd

ping -c2 $ip > /dev/null
if [ $? -ne 0 ]; then
  echo "Error - no target found $ip !"
  exit 1
fi

scp -r include/* $user@$ip:/usr/local/include
scp -r bin/*     $user@$ip:/usr/local/bin
scp -r lib/*     $user@$ip:/usr/local/lib
scp -r etc/*     $user@$ip:/usr/local/etc

echo "install success on $ip!"