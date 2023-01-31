# music_sequencer
This is a music sequencer that stores music notes in a BST. The functions include search, insert, delete, reverse and harmonize.

- A2_test_driver.c is an automative test driver, to help me test and debug.
- A2_interactive_driver.c is an interactive driver to help me manually test my BST 
and which I can use to manipulate musical notes and play-back the music stored by my sequencer.
- NoteSynth.c implements a simple but fully-functional software synthesizer. 
It receives a list of notes from the sequencer, and produces the sounds corresponding to each of them, 
at the right point in time, to play the notes in your tree. This file is given by the professor.
- note_frequencies.txt has a list of notes, with the name and frequency of each note. 
The file is required by NoteSynth.c to make music.
- All other .txt files contain song information I can use to test and manipulate my BST.

To compile the BST code with the test driver, use:
  gcc -Wall A2_test_driver.c -lm
To compile the BST code with the interactive driver use:
  gcc -Wall A2_interactive_driver.c -lm
