#!/bin/sh


valid=N
echo "update ? (N/y)"
read valid

if [ $valid = "Y" ] || [ $valid = "Yes" ] || [ $valid = "yes" ] || [ $valid = "y" ]
then
  curl http://files.vhugot.com/Restricted/Python/PythonNotesSC.pdf --output cours.pdf
elif [ $valid = "N" ] || [ $valid = "No" ] || [ $valid = "no" ] || [ $valid = "n" ]
then
  return 1
else
  echo $valid is invalid
fi