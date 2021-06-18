# New World Simulation

Authors: John Nguyen, Joshua Goldberg

View documentation [here](https://goldbergdata.github.io/newWorldSimulation/). 

This program simulates alien species colonizing planets in a star system. Aliens and planets begin in predefined locations specified by a map text file. As the simulation progresses, they will increase in population until they reach the capacity for their planet and begin sending spaceships to colonize new planets. Aliens encountering other species will fight each other for control. The simulation stores its state in three 2-dimensional vectors, for placement of the planets, spaceships, and explosions for flair. The user can choose to start, stop, and reset the simulation in the GUI displaying the simulation, as well as change both the background and initial placement map.

<img src="docs/newWorldSim.gif" alt="Simulation" width="50%">

# Usage

There are a couple use-cases for the simulation:

- Compile and run the simulation.
- Create your own aliens. This is probably the more interesting approach, since you can define the behavior of your own aliens by inheriting `AlienBase` and overriding exploration and population.
- Create your own planets. Another interesting approach for this code base, as the simulation is heavily dependent on the planet attributes.

Note: So far, the aliens and planets implemented are simplistic. A next step would be to develop a dynamic fight between aliens based on attributes, such as HP, attack, etc. Planets are also one-dimensional. Characteristics can be defined for planets such as temperature (can be dictated by proximity from a sun, hazard, and population growth bonus.
