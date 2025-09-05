# 3D-Protein
A crack at OpenGL and a final push with C++, programming a graphics engine that takes a .pdb file (protein data bank) as input, procedurally interpreting atoms (and bonds through bond threshold mathematics), and then rendering them as points and lines with atom specific colours.

Packaged also is input mechanics, with WASD controlling three-dimensional positioning, and the arrow keys controling X/Y camera rotation (no gimba-lock in my house). Additionally, pressing B and M toggles visibility for the calculated bonds and the atoms respectively, with ^ and v on the numpad controlling the thickness of what's rendered. It is recommended for smaller molecules to play around with the bond toggle and up the thickness, but for larger stuff, disable bonds and have smaller atoms for visibility and performance. Tab triggers the file open dialogue in the command prompt.

Performance and Pespective mode can be switched with 'P', rendering realistic atomic size and depth at the cost of performance.
