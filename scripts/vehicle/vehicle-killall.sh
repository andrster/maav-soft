#!/bin/sh

SSH_OPTS="-t"

# for h in $(cat res/admin/hosts)
# do
# 	ping -c 1 -W 5 ${h} > /dev/null

# 	if [ $? -eq 0 ]
# 	then
# 		ssh ${SSH_OPTS} maav@${h} "/home/maav/software/software-killall"
# 	fi
# done
ssh ${SSH_OPTS} maav@192.168.1.61 "/home/maav/software/software-killall"

