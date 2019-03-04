# ELECH309-2019
## Labos
Solutions des labos d'introduction du projet intégré

### EmptyProj.X
Squelette de projet pour les labos utilisant l'Explorer16

### Labo1.X
Solution du labo 1 illustrant les GPIOs et l'utilisation d'un timer en polling

### Voltmetre1.X
Version 1 du voltmètre du labo 2, avec le double polling du timer et de l'ADC

### Voltmetre2.X
Version 2 du voltmètre du labo 2, avec déclenchement automatique de l'ADC par le timer et polling uniquement de l'ADC.
Cette solution assure une période d'échantillonnage exacte.

### Synthe1.X
Version la plus simple du synthétiseur qui envoie les échantillons au DAC par polling (pas de clavier).

### Synthe2.X
Ajout de la lecture du clavier par polling  à la version précédente.
Cette version ne fonctionne pas correctement car les échantillons ne sont pas envoyés à la bonne fréquence.
Cela illustre les limites du polling.

### Synthe3.X
Version corrigée du synthétiseur : l'envoi des échatntillons se fait par interruption, le temps d'exécution de la boucle principale
n'a plus d'influence sur la période denvoi.
