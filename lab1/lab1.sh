#!/bin/bash


echo "Alfeder Igor, 718-1"
echo -e "\n----- Creating a CD image -----\n\n"

PROGRUN=true

while $PROGRUN; do

	read -p "Enter the directory path: " DIR

	if ! [ -d "$DIR" ]; then
		echo -e "ERROR: Directory not found\n"
		continue
	fi


	read -p "Enter the image name: " NAME

	if [ "$NAME" = "" ]; then
		echo -e "ERROR: Empty name\n"
		continue
	fi


	# Adding data to image name
	if [ -e "$NAME.iso" ]; then
		NAME="$NAME-`date -I`"
	fi

	NAME="$NAME.iso"
	echo -e "\nFinal image name: $NAME"

	echo -e "CREATING IMAGE\n"
	genisoimage -o $NAME $DIR

	echo -e "##   IMAGE CREATED   ##\n\n"

	read -p "Create image retry? [y/n]: " SELECT
	if ! [ "$SELECT" = "y" ]; then
        	PROGRUN=false
    	fi

done



