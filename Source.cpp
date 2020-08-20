#define _CRT_SECURE_NO_WARNINGS
//#define ALLOW_ROTATION

#include <TXLib.h>
#include "Vector3.h"
#include "Color.h"

//-------------------------------------------------

const size_t wWidth  = 800;
const size_t wHeight = 800;

double MoveSpeed = 4;

Color Background (32, 32, 32);
Color Foreground (TX_WHITE);

const size_t Thikness = 3;

double CubeLength = 0.15;

//-------------------------------------------------

#define RANDOMCOLOR Color (rand () % 255, rand () % 255, rand () % 255)

//-------------------------------------------------

void DrawLine3D (Vector3d coord1, Vector3d coord2);

void DrawLine3D (double x1, double y1, double z1, double x2, double y2, double z2);

void DrawCube ();

void Translate (Vector3d offset);

void Translate (double x, double y, double z);

void Rotate (Vector3d rotation);

void Rotate (double x, double y, double z);

void Control ();

void DrawOffset ();

//-------------------------------------------------

Vector3d Offset   (0, 0, -49.4);

Vector3d Rotation (0, 0, 0);

//-------------------------------------------------

int main ()

{

	_txConsoleMode = SW_SHOW;

	txCreateWindow (wWidth, wHeight);
	txDisableAutoPause ();

	SetWindowText (txWindow (), "I don't want to see 'TXLib' in my program title. (Test 3D Cube)");

	txBegin ();

	while (!GetAsyncKeyState (VK_ESCAPE))

	{

		txSetFillColor (Background);
		txClear ();

		DrawCube   ();
		DrawOffset ();

		Control ();

		txSleep (0);

	}

	return 0;

}

//-------------------------------------------------

void DrawCube ()

{

	txSetColor     (Foreground, Thikness);
	txSetFillColor (Foreground);

	double z1 = 50;
	double z2 = z1 + CubeLength;

	           //x1   y1  z1   x2   y2  z2
	DrawLine3D (-50,  50, z1,  50,  50, z1);
	DrawLine3D (-50, -50, z1,  50, -50, z1);
	DrawLine3D (-50,  50, z1, -50, -50, z1);
	DrawLine3D ( 50,  50, z1,  50, -50, z1);

	DrawLine3D (-50,  50, z2,  50,  50, z2);
	DrawLine3D (-50, -50, z2,  50, -50, z2);
	DrawLine3D (-50,  50, z2, -50, -50, z2);
	DrawLine3D ( 50,  50, z2,  50, -50, z2);

	DrawLine3D ( 50,  50, z1,  50,  50, z2);
	DrawLine3D ( 50, -50, z1,  50, -50, z2);

	DrawLine3D (-50,  50, z1, -50,  50, z2);
	DrawLine3D (-50, -50, z1, -50, -50, z2);

}

//-------------------------------------------------

void DrawLine3D (Vector3d coord1, Vector3d coord2)

{

	coord1 += Offset;
	coord2 += Offset;

	for (size_t i = 0; i < 3; i ++) if (coord1.data[i] == 0) coord1.data[i] = 1;
	for (size_t i = 0; i < 3; i ++) if (coord2.data[i] == 0) coord2.data[i] = 1;

#ifdef ALLOW_ROTATION

	//z rotation

	coord1.x = coord1.x * sin (Rotation.z) + coord1.y * cos (Rotation.z); 
	coord1.y = coord1.x * cos (Rotation.z) - coord1.y * sin (Rotation.z);
	coord1.z = coord1.z;

	coord2.x = coord2.x * sin (Rotation.z) + coord2.y * cos (Rotation.z); 
	coord2.y = coord2.x * cos (Rotation.z) - coord2.y * sin (Rotation.z);
	coord2.z = coord2.z;

	//y rotation

	coord1.x = coord1.x * sin (Rotation.y) + coord1.z * cos (Rotation.y); 
	coord1.z = coord1.x * cos (Rotation.y) - coord1.z * sin (Rotation.y);
	coord1.y = coord1.y;

	coord2.x = coord2.x * sin (Rotation.z) + coord2.z * cos (Rotation.z); 
	coord2.z = coord2.x * cos (Rotation.z) - coord2.z * sin (Rotation.z);
	coord2.y = coord2.y;

	//x rotation

	coord1.z = coord1.z * sin (Rotation.x) + coord1.y * cos (Rotation.x); 
	coord1.y = coord1.z * cos (Rotation.x) - coord1.y * sin (Rotation.x);
	coord1.z = coord1.z;

	coord2.z = coord2.z * sin (Rotation.x) + coord2.y * cos (Rotation.x); 
	coord2.y = coord2.z * cos (Rotation.x) - coord2.y * sin (Rotation.x);
	coord2.z = coord2.z;

#endif

	double x1 = coord1.x / coord1.z;
	double y1 = coord1.y / coord1.z;

	double x2 = coord2.x / coord2.z;
	double y2 = coord2.y / coord2.z;

	txLine (wWidth / 2 + x1, wHeight / 2 - y1, wWidth / 2 + x2, wHeight / 2 - y2);

}

