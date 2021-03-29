# WindRm

## A reMarkable UI for Ash Wolf's great Psion 5mx (Windermere) emulator.

You will need a ROM. I personally own a Psion 5mx and will not be distributing a ROM file.

To run:
```
$ ./WindRm [name of ROM file e.g. Sys$rom.bin] 
```

First boot takes several minutes on the reMarkable, but I've added support for saving state so once booted, you can exit with the save button and full state will be written to a 32MB `psion.out` file in the same directory. On future launches, `WindRm` will look for the `psion.out` file and restore that state.