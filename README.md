# Construction-de-courbes-de-niveau-en-2D-et-3D
## Problématique de recherche :
Dans le domaine d’infographie, il existe des algorithmes permet de construire les courbes de niveau, appellés aussi courbes isovaleurs d’un champ scalaire (par example des images binaires ou en niveaux gris). Dans ce contexte, nous nous intéressons à l’algorithme marching squares [2] en deux dimensions et marching cubes [1] en trois dimensions pour créer des objets polygonaux à partir de champ scalaire par approximation d’une isosurface. Un example est donné dans la figure ci-après.

## Sujet :
Les méthodes de marching squares et marching cubes utilisent souvent de table de correspondance (Look-Up-Table – LUT) pour la construction des isosurfaces, et aussi l’interpolation de champs scalaires pour calculer la position exacte des isosurfaces. La réalisation du travail consistera à implémenter les deux méthodes de marching squares et marching cubes dans la littérature en utilisant LUT et des différents méthodes d’interpolation comme l’interpolation linéaire, bilinéaire, cubique, . . . La parallélisation de la méthode sera également considérée.

## References:
[1] Lorensen, W. E.; Cline, Harvey E. (1987). "Marching cubes: A high resolution 3d surface construction algorithm". ACM Computer Graphics. 21 (4): 163–169.

[2] Maple, C. (2003). Geometric design and space planning using the marching squares and marching cube algorithms. Proc. 2003 Intl. Conf. Geometric Modeling and Graphics. pp. 90-95.
