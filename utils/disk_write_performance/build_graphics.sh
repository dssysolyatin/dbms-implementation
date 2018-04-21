#!/bin/bash

COMMAND_PATH=./../../disk_write_performance

TMP_FILE=$(mktemp)
TMP_DIR=$(mktemp -d)

BLOCK_SIZES=(1 16 32 64 128 256 512 1024 2048 4096 8192 16384)
WRITE_PLOT_COMMAND="set term png;set key left top;set title \"Write performance\";set xlabel \"MB\";set ylabel \"Time of writes, seconds\";set output \"write_plot.png\"; plot "
READ_PLOT_COMMAND="set term png;set key left top;set title \"Read performance\";set xlabel \"MB\";set ylabel \"Time of read, seconds\";set output \"read_plot.png\"; plot "

for BLOCK_SIZE in "${BLOCK_SIZES[@]}"
do
    for WRITE_SIZE_MB in $(seq 10 10 100)
    do
        WRITE_SIZE_BYTES=$((1024*1024*$WRITE_SIZE_MB))
        COMMAND_RESULT=$($COMMAND_PATH $TMP_FILE $BLOCK_SIZE $WRITE_SIZE_BYTES)
        echo "$WRITE_SIZE_MB $COMMAND_RESULT" >> ${TMP_DIR}/${BLOCK_SIZE}.txt
    done

    LINE_COLOR=$(openssl rand -hex 3)
    WRITE_PLOT_COMMAND="${WRITE_PLOT_COMMAND} \"${TMP_DIR}/${BLOCK_SIZE}.txt\" using (\$1):(\$2/1000000) title \"${BLOCK_SIZE} bytes\" with lines lw 2 lc rgb \"#${LINE_COLOR}\", "
    READ_PLOT_COMMAND="${READ_PLOT_COMMAND} \"${TMP_DIR}/${BLOCK_SIZE}.txt\" using (\$1):(\$3/1000000) title \"${BLOCK_SIZE} bytes\" with lines lw 2 lc rgb \"#${LINE_COLOR}\", "
done;

gnuplot -e "${WRITE_PLOT_COMMAND}"
gnuplot -e "${READ_PLOT_COMMAND}"

rm -rf ${TMP_FILE}
rm -rf ${TMP_DIR}

