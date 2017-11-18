#include "Complex.h"
#define MAX_RAND 100
Complex::Complex(){
	this->real=0;
	this->img=0;
}
Complex::Complex(double real){
	this->real = real;
	this->img = 0;
}
Complex::Complex(double real,double img){
	this->real = real;
	this->img = img;
}
Complex::Complex(string complex){
	for (int i = 0; i < complex.length(); ++i)
	{
		if(complex[i]=='i')
		{
			complex.erase(i,1);
			complex += string("i");
			break;
		}
	}

	int seperator;
	int sign;
	if(complex.find_first_of("+",1) != -1){
		seperator = complex.find_first_of("+",1);
		sign = 1;
	}
	else if(complex.find_first_of("-",1) != -1){
		seperator = complex.find_first_of("-",1);
		sign = -1;
	}
	else{
		seperator = -1;
	}
	if(seperator == -1){
		if(complex[complex.length()-1] == 'i'){
			this->img = atof(complex.substr(0,seperator).c_str());
			this->real = 0;
		}else{
			this->real = atof(complex.substr(0,seperator).c_str());
			this->img=0;
		}
	}else{
		this->real = atof(complex.substr(0,seperator).c_str());
		if(complex.substr(seperator,complex.length()-seperator-1).length() == 1)
			this->img = 1*((complex[seperator]=='-')?-1:1);
		else
			this->img = atof(complex.substr(seperator,complex.length()-seperator-1).c_str());
	}
}

void Complex::setReal(double real){
	this->real = real;
}
void Complex::setImaginary(double img){
	this->img = img;
}
double Complex::getReal(){
	return this->real;
}
double Complex::getImaginary(){
	return this->img;
}

double Complex::magnitude(){
	return sqrt(pow(this->real,2)+pow(this->img,2));
}
double Complex::phase(){
	return toDegree(atan(this->img/this->real));
}

Complex Complex::operator+(Complex a){
	Complex result;
	result.real = this->real + a.real;
	result.img = this->img + a.img;
	return result;
}
Complex Complex::operator-(Complex a){
	Complex result;
	result.real = this->real - a.real;
	result.img = this->img - a.img;
	return result;
}
Complex Complex::operator*(Complex a){
	Complex result;
	result.real = this->real * a.real - this->img * a.img;
	result.img = this->real * a.img + this->img * a.real;
	return result;
}
Complex Complex::operator/(Complex a){
	Complex result;
	double mag = this->magnitude() / a.magnitude();
	double phase = this->phase() - a.phase(); 
	result.real = mag*cos(toRadian(phase));
	result.img = mag*sin(toRadian(phase));
	return result;
}

Complex Complex::operator+(double a){
	Complex result;
	result.real = this->real + a;
	result.img = this->img;
	return result;
}
Complex Complex::operator-(double a){
	Complex result;
	result.real = this->real - a;
	result.img = this->img;
	return result;
}
Complex Complex::operator*(double a){
	Complex result;
	result.real = this->real * a;
	result.img = this->img * a;
	return result;
}
Complex Complex::operator/(double a){
	Complex result;
	result.real = this->real / a;
	result.img = this->img / a;
	return result;
}
Complex Complex::operator^(double a){
	Complex result;
	double mag = pow(this->magnitude(),a);
	double phase = this->phase() * a; 
	result.real = mag*cos(toRadian(phase));
	result.img = mag*sin(toRadian(phase));
	return result;
}


Complex Complex::rand(){
	Complex result;
	result.real = ::rand()%MAX_RAND;
	result.img = ::rand()%MAX_RAND;
	return result;
}

Complex sin(Complex a){
	Complex result;
	result.real = sin(a.real)*cosh(a.img);
	result.img = cos(a.real)*sinh(a.img);
	return result;
}

Complex cos(Complex a){
	Complex result;
	result.real = cos(a.real)*cosh(a.img);
	result.img = -sin(a.real)*sinh(a.img);
	return result;
}

ostream& operator<<(ostream& out,Complex a){
	if(a.real != 0) out << a.real;
	if(a.img > 0 && a.real != 0) 
		if(a.img != 1 )
			out << "+" << a.img << "i";
		else
			out << "+i";
	if(a.img > 0 && a.real == 0)
		if(a.img != 1)
			out << a.img << "i";
		else
			out << "i";
	else if(a.img < 0 && a.img!= -1) out << a.img << "i";
	else if(a.img == -1) out<< "-i";


	return out;

}


char Complex::operator<(double a)
{
	if(real> a)
		return 1;
	else
		return 0;
}
char Complex::operator>(double a)
{
	if(real<a)
		return 1;
	else
		return 0;
}

Complex Pow(Complex a, double p)
{
	return a^p;
}


Complex Complex::operator+=(Complex a)
{
	return (*this) + a;
}

Complex Complex::operator-=(Complex a)
{
	return (*this) - a;
}


Complex Complex::operator*=(Complex a)
{
	return (*this) * a;
}


Complex Complex::Complex::operator/=(Complex a)
{
	return (*this) / a;
}


Complex Complex::operator+=(double a)
{
	return (*this) + a;
}

Complex Complex::operator-=(double a)
{
	return (*this) - a;
}


Complex Complex::operator*=(double a)
{
	return (*this) * a;
}


Complex Complex::operator/=(double a)
{
	return (*this) / a;
}





Complex operator+(double a,Complex b)
{
	return b + a;
}


Complex operator-(double a,Complex b)
{
	return b - a;
}




Complex operator*(double a,Complex b)
{
	return b * a;
}




Complex operator/(double a,Complex b)
{
	return b / a;
}



int operator<(double a,Complex b)
{
	return b < a;
}




int operator>(double a,Complex b)
{
	return b > a;
}


char Complex::operator>(Complex a)
{
	return this->magnitude() > a.magnitude();
}
	

char Complex::operator<(Complex a)
{
	return this->magnitude() < a.magnitude();
}
	

Complex Complex::operator-()
{
	Complex result;
	result.img = -1*this->img;
	result.real = -1*this->real;

	return result;
}

Complex Sqrt(Complex a)
{
	return Pow(a,0.5);
}

char Complex::operator==(double a)
{
	if(a == this->real && this->img==0)
		return 1;
	else return 0;
}

char Complex::operator==(Complex a)
{
	if(a.real == this->real && this->img==a.img)
		return 1;
	else return 0;
}

char operator==(double a,Complex b)
{
	return (b==a);
}




char Complex::operator!=(double a)
{
	if(a == this->real && this->img==0)
		return 0;
	else return 1;
}

char Complex::operator!=(Complex a)
{
	if(a.real == this->real && this->img==a.img)
		return 0;
	else return 1;
}

char operator!=(double a,Complex b)
{
	return (b!=a);
}

Complex Round(Complex a)
{

	a.real = round(a.real);
	a.img = round(a.img);
	return a;

}