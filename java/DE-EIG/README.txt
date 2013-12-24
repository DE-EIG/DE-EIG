HOW TO INTEGRATE DE-EIG INTO YOUR DE VARIANTS:

	Simply call Xover.run to complete the crossover. Please note that the 
	input parameter CR must be a NPx1 vector which contains the crossover 
	rate for each pair of target vector and donor vector.

TO THINK ABOUT THE BIG PICTURE OF DE-EIG:

	Please run this program by DEEIG.main.

LIST OF FUNCTIONS:

Entry point of the program:		DEEIG.java
Test function:					Ellipsoidalrot.java
DE/rand/1/bin:					Derand1bin.java
DE/rand/1/eig:					Derand1eig.java
Binomial crossover:				Bincrossover.java
EIG crossover:					Eigcrossover.java
Mixed bin and EIG crossover:	Mixcrossover.java
Overall crossover:				Xover.java
