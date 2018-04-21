# disk_write_performance

## Description
disk_write_performance is util for testing speed of read/write depending on the block size

## Usage
```
disk_write_performance <filename> <blocksize in bytes> <writesize in bytes>
```

Output:
```
<write_time_in_microseconds> <read_time_in_microseconds>
```

# build_graphics.sh

## Description
build_graphics.sh is util for generate two plot: read performance plot, write performance plot
The util uses gnuplot and disk_write_performance utils

Example of plots:




The graphs show that it is best to use block size >= 4096

