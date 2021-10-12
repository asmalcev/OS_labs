#!/bin/bash

last_filename=""

help_text="\
Usage: bash script.sh [flags] [filename1 word1 ...]

Avaible flags:
        -h, --help # Display helpt text and exit\
"
error_text="\
Incorrect flag:

Use -h, --help flag to get help information\
"

count_of_created_files=0

[ -f report ] && rm report

for i in $*
do
	if   [[ $i =~ --.* ]]; then
		case $i in
			--help)
				echo "$help_text"
				exit 0
			;;
			*)
				echo "$error_text"
				exit 0
		esac
	elif [[ $i =~ -.* ]]; then
		case $i in
                        -h)
                                echo "$help_text"
				exit 0
                        ;;
                        *)
				echo "$error_text"
				exit 0
                esac
	else
		if [[ -z $last_filename ]]; then
			last_filename=$i 
		else
			if [ -f $last_filename ]; then
				echo "$last_filename exists" >> report
			else
				echo "$i" > $last_filename
				echo "$last_filename created" >> report
				let "count_of_created_files += 1"
			fi
			last_filename="" 
		fi
	fi
done

echo "
Count of created files: $count_of_created_files" >> report
