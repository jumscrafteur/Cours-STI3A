1. .
   1. (pas de réponse)
   2. Sortie : 
      ``` 
      Drawing the 4 th zone of a shape
      Drawing a shape
      Drawing a  rectangle
      ```
   3. c'est un polymorphisme implicite d'héritage
   4. Sortie :
        ```
        Computing the perimeter of a quadrilateral
        Computing the perimeter of a rectangle
        ```
   5. Dans notre code , dans le 1er cas le périmètre a été calculé via la méthode "getPerimeter" de la classe Quadrilateral car la variable a été créé comme un Quadrilateral qui est moins spécifique que Rectangle.
    Dans le deuxième cas on utilise "getPerimeter" de la class Rectangle car la variable a été créé comme un rectangle directement
   6. Ce code est acceptable car Rectangle , Quadrilateral et Ellipse sont tout les trois des enfants de GeometricalShape. C'est un transtypage implicite
   7. Erreur : 
        ```
        Type mismatch: cannot convert from Quadrilateral to Rectangle
        ```
   Cette erreur a lieux car Quadrilateral est une classe parent de Rectangle , Rectangle peut donc posséder des méthodes et des arguments supplémentaires
   8.Erreur :
        ```
        The method getPerimeter() is undefined for the type GeometricalShape
        ```
        Cette erreur a lieux car même si `listFig[0]` est de type Rectangle , `listFig`est une liste de GeometricalShape qui ne possède pas de méthode getPerimeter()
