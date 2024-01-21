#ifndef SHAPE_H_
#define SHAPE_H_

#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<list>
#include<fstream>
#include <iomanip>    

/*partners: ufacio2, ehaynes2
 * The lab 12 powerpoint, mp12 document, and c++ lectures from ece220 assisted with the coding.
 * introduction: This program creates a base class named Shape and four shape derived classes: Rectangle, Circle, Sphere, and Rectangular Prism. 
 * In the Shape base class, a constructor with the shape's name is made, along with a set function for its name and two virtual functions for getArea() and getVolume();
 * In the rectangle class, it is made with a template. Within this template, there is a constructor that sets the width and length of the shape and the name to Rectangle. This class also
 * builds upon the base getArea and getVolume functions to calcuate its area/volume, has getter functions for its private variables, and an overloaded add operator and an overloaded subtract operator.
 * All of the overloaded add operators add the respective private variables (width with width or height with height) together for two objects of that class and returns a new object with those new parameters.
 * The overloaded subtract operator subtracts the respective variables from one another and returns an object with those new parameters. If any such calculations results in a negative number, it'll set that
 * parameter as a 0. 
 * In the other three derived shape classes (circle, sphere and rectangular prism), they each have their own constructors that are instantiated with their respective values (sphere and circle
 * have radius while the rectangular prism has a width, length and height) and names. Theese classes also have their own getArea() and getVolume() functions, getter functions, 
 * overloaded add operator and overloaded subtract operator. 
 * The CreateShapes function reads the given file and makes a list filled with the shapes on said file. All shapes are correctly initialized with the given values.
 * The MaxArea function goes through the list and returns the greatest area of a shape located in said list.
 * The MaxVolume function goes through a shapes list and returns the greatest volume of a shape located in said list. 
*/

using namespace std;

//Base class
//Please implement Shape's member functions
//constructor, getName()
class Shape{
public:
	//Base class' constructor should be called in derived classes'
	//constructor to initizlize Shape's private variable 
  	Shape(string name) {
	name_ = name;							//set the name given in the parameter to the private variable name_
	}
	
  	string getName() {
	return name_;							//get function: return the value of the private variable name_
	}
	
  	virtual double getArea() const = 0;
  	virtual double getVolume() const = 0;
	
private:
  string name_;


};

//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-

template <class T>
class Rectangle : public Shape{
public:
  	Rectangle<T>(T width = 0, T length = 0):Shape("Rectangle") {
	width_ = width;							//Shape name is already set. Now set the width and length with the given
	length_ = length;						//parameters
	}
	
  	double getArea() const {
		return (double)(width_* length_);			//multiply the width and the area. Typecast to double to ensure right return value
	}
	
  	double getVolume() const {	
		return (double)0;					//a rectangle has no volume. Return 0. Typecasted to ensure correct return value
	}
	
	Rectangle<T> operator + (const Rectangle<T>& rec) {
		return Rectangle((T)rec.width_ + width_, (T)rec.length_ + length_);	//create a new object Rectangle with the added widths and lengths
											// of the current rectangle and an additional rectangle.
	}
	
	Rectangle<T> operator - (const Rectangle<T>& rec) {
		return Rectangle(max((T)0, width_ -(T)rec.width_), max((T)0, length_ - (T)rec.length_));	//create a new rectangle object with
					//the width & length of the current rectangle minus the values of another rectangle. If that new width/length is 
					//a negative number, return 0 instead. 
	} 
	
	T getWidth() const { 
		return width_;		//get function: returns current rectangle's width
	}
	
	T getLength() const { 
		return length_;		//get function: returns current rectangle's length
	}
private:
	T width_;
	T length_;

};

//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Circle : public Shape{
public:
  	Circle(double radius):Shape("Circle") {			
		radius_ = radius;	//set the radius of the circle
	}
	
  	double getArea() const{		
		return (double) (M_PI * radius_ * radius_);	//return the area of the circle
	}
	
 	double getVolume() const{
		return (double)0;				//a circle has no volume so we return 0
	}
	
  	Circle operator + (const Circle& cir){
		return Circle (radius_ + cir.radius_);		//return a new object with a radius that is equal to the current cicle's radius + another
								//circle's radius
	}
	
	Circle operator - (const Circle& cir){
		return Circle(max(0.0, radius_ - cir.radius_));	//return a new circle object that has the radius of the current circle minus the radius
								//of another circle. If that results in a negative number, return 0 instead.
	} 

	double getRadius() const { 
		return radius_;					//get function for the radius of the circle
	}
	
private:
	double radius_;

};



