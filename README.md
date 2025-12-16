# Student Management System



## Data File Format

(`data.txt`) follows cette structure:

```
ETUDIANTS
numero;prenom;nom;age
226345678;Alexander;Müller;19
...

MATIERES
nom;coef
Mathematiques;2.25
Physique;1.75
...

NOTES
id;nom;note
226767522;Geographie;18.3
226112457;Mathematiques;2.2
...
```


### Build Commands

```bash
make        # Compile le projet (crée bin/student_manager)
make run    # Compile et lance le programme directement
make clean  # Supprime les fichiers objets (.o)
make fclean # Supprime tout (objets + exécutable + sauvegarde)
make re     # Recompile tout depuis zéro
```