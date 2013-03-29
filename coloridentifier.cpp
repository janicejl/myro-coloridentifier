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

class NameHex {
	private:
		string name;
		string hex;
	public:
		string getName() {
			return name;
		}
		string getHex() {
			return hex;
		}
		void setName(string n) {
			name = n;
		}
		void setHex(string h) {
			hex = h;
		}
};

int main(int argc, char ** argv)
{
//coloridentifier

	ifstream in;
	//in.open(argv[1]);
	in.open("colorList.txt");
	//vector<NameHex> list;
	map<string, string> list;
	if (in.good()) {
		string word = "";
		string colorname = "";

		while(!in.eof()) {
			colorname = "";
			//NameHex temp;
			in>>word;
			//cout<<word<<endl;
			while(word[0] != '#') {
				colorname = colorname + word + " ";
				in>>word;
			}
			//temp.setName(colorname);
			//temp.setHex(word);

			//list.push_back(temp);
			//list.insert(pair<string,string>(word, colorname));
			//list.insert(word, colorname);
			cout<<"Inserting: "<<toUppercase(word)<<"  "<<colorname<<endl;
			list[toUppercase(word)] = colorname;
		}

		// for (int i = 0; i < (int)list.size(); i++) {
		// 	cout<< list[i].name<<"  "<<list[i].hex<<endl;
		// }

		in.close();
	} else {
		cout<<"Bad file."<<endl;
	}

	connect();
	cout << "Waiting..." << endl;
	wait(1);

	//robot.setWhiteBalance(0);
	//robot.darkenCamera(0);

	while(true) {
		string hex = analyzePicture();
		//string hex = RGBToHex(255, 255, 255);
		//cout<<hex<<endl;

		// for (int i = 0; i < (int)list.size(); i++) {
		// 	//if (list[i].getHex() == hex) {
		// 	if (strcasecmp(hex.c_str(), list[i].getHex().c_str()) == 1) {
		// 		cout<<list[i].getName()<<endl;
		// 		break;
		// 	}
		// }

		//list.at(hex);
		cout<<list[hex]<<endl;
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