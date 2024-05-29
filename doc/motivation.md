# Motivation and Objectives

## Motivation

I decided to make **ARCMAN** as my C++ Object-Oriented Programming project because it combines my passion for arcade games (especially Pac-Man) with a practical application of software engineering principles. It offers a hands-on opportunity to explore essential objetc-oriented programming concepts such as inheritance and polymorphism, while also enhancing my proficiency in C++. 

Also, I wanted to add things that are specific to an average student studying at "HE-Arc", like the player using the logo colors and the walls of the maze being the same color as the school wals, so the game is fun for my class mates.

## Objectives

The objectives for the game are:

### General Project goals

* Try to use as much of the components already provided by **C++**, like objects from the Standard Library or concepts specific to C++
* Implement the game using a Graphics Library (SFML)
* Make the game cross-platform (Windows, Linux, MacOs)
* Use *Design Patterns* where it is useful


### Graphics

* Try to use the classes provided by the Graphics Engine as base classes for my own
* Draw sprites on my own
* Prioritize using maths for position and vector calculations

### Classes and Objects

* Implement a class **Entity**, preferably extending the **Sprite** class provided by **SFML**, where I can manage all the general things related to the entities in the game 
* Implement the **Player** as accurate as possible from the base game
* Implement **Ghosts** that chase the player (choosing direction randomly or using a search algorithm)
* Implement a *direction queue* for player's mouvement
* Implement the physics for the maze, using entity collision or an unoriented graph
* Implement a **Logger**
