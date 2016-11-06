Description
===========

This project was written as a prototype for software that would run on a handheld device.
Its purpose is to guide the user from one point of interest to another, in a well defined space. (showroom, university campus, exhibitions...)
These places must be linked in some physical way that a person can follow. 
We also require there to be some sort of "signpost" at each intersection indicating where each path leads.
At each point of interest, there must also be some sort of way to update the device with the current position (for example nfc tags).

*"But that sounds a bit pointless! If you need all that why not just use a map?"*
Well for someone who can see that would be true, but this was developed at our university as a tool to help blind people.

This is of course only the base code for the path finding aspect. 
Methods of actually handling user input/output in the intended scenario are not implemented, and for now it's just command line prompts.



Example
-------

- user inputs current position, and desired destination (denoted by numbers).
- shortest path is calculated, and the first instruction is given (ex: take exit 2 to destination_x)
- then the user follows this path, and updates th system upon arrival.
- if the user is where we expected him to be, we continue until he arrives to the final destination.
  if the user made a mistake, the path is recalculated from his current position.


Usage
-----

The information about the area through which the user is guided is represented in text files.
This text file is processed by our program in order to build a graph structure from it.
The person organizing the event can enter the required information into this text file:
- number of places
- adjacent places
- distances between places

There are some example files provided as well as some *poorly* drawn illustrations of the graphs.


From there, we used dijkstra's algorithm to generate the shortest paths from the source node.


**Participants:** Philip Scales (Kyuhae) and Joao Pedro Freitas