Zavrsni rad/Final work - Simulacija autonomne voznje automobila/ Simulator for autonomous car driving
Simon Grgurina

Used Unreal Engine 4, version 4.15.3

Project provides an environment for training neural networks using genetic algoritm 
for the purpose of controling a car on a racing track. It also allows easy creation 
of new race tracks.

Usage instructions
Download zip, unpack and build by launching uproject file using UE4. Requires UE4 
and Visual Studio prepared for usage with Unreal Engine 4. After building project use
.uproject file to generate visual studio files. 
Control keybinds can be found and changed in project settings. Genetic algorithm parameters
and neural network structure can be changed by using parameters in MyGameInstance before
launching play. After launching play and possesing pawn start training process by 
using the keybind for training start. Neural net performance and genetic 
algorithm steps can be monitored in ouput log.
Create new tracks by putting a TrackGenerator object in a new level and adding spline points
to create tracks. Before using track, adjust finish line position and spawn point 
position and rotation to be the same as starting position of the car.
