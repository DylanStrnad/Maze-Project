#include <iostream>
#include <cmath>

using std::cout; using std::cin; using std::endl;


int main() {

	int cookie = 142;

	char gender;

	int weight, feet, inch, age;

	cout << "what is your gender:[m/f]";
	cin >> gender; 

	cout << "What is your weight in pounds:";
	cin >> weight;

	cout << "What is your height feet:";
	cin >> feet;

	cout << "inches:";
	cin >> inch;

	cout << "What is your age:";
	cin >> age;

	if (gender == 'm') {

		int bmrMen(int weight,int height,int age);
		cout << "BMR:" << (66 + (6.3 * weight) + (12.9 * ((12 * feet) + inch)) - (6.8 * age)) << endl;
		cout << "number of cookies that can be consumed per day:" << floor((66 + (6.3 * weight) + (12.9 * ((12 * feet) + inch)) - (6.8 * age)) / cookie);

	}else if (gender == 'f') {
		int bmrWomen(int weight, int height, int age);
		cout << "BMR:" << 655 + (4.3 * weight) + (4.7 * ((12 * feet) + inch)) - (4.7 * age) << endl;
		cout << "number of cookies that can be consumed per day:" << floor((655 + (4.3 * weight) + (4.7 * ((12 * feet) + inch)) - (4.7 * age)) / cookie);
	}
	else
		cout << "invalid response";
	
}


	int bmrMen(int weight, int height, int age) {

		int result = 66 + (6.3 * weight) + (12.9 * height) - (6.8 * age);
		return result;
		
	}

	int bmrWomen(int weight, int height, int age) {

		int result = 655 + (4.3 * weight) + (4.7 * height) - (4.7 * age);
		return result;
		
	}