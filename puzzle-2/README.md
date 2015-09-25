# Second Puzzle

skills required:

* patience!
* port scanning
* CLI usage of steghide

## Todo

* make clue file
* embed new file in pic (use real password)
* get a better pic (me with hoodie)

## Location

hidden in chillout area 

## UX

* find the access point given in first solution, 
* ap only appears for 1 minute in 3.
* connect with pw given in first solution
* port scan, finds port 9600
* connect with web browser it serves image
 
data can be extracted by:

    steghide extract -sf data/bust.jpg -p passphrase

extracted text is clue for 3rd puzzle:

* link to source of the third puzzle
* password (one of 100 lines of text)

## Notes

image has data encoded into it by steghide:

    steghide embed -cf data/bust.jpg -ef clue.txt -p xojezj
