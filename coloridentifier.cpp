#include <Myro.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <CImg/CImg.h>
#include <cstdio>
#include <fstream>
#include <map>


using namespace std;
using namespace cimg_library;

string analyzePicture();
string RGBToHex(int rNum, int gNum, int bNum);
string toUppercase(string word);
void readColorListOne(map<string, string> &list);
void readColorListTwo(map<string, string> &list);
void readColorListThree(map<string, string> &list);
void readColorListFour(map<string, string> &list);
string findClosest(string original, map<string, string> list);
int getR(string hex);
int getG(string hex);
int getB(string hex);
int hexToDec(char c);


int main(int argc, char ** argv) {
//coloridentifier

	map<string, string> list;

	readColorListFour(list);
	readColorListTwo(list);
	readColorListThree(list);
	readColorListOne(list);
	cout<<list.size()<<endl;

	// string asdf = findClosest("#1ABF29", list);

	// cout<<asdf<<" = "<<list[asdf]<<endl;

	connect();
	cout << "Waiting..." << endl;
	wait(1);

	while(true) {
		string hex = analyzePicture();

		string closestHex = findClosest(hex, list);

		cout<<endl;
		cout<<list[closestHex]<<endl;
	}	
	
	cout << "Waiting..." << endl;
	
	cout << "Disconnecting" << endl;
	disconnect();

	return 0;
}

string analyzePicture() {
	cout << "Take a picture..." << endl;
	robot.beep(0.2,990);
	PicturePtr pic = robot.takePicture("jpeg", false);
	pic->show("Robot View");
	//pic->savePicture("pic.jpg");

	double r=0,g=0,b=0;

	for (int i = 0; i < pic->getWidth(); i++) {
		for (int j = 0; j < pic->getHeight(); j++) {
			Pixel p = pic->getPixel(i,j);
			r += (double) p.R;
			g += (double) p.G;
			b += (double) p.B;
		}
	}

	int totalPixels = pic->getWidth() * pic->getHeight();

	Pixel averageColor;
	averageColor.R = r/totalPixels;
	averageColor.G = g/totalPixels;
	averageColor.B = b/totalPixels;

	cout << "Average Pixel: " << (int)averageColor.R 
		<< ',' << (int)averageColor.G << ','<< (int)averageColor.B << endl;

	string hexValue = RGBToHex((int)averageColor.R, (int)averageColor.G, (int)averageColor.B);
	cout<<"Hex: "<<hexValue<<endl;

	return hexValue;
}

string RGBToHex(int rNum, int gNum, int bNum)
{
	string result;

	result += "#";

	char r[255];	
	sprintf(r, "%.2X", rNum);
	result.append(r );

	char g[255];	
	sprintf(g, "%.2X", gNum);
	result.append(g );

	char b[255];	
	sprintf(b, "%.2X", bNum);
	result.append(b );

	return result;
}

string toUppercase(string word) 
{
	string name = "";

	for (int i = 0; i < word.length(); i++) {
		word[i] = toupper(word[i]);
		name = name + word[i];
	}
	return name;
}

void readColorListOne(map<string, string> &list) {
	ifstream in("colorList.txt");

	if (in.good()) {
		string word = "";
		string colorname = "";

		while(!in.eof()) {
			colorname = "";
			in>>word;
			//cout<<word<<endl;
			while(word[0] != '#') {
				colorname = colorname + word + " ";
				in>>word;
			}
			if (colorname != ""){
				cout<<"Inserting: "<<toUppercase(word)<<"  "<<colorname<<endl;
				list[toUppercase(word)] = colorname;
			}
		}

		in.close();
	} else {
		cout<<"Bad file."<<endl;
	}

}

void readColorListTwo(map<string, string> &list) {
	ifstream in("colorList2.txt");

	int r,g,b;
	string name;
	string hex;

	if (in.good()) {
		while (!in.eof()) {
			in>>r;
			in>>g;
			in>>b;
			getline(in, name);

			hex = RGBToHex(r,g,b);
			cout<<"Inserting: "<<hex<<"  "<<name<<endl;
			list[hex] = name;
		}
	} else {
		cout<<"Bad file."<<endl;
	}

	in.close();	
}

