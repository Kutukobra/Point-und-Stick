# Point und Stick

Simple 2D rope/cloth simulation with Raylib.

## Build and Run

### Windows:
`make`

## Controls

- Click the left mouse button on screen to put a node.
- Connect nodes by clicking and dragging between nodes.
- Cycle between static immovable red nodes and movable white nodes with 'A'.
- Press `SPACE` to play/pause the simulation.
- Drag mouse right click accross edges to 'cut' the edges.

## To-Do
- Implement memory safety with smart pointers.
- Implement more efficient data structure to add/delete edges.

## Warning

This project has memory safety issues, deleted edges and unrendered nodes are not cleared from memory (long live C++).