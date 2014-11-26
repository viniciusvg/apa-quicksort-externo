#!/bin/bash
cat arquivo.bin | hexdump -v -e '/4  "%d\n"'