void readColorListThree(map<string, string> &list) {
	ifstream in("colorList3.txt");

	int r,g,b;
	string name;
	string hex;
	int rubbishNum;
	string rubbishWord;

	if (in.good()) {
		while (!in.eof()) {
			in>>rubbishWord;
			in>>r;
			in>>g;
			in>>b;
			in>>rubbishNum;
			getline(in, name);

			hex = RGBToHex(r,g,b);

			cout<<"Inserting: "<<hex<<"  "<<name<<endl;
			list[hex] = name;
		}
	} else {
		cout<<"Bad file."<<endl;
	}

	in.close();	
}

void readColorListFour(map<string, string> &list) {
	ifstream in("colorList4.txt");

	int r,g,b;
	string name;
	string hex;

	if (in.good()) {
		while (!in.eof()) {
			in>>r;
			in>>g;
			in>>b;
			getline(in, name);

			hex = RGBToHex(r,g,b);
			cout<<"Inserting: "<<hex<<"  "<<name<<endl;
			list[hex] = name;
		}
	} else {
		cout<<"Bad file."<<endl;
	}

	in.close();	
}


string findClosest(string original, map<string, string> list) {
	const int R = getR(original);
	const int G = getG(original);
	const int B = getB(original);

	// cout<<R<<" "<<G<<" "<<B<<endl;

	string key, value;

	string nearest = "";

	double difference = 500.0;

	typedef map<string, string>::iterator it_type;
	for(it_type iterator = list.begin(); iterator != list.end(); iterator++) {
		int keyR = 0, keyG = 0, keyB = 0;

	    key = iterator->first;
	    value = iterator->second;

	    keyR = getR(key);
	    keyG = getG(key);
	    keyB = getB(key);

	    if ((R == keyR) && (G == keyG) && (B == keyB)) {
	    	return original;
	    }

	    if (((keyR == 0) && (keyG == 0) && (keyB == 0)) || ((keyR == 255) && (keyG == 255) && (keyB == 255))) {
	    	continue;
	    }

	    double distance = sqrt((R - keyR)*(R - keyR) + (G - keyG)*(G - keyG) + (B - keyB)*(B - keyB));

	    // cout<<distance<<endl;

	    if (distance < difference) {
	    	difference = distance;
	    	nearest = key;
	    	// cout<<"New nearest: "<<nearest<<endl;
	    }
   
	}
	// cout<<R<<" "<<G<<" "<<B<<endl;
	// cout<<original<<" "<<nearest<<endl;
	// cout<<difference<<endl;
	return nearest;
}

int getR(string hex) {
	int r1 = hexToDec((char)hex[1])*16;
	int r2 = hexToDec((char)hex[2]);

	return r1+r2;
}
int getG(string hex) {
	int g1 = hexToDec((char)hex[3])*16;
	int g2 = hexToDec((char)hex[4]);

	return g1+g2;
}
int getB(string hex) {
	int b1 = hexToDec((char)hex[5])*16;
	int b2 = hexToDec((char)hex[6]);

	return b1+b2;
}

int hexToDec(char c) {
	if (c == '0') {
		return 0;
	} else if (c == '1') {
		return 1;
	} else if (c == '2') {
		return 2;
	} else if (c == '3') {
		return 3;
	} else if (c == '4') {
		return 4;
	} else if (c == '5') {
		return 5;
	} else if (c == '6') {
		return 6;
	} else if (c == '7') {
		return 7;
	} else if (c == '8') {
		return 8;
	} else if (c == '9') {
		return 9;
	} else if (c == 'A' || c == 'a') {
		return 10;
	} else if (c == 'B' || c == 'b') {
		return 11;
	} else if (c == 'C' || c == 'c') {
		return 12;
	} else if (c == 'D' || c == 'd') {
		return 13;
	} else if (c == 'E' || c == 'e') {
		return 14;
	} else if (c == 'F' || c == 'f') {
		return 15;
	} 
}