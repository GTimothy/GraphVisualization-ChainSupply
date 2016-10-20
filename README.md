# GraphVisualization-ChainSupply
An introduction to the C programming language - 1st year project at TELECOM Nancy


English

This program was designed to allow users to visualize a network of freight transportation.
Users will have to choose between having the network be generated at random or manually entering its dependencies on the command line.
A .dot file will be created and compiled using GraphViz, an open-source C library for the visualization of graphs.
Users must then choose two warehouses between which he wishes to find the shortest path, which will be found using the Dijktra algorithm implemented in the program.
Users must finally define the amount of products they wish to transport from one warehouse to another.
The final solution will be shown as an JPEG image.

Users will be guided all along.

IMPORTANT: for a 6 node graph, nodes are numbered from 1 to 6 and not from 0 to 5

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

Français

Ce programme a été conçu pour permettre à l'utilisateur de visualiser un réseau de transport de marchandises.
Dans un premier temps l'utilisateur devra choisir entre deux modes de fonctionnement : une génération aléatoire ou une saisie manuelle du réseau.
Un fichier .dot est créé et compilé à l'aide de GRAPHVIZ en format .jpg.
L'utilisateur devra par la suite indiquer le numéro des deux dépôts entre lesquels il souhaite trouver un chemin. L'algorithme de Dijkstra utilisé permettra de trouver le plus court chemin entre ces deux dépôts pour présenter la solution sous format .jpg.
L'étape finale consiste à définir la quantité de marchandises que l'utilisateur souhaite transporter entre ces deux points. L'état final du réseau sera affiché sous format .jpg.

L'utilisateur sera guidé tout au long de ses démarches. 
ATTENTION : pour un graphe à 6 sommets par exemple, les sommets sont numérotés de 1 à 6, et non pas de 0 à 5.
