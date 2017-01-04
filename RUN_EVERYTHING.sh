#!/bin/bash
cd "$(dirname "$0")"

builds/Server &

sleep 2s

for i in $(seq 10)
do
	builds/Beacon boat_$i &
	sleep 1s
done

cd builds #for working directory of Client
./Client
killall -SIGKILL Beacon
killall -SIGKILL Server