//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Sphere : public Shape{
public:
  	Sphere(double radius):Shape("Sphere") {
		radius_ = radius;				//sets the radius for the new sphere object
	}

  	double getVolume() const {
		return 4.0/3.0*M_PI*pow(radius_,3);		//calculate the volume of the sphere
	}	
	
  	double getArea() const {			
		return 4.0 * M_PI * pow(radius_,2);		//calculates the area of the sphere
	}

	Sphere operator + (const Sphere& sph) {			//creates a new sphere object that has a radius of the current sphere plus another sphere
		return Sphere(radius_ + sph.radius_);
	}

	Sphere operator - (const Sphere& sph) {
		return Sphere(max(0.0, radius_ - sph.radius_));	//creates a new sphere that has a radius that is equal to the current sphere minus another
								//sphere. If that value is a negative number, the radius will equal 0
	} 
	
	double getRadius() const {
		return radius_;					//get function for the sphere's radius
	}

private:
	double radius_;

};

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
class RectPrism : public Shape{
public:
  	RectPrism(double width, double length, double height):Shape("RectPrism") {
		length_ = length;			//set the length, width and the height of the object
		width_ = width;
		height_ = height;		
	}
	
  	double getVolume() const {
		return length_* height_* width_;	//calculates the volume of the rectangular prism
	}
  	
	double getArea() const {
		return (length_* width_ + length_* height_ + width_* height_)*2;	//calculates the area of the rectangular prism
	}
	
	RectPrism operator + (const RectPrism& rectp){
		return RectPrism(width_ + rectp.width_, length_ + rectp.length_, height_ + rectp.height_);	//creates a new rectangular prism object
														//with the length, width, and height equal
														//to the sum of current rectangular prism's parameters
														//and the respective parameters on the other rectangular prism
	}
	
	RectPrism operator - (const RectPrism& rectp){											
		return RectPrism(max(0.0, width_ - rectp.width_), max(0.0, length_ - rectp.length_), max(0.0,height_ - rectp.height_));	//create a new rectangular prism with a new length, width
																	//and height that is equal to the current prism's value minus
																	//another prism's respective values
	}	
	
	double getWidth() const { 			//There are three getter functions for the width, length and height
		return width_;
	}
	
	double getLength() const { 
		return length_;
	}
	
	double getHeight() const { 
		return height_;
	}
private:
  	double length_;
  	double width_;
  	double height_;

};

// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
static list<Shape*> CreateShapes(char* file_name) {
	//@@Insert your code here
	int num, i;						//declare variables that will be used later on
	ifstream stream(file_name, std::ifstream::in);		//create the stream
	stream >> num;						//read in the first number, which is the number of objects needed to be in the list, from stream
	list<Shape*> myList;					//creates the list
	string currName;					//creates a variable for the name of the shape
	double length, width, height;				//creates other useful variables for storing the right values
	for (i = 0; i < num; i++)
	{
		stream >> currName;				//read in the name of a shape
		if (currName == "Rectangle")			//if that name is a rectangle, read in the next two values for width and height
		{ 	stream >> width >> height;
			Rectangle<double>  *rectan = new Rectangle<double>(width, height);	//create new rectangle object and the pointer associated with it
			myList.push_back(rectan);						//add that ptr to the list
		}
		else if (currName == "Circle")			//shape is a circle
		{
			stream >> length;			//to save on variables, reuse length variable as the radius and read in the radius from the stream
			Circle* circ = new Circle(length);	//instantiate a new circle object and get the pointer to it
			myList.push_back(circ);			//add the ptr to the list
		}
		else if (currName == "Sphere")			//next shape is a sphere
		{	
			stream >> length;			//use length as radius temporarily and read in the radius from the stream
			Sphere* sphe = new Sphere(length);	//create a ptr to an object sphere
			myList.push_back(sphe);			//add the ptr to the list
		}
		else
		{
			stream>>width>>length>>height;		//if it wasn't any of the shapes above, it must be a rectangular prism. Get the width, length and height from stream
			RectPrism* rectpri = new RectPrism(width, length, height);	//create a ptr to a new rectangular prism
			myList.push_back(rectpri);		//add new ptr to the list
		}
	}

	stream.close();		//close the stream
	return myList;
}

// call getArea() of each object 
// return the max area
static double MaxArea(list<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
	list<Shape*>::iterator myList;			//instantiate the iterator and name it myList
	for (myList = shapes.begin(); myList !=shapes.end(); myList++)	//go through the whole list with an iterator
	{
		if ((*myList)->getArea() >= max_area)		//check if the current object in that list has a area greater than the current max area
		{
			max_area = (*myList)->getArea();	//if so, set new max area to max_area
		}
	}
	return max_area;
}

// call getVolume() of each object 
// return the max volume
static double MaxVolume(list<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
	list<Shape*>::iterator myList;			//instantiate a variable to keep track of the index while looping through the iterator
	for (myList = shapes.begin(); myList != shapes.end(); myList++)	//iterate through the list
	{
		if ((*myList)->getVolume() >= max_volume)		//check to see if the volume of the object at that point in the list is greater than the current max_volume
		{
			max_volume = (*myList)->getVolume();		//if so, set new max volume
		}
	}
	return max_volume;
}
#endif

