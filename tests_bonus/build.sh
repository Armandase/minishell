#!/bin/bash

gcc wildcards.c ../builtins/*.c -o exec -g -L../libft -lft
#./exec ls "*.c"
