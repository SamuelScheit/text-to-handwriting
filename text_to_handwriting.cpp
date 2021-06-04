/*
 *****************************************************************************
 *                                                                           *
 *                          Platform Independent                             *
 *                     Bitmap Image Reader Writer Library                    *
 *                                                                           *
 * Author: Arash Partow - 2002                                               *
 * URL: http://partow.net/programming/bitmap/index.html                      *
 *                                                                           *
 * Note: This library only supports 24-bits per pixel bitmap format files.   *
 *                                                                           *
 * Copyright notice:                                                         *
 * Free use of the Platform Independent Bitmap Image Reader Writer Library   *
 * is permitted under the guidelines and in accordance with the most current *
 * version of the MIT License.                                               *
 * http://www.opensource.org/licenses/MIT                                    *
 *                                                                           *
 *****************************************************************************
*/
#define _SCL_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE 

#pragma warning(disable:4996)
#include "stdafx.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h> 
#include "bitmap_image.hpp"

int main(int argc)
{
	int DinA4 = 3508;
	int pages = 1;
	srand(time(NULL));

	char text[] = "Es macht keinen Sinn zu erwaehnen, dass dieser Text eigentlich gar keinen Sinn hat. Warum ist es mir ueberhaupt in den Sinn gekommen, einen Text zu schreiben, der absolut keinen Sinn hat? Womoeglich haette es einen Sinn, wenn ich mir einen ueberlegt haette. Wobei wenn ich ehrlich bin, macht es genauso wenig Sinn, einen Text mit Sinn zu nennen. Wie sinnlos waere das, dem Leser anzukuendigen, dass der Text einen Sinn hat. Nun faellt mir auf, dass es auch genauso wenig Sinn machen wuerde, diesen Text zu lesen, ich meine, wie sinnlos waere das? Es waere eine sinnlose Zeitverschwendung. Mit ebenso wenig Sinn, wie einen Text zu schreiben, den eigentlich man nicht zu lesen braucht, weil er diesen Sinnesanspruch einfach nicht gerecht wird. Und nun komme ich zu dem Schluss, dass ich mich noch sinnloserweise darueber aufregen koennte, wie sinnlos es ist, in allem immer einen Sinn sehen zu wollen. Es muss ja nun nicht wirklich immer alles einen Sinn ergeben. Waere ja sinnlos, wenn alles einen Sinn haette.";

	if (text) {
		bitmap_image image(2480, DinA4);
		image.clear(0xff);
		int length = 0;
		for (length = 0; text[length] != '\0'; length++);
		unsigned int width = 256;
		unsigned int height = 256;
		for (int i = 0; i < length; i++) {
			char folder[20] = "img/";

			switch (text[i]) {
				case 92: // "\"
					height += 128;
					width = 256;
					break;
				case 32: //space
					width += 60;
					continue;
					break;
				case -33: //ß
					strcpy(&folder[4], "eszett/");
					itoa(rand() % 5 + 1, &folder[11], 10);
					strcpy(&folder[12], ".bmp");
					break;
				case 34: //"
					strcpy(&folder[4], "''/1.bmp");
					break;
				case 58: //:
					strcpy(&folder[4], "dpunkt/1.bmp");
					break;
				case -28: //ae
					strcpy(&folder[4], "ae-low/");
					itoa(rand() % 5 + 1, &folder[10], 10);
					strcpy(&folder[11], ".bmp");
					break;
				case -60: //ae
					strcpy(&folder[4], "ae-up/");
					itoa(rand() % 5 + 1, &folder[10], 10);
					strcpy(&folder[11], ".bmp");
					break;
				case -10: //oe
					strcpy(&folder[4], "oe-low/");
					itoa(rand() % 5 + 1, &folder[10], 10);
					strcpy(&folder[11], ".bmp");
					break;
				case -42: //oe
					strcpy(&folder[4], "oe-up/");
					itoa(rand() % 5 + 1, &folder[10], 10);
					strcpy(&folder[11], ".bmp");
					break;
				case -36: //ue
					strcpy(&folder[4], "ue-up/");
					itoa(rand() % 5 + 1, &folder[10], 10);
					strcpy(&folder[11], ".bmp");
					break;
				case -4: //ue
					strcpy(&folder[4], "ue-low/");
					itoa(rand() % 5 + 1, &folder[11], 10);
					strcpy(&folder[12], ".bmp");
					break;
				case 63: //?
					strcpy(&folder[4], "frage/");
					itoa(rand() % 5 + 1, &folder[10], 10);
					strcpy(&folder[11], ".bmp");
					break;
				case 46: //.
					strcpy(&folder[4], "punkt/1.bmp");
					break;
				default:
					folder[4] = text[i];
					if (islower(text[i]) != 0) {
						strcpy(&folder[5], "-low/");
						itoa(rand() % 5 + 1, &folder[10], 10);
						strcpy(&folder[11], ".bmp");
					} else if (isupper(text[i])) {
						strcpy(&folder[5], "-up/");
						itoa(rand() % 5 + 1, &folder[9], 10);
						strcpy(&folder[10], ".bmp");
					} else {
						strcpy(&folder[5], "/");
						itoa(rand() % 5 + 1, &folder[6], 10);
						strcpy(&folder[7], ".bmp");
					}

					break;
			}

			std::string file_name(&folder[0]);
			bitmap_image letter(file_name);
			unsigned int tmpwidth = 0;
			for (int j = 0; text[i + j] != 32; j++) {
				if (j > 10) {
					break;
				}
				tmpwidth += 45;
			}

			if (tmpwidth + width >= 2480 - 256) {
				height += 128;
				width = 256;
			}
			if (height >= DinA4 - 256) {
				height = 256;
				width = 256;
				image.save_image("output"+ std::to_string(pages)+".bmp");
				pages++;
				image.clear(0xff);
			}
			
			if (letter.height() >= 128) {
				image.copy_from(letter, width, height);
			}
			else {
				image.copy_from(letter, width, height + 128 - letter.height());
			}
			width += letter.width() + 8;
		}
		image.save_image("output" + std::to_string(pages) + ".bmp");
	}

	system("pause");
	return 0;
}


/*
   Note: In some of the tests a bitmap image by the name of 'test.bmp'
         is required. If not present the test will fail.
*/
