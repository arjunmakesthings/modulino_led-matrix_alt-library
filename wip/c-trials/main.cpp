#include <iostream>
#include <stdio.h>
#include "font.hpp"

using namespace std; 

int main(){
	//outputs vectors:
	auto pts = serif_font::pixels('a');

	for (int i = 0; i<pts.size(); ++i){
		//go over all the returned points, and: 

		cout << "point " << i << ": " << "x: " << pts[i].x << ", " << "y: " << pts[i].y  << "\n"; 
		/*
		   ^ this returns all points like so: 
		   	point {num}: x: val, y:val
		*/
	}	

	return 0; 
}
