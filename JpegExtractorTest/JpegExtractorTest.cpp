#include "pch.h"
#include <iostream>
#include <string>
#include "../JpegExtractor/JpegExtractor.h"

using namespace std;

int main()
{
	string path1 = "C:\\Users\\rtviw\\Desktop\\картинки для курсача\\img1.jpg";
	string path2 = "C:\\Users\\rtviw\\Desktop\\картинки для курсача\\img2.jpg";
	string path3 = "C:\\Users\\rtviw\\Desktop\\картинки для курсача\\img3.jpg";
	string path4 = "C:\\Users\\rtviw\\Desktop\\картинки для курсача\\img4.jpg";
	string path5 = "C:\\Users\\rtviw\\Desktop\\картинки для курсача\\img5.jpg";
	string* paths = new string[5]{ path1, path2, path3, path4, path5 };

	for (int i(0); i < 5; i++)
	{
		JpegExtractor je(paths[i]);
		je.analyzeFile();

		std::cout << je.getCommentary();
	}

	return 0;
}
