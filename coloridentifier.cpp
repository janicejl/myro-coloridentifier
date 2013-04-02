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


int main(int argc, char ** argv) {
//coloridentifier

	map<string, string> list;

	readColorListFour(list);
	readColorListTwo(list);
	readColorListThree(list);
	readColorListOne(list);
	cout<<list.size()<<endl;

	connect();
	cout << "Waiting..." << endl;
	wait(1);

	//robot.setWhiteBalance(0);
	//robot.darkenCamera(0);

	while(true) {
		string hex = analyzePicture();

		cout<<hex<<" = "<<list[hex]<<endl;
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