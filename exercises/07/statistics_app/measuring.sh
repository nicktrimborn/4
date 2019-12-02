#!/bin/sh

APP=/mnt/microsd/statistics
AMOUNT=50  
# delay=0
( tail -f /dev/irqgen | tee /root/latencies.csv | $APP ) &
#sleep 2
# ( tail -f /dev/irqgen | tee /root/latencies.csv ) &
echo "entering for loops"
# for i in $(seq 1 10); do
    # echo $seq
    for line in $(seq 0 15); do
        for delay in 0 100 1000 10000 ; do
            # echo $delay
            tgt=$(($AMOUNT + $(cat /sys/kernel/irqgen/total_handled)))
            echo $line > /sys/kernel/irqgen/line
            echo $delay > /sys/kernel/irqgen/delay
            echo $AMOUNT > /sys/kernel/irqgen/amount

            # sleep 0.2
            while : ; do
                if [ $tgt -le $(cat /sys/kernel/irqgen/total_handled) ]  ; then
                    break
                fi
                sleep 0.1
            done
        done
    done
# done

sleep 5

kill -INT %1