//-------------------------------------------------

void DrawLine3D (double x1, double y1, double z1, double x2, double y2, double z2)

{

	DrawLine3D (Vector3d (x1, y1, z1), Vector3d (x2, y2, z2));

}

//-------------------------------------------------

void Translate (Vector3d offset)

{

	Offset += offset;

}

//-------------------------------------------------

void Translate (double x, double y, double z)

{

	Translate (Vector3d (x, y, z));

}

//-------------------------------------------------

void Rotate (Vector3d rotation)

{

	Rotation += rotation;

}

//-------------------------------------------------

void Rotate (double x, double y, double z)

{

	Rotate (Vector3d (x, y, z));

}

//-------------------------------------------------

void Control ()

{

	if (GetAsyncKeyState (VK_RIGHT)) Translate ( MoveSpeed, 0, 0); //+x offset
	if (GetAsyncKeyState (VK_LEFT))  Translate (-MoveSpeed, 0, 0); //-x offset

	if (GetAsyncKeyState (VK_UP))    Translate (0,  MoveSpeed, 0); //+y offset
	if (GetAsyncKeyState (VK_DOWN))  Translate (0, -MoveSpeed, 0); //-y offset

	if (GetAsyncKeyState (VK_PRIOR)) Translate (0, 0,  MoveSpeed / 10); //+z offset
	if (GetAsyncKeyState (VK_NEXT))  Translate (0, 0, -MoveSpeed / 10); //-z offset

#ifdef ALLOW_ROTATION

	if (GetAsyncKeyState ('A')) Rotate ( MoveSpeed, 0, 0);         //+x rotation
	if (GetAsyncKeyState ('D')) Rotate (-MoveSpeed, 0, 0);         //-x rotation

	if (GetAsyncKeyState ('W')) Rotate (0,  MoveSpeed, 0);         //+y rotation
	if (GetAsyncKeyState ('S')) Rotate (0, -MoveSpeed, 0);         //-y rotation
	
	if (GetAsyncKeyState ('Q')) Rotate (0, 0,  MoveSpeed);         //+z rotation
	if (GetAsyncKeyState ('E')) Rotate (0, 0, -MoveSpeed);         //-z rotation

	if (GetAsyncKeyState (VK_OEM_PLUS))  MoveSpeed += 0.1;         //+control velocity
	if (GetAsyncKeyState (VK_OEM_MINUS)) MoveSpeed -= 0.1;         //-control velocity

#endif

	if (GetAsyncKeyState ('Z')) CubeLength += 0.01;                //+cube length
	if (GetAsyncKeyState ('X')) CubeLength -= 0.01;                //-cube length

	if (GetAsyncKeyState ('C'))                                    //reset offset and rotation

	{
	
		Offset   = Vector3d (0, 0, -49.4);
		Rotation = Vector3d (0, 0,  0 );

		MoveSpeed = 4;

		CubeLength = 0.12;

		Foreground = TX_WHITE;

	}

	if (GetAsyncKeyState ('R')) Foreground = RANDOMCOLOR;          //да просто так

}

//-------------------------------------------------

void DrawOffset ()

{

	size_t       CharSize = 25;
	const char * Font     = "Consolas";

	char str[MAX_PATH] = "";

	sprintf (str, "Offset: %.1lf, %.1lf, %.1lf, Move speed: %.1lf\n", Offset.x, Offset.y, Offset.z, MoveSpeed);

	size_t x = 4;
	size_t y = wHeight - CharSize * 2 - 12;

	txSetColor     (RGB (24, 24, 24));
	txSetFillColor (RGB (24, 24, 24));

	txRectangle (0, y - 2, wWidth, wHeight);

	txSetColor     (RGB (0, 175, 255));
	txSetFillColor (RGB (0, 175, 255));

	txSelectFont (Font, CharSize, CharSize / 2.3, 1000);

	txTextOut (4, wHeight - CharSize - 4, str);

	sprintf (str, "Rotation: %.1lf, %.1lf, %.1lf, Cube length: %.2lf", Rotation.x, Rotation.y, Rotation.z, CubeLength);

	txTextOut (4, wHeight - CharSize * 2 - 8, str);

}