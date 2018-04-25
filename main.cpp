#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <algorithm>

int currentShot = 0;
int gunAttachments[2][4];
int scopeType[2];
int attMod[2];
int cur_gun_id[3];
int cur_eqp_gun = 1;
int elapsed = 0;
int stance;
bool rapidFire[3];
bool autoFire[3];
bool isOn = false;
bool isMapOpen = false;
bool isInventoryOpen = false;
bool isMenuOpen = false;
bool rapidFireRunning = false;


using namespace std;

struct Weapon {
	int id;
	int val_x[3][40];
	int val_y[3][40];
	int RPS;
	bool isSingle;
	string name;
} AK, Groza, M16, ScarL, M4, Aug, MG, UMP, Uzi, Vec, Thompson, Winchester, VSS, Mini14, SKS, Kar98, MK14, M24, AWM, Glock, P92, P1911, R45, Revolver;

Weapon Guns[3];

void initARs() {
	AK.id = 1;
	//difference - 1.394117647058824
	int tempAKY0[40] = { 19,19,19,19,19,19,19,19,19,19,19,22,22,22,22,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23 };
	int tempAKY1[40] = { 17,17,17,17,17,17,17,17,17,17,17,20,20,20,20,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21 };
	int tempAKY2[40] = { 14,14,14,14,14,14,14,14,14,14,14,17,17,17,17,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18 };
	copy(tempAKY0, tempAKY0 + 40, AK.val_y[0]);
	copy(tempAKY1, tempAKY1 + 40, AK.val_y[1]);
	copy(tempAKY2, tempAKY2 + 40, AK.val_y[2]);
	AK.RPS = 100;
	AK.name = "AK47";

	Groza.id = 2;
	int tempGrozaY0[40] = { 19,19,19,19,19,19,19,19,19,19,19,22,22,22,22,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23 };
	int tempGrozaY1[40] = { 17,17,17,17,17,17,17,17,17,17,17,20,20,20,20,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21 };
	int tempGrozaY2[40] = { 14,14,14,14,14,14,14,14,14,14,14,17,17,17,17,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18 };
	copy(tempGrozaY0, tempGrozaY0 + 40, Groza.val_y[0]);
	copy(tempGrozaY1, tempGrozaY1 + 40, Groza.val_y[1]);
	copy(tempGrozaY2, tempGrozaY2 + 40, Groza.val_y[2]);
	Groza.RPS = 80;
	Groza.name = "Groza";

	M16.id = 3;
	//Difference - 1.923076923076923
	int tempM16Y0[40] = { 15,15,15,17,19,19,19,19,19,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16 };
	int tempM16Y1[40] = { 13,13,13,15,17,17,17,17,17,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14 };
	int tempM16Y2[40] = { 10,10,10,12,14,14,14,14,14,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11 };
	copy(tempM16Y0, tempM16Y0 + 40, M16.val_y[0]);
	copy(tempM16Y1, tempM16Y1 + 40, M16.val_y[1]);
	copy(tempM16Y2, tempM16Y2 + 40, M16.val_y[2]);
	//M16.val_y = {25,25,25,29,33,33,32,33,32,32,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30};
	M16.RPS = 75;
	M16.name = "M16";

	ScarL.id = 4;
	//Difference - 1.25
	int tempScarY0[40] = { 18,19,20,19,20,20,20,20,20,20,21,21,22,22,22,22,23,24,24,25,26,28,29,29,30,29,30,29,30,29,30,29,29,29,29,29,30,30,30,30 };
	int tempScarY1[40] = { 16,17,18,17,18,18,18,18,18,18,19,19,20,20,20,20,21,22,22,23,24,26,27,27,28,27,28,27,28,27,28,27,27,27,27,27,28,28,28,28 };
	int tempScarY2[40] = { 13,14,15,14,15,15,15,15,15,15,16,16,17,17,17,17,18,19,19,20,21,23,24,24,25,24,25,24,25,24,25,24,24,24,24,24,25,25,25,25 };
	copy(tempScarY0, tempScarY0 + 40, ScarL.val_y[0]);
	copy(tempScarY1, tempScarY1 + 40, ScarL.val_y[1]);
	copy(tempScarY2, tempScarY2 + 40, ScarL.val_y[2]);
	//ScarL.val_y={20,21,22,21,22,22,23,22,23,23,24,24,25,25,25,25,26,27,28,29,30,32,34,34,35,34,35,34,35,34,35,34,34,34,34,34,35,35,35,35,35,35,35,35,35,35}
	ScarL.RPS = 96;
	ScarL.name = "Scar-L";

	M4.id = 5;
	int tempM4Y0[40] = { 21,21,21,21,21,21,21,21,21,23,23,24,23,24,25,25,26,27,27,32,31,31,31,31,31,31,31,32,32,32,35,35,35,35,35,35,35,35,35,35 };
	int tempM4Y1[40] = { 17,17,17,17,17,17,17,17,17,19,19,20,19,20,21,21,22,23,23,28,27,27,27,27,27,27,27,28,28,28,31,31,31,31,31,31,31,31,31,31 };
	int tempM4Y2[40] = { 13,13,13,13,13,13,13,13,13,15,15,16,15,16,17,17,18,19,19,24,23,23,23,23,23,23,23,24,24,24,27,27,27,27,27,27,27,27,27,27 };
	copy(tempM4Y0, tempM4Y0 + 40, M4.val_y[0]);
	copy(tempM4Y1, tempM4Y1 + 40, M4.val_y[1]);
	copy(tempM4Y2, tempM4Y2 + 40, M4.val_y[2]);
	//M4.val_y = {21,21,21,21,21,21,21,21,21,23,23,24,23,24,25,25,26,27,27,32,31,31,31,31,31,31,31,32,32,32,35,35,35,35,35,35,35,35,35,35,35}
	M4.RPS = 86;
	M4.name = "M4";

	Aug.id = 6;
	int tempAugY0[40] = { 18,19,20,19,20,20,20,20,20,20,21,21,22,22,22,22,23,24,24,25,26,28,29,29,30,29,30,29,30,29,30,29,29,29,29,29,30,30,30,30 };
	int tempAugY1[40] = { 16,17,18,17,18,18,18,18,18,18,19,19,20,20,20,20,21,22,22,23,24,26,27,27,28,27,28,27,28,27,28,27,27,27,27,27,28,28,28,28 };
	int tempAugY2[40] = { 13,14,15,14,15,15,15,15,15,15,16,16,17,17,17,17,18,19,19,20,21,23,24,24,25,24,25,24,25,24,25,24,24,24,24,24,25,25,25,25 };
	copy(tempAugY0, tempAugY0 + 40, Aug.val_y[0]);
	copy(tempAugY1, tempAugY1 + 40, Aug.val_y[1]);
	copy(tempAugY2, tempAugY2 + 40, Aug.val_y[2]);
	Aug.RPS = 86;
	Aug.name = "Aug";

	MG.id = 7;
	int tempMGY0[40] = { 18,19,20,19,20,20,20,20,20,20,21,21,22,22,22,22,23,24,24,25,26,28,29,29,30,29,30,29,30,29,30,29,29,29,29,29,30,30,30,30 };
	int tempMGY1[40] = { 16,17,18,17,18,18,18,18,18,18,19,19,20,20,20,20,21,22,22,23,24,26,27,27,28,27,28,27,28,27,28,27,27,27,27,27,28,28,28,28 };
	int tempMGY2[40] = { 13,14,15,14,15,15,15,15,15,15,16,16,17,17,17,17,18,19,19,20,21,23,24,24,25,24,25,24,25,24,25,24,24,24,24,24,25,25,25,25 };
	copy(tempMGY0, tempMGY0 + 40, MG.val_y[0]);
	copy(tempMGY1, tempMGY1 + 40, MG.val_y[1]);
	copy(tempMGY2, tempMGY2 + 40, MG.val_y[2]);
	MG.RPS = 75;
	MG.name = "MG";
}
void initSMGs() {
	UMP.id = 8;
	int tempUMPY0[40] = { 18,19,18,19,18,19,19,21,23,24,23,24,23,24,23,24,23,24,23,24,23,24,24,25,24,25,24,25,24,25,24,25,25,26,25,26,25,26,25,26 };
	int tempUMPY1[40] = { 14,15,14,15,14,15,15,17,19,20,19,20,19,20,19,20,19,20,19,20,19,20,20,21,20,21,20,21,20,21,20,21,21,22,21,22,21,22,21,22 };
	int tempUMPY2[40] = { 10,11,10,11,10,11,11,13,15,16,15,16,15,16,15,16,15,16,15,16,15,16,16,17,16,17,16,17,16,17,16,17,17,18,17,18,17,18,17,18 };
	copy(tempUMPY0, tempUMPY0 + 40, UMP.val_y[0]);
	copy(tempUMPY1, tempUMPY1 + 40, UMP.val_y[1]);
	copy(tempUMPY2, tempUMPY2 + 40, UMP.val_y[2]);
	UMP.RPS = 92;
	UMP.name = "UMP";

	Uzi.id = 9;
	int tempUziY0[40] = { 16,17,18,20,21,22,23,24,25,26,28,30,32,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34 };
	int tempUziY1[40] = { 14,15,14,15,14,15,15,17,19,20,19,20,19,20,19,20,19,20,19,20,19,20,20,21,20,21,20,21,20,21,20,21,21,22,21,22,21,22,21,22 };
	int tempUziY2[40] = { 10,11,10,11,10,11,11,13,15,16,15,16,15,16,15,16,15,16,15,16,15,16,16,17,16,17,16,17,16,17,16,17,17,18,17,18,17,18,17,18 };
	copy(tempUziY0, tempUziY0 + 40, Uzi.val_y[0]);
	copy(tempUziY1, tempUziY1 + 40, Uzi.val_y[1]);
	copy(tempUziY2, tempUziY2 + 40, Uzi.val_y[2]);
	Uzi.RPS = 48;
	Uzi.name = "Uzi";

	Vec.id = 10;
	int tempVecY0[40] = { 16,17,18,20,21,22,23,24,25,26,28,30,32,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34 };
	int tempVecY1[40] = { 14,15,14,15,14,15,15,17,19,20,19,20,19,20,19,20,19,20,19,20,19,20,20,21,20,21,20,21,20,21,20,21,21,22,21,22,21,22,21,22 };
	int tempVecY2[40] = { 10,11,10,11,10,11,11,13,15,16,15,16,15,16,15,16,15,16,15,16,15,16,16,17,16,17,16,17,16,17,16,17,17,18,17,18,17,18,17,18 };
	copy(tempVecY0, tempVecY0 + 40, Vec.val_y[0]);
	copy(tempVecY1, tempVecY1 + 40, Vec.val_y[1]);
	copy(tempVecY2, tempVecY2 + 40, Vec.val_y[2]);
	Vec.RPS = 55;
	Vec.name = "Vector";

	Thompson.id = 11;
	int tempThompsonY0[40] = { 16,17,18,20,21,22,23,24,25,26,28,30,32,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34 };
	int tempThompsonY1[40] = { 14,15,14,15,14,15,15,17,19,20,19,20,19,20,19,20,19,20,19,20,19,20,20,21,20,21,20,21,20,21,20,21,21,22,21,22,21,22,21,22 };
	int tempThompsonY2[40] = { 10,11,10,11,10,11,11,13,15,16,15,16,15,16,15,16,15,16,15,16,15,16,16,17,16,17,16,17,16,17,16,17,17,18,17,18,17,18,17,18 };
	copy(tempThompsonY0, tempThompsonY0 + 40, Thompson.val_y[0]);
	copy(tempThompsonY1, tempThompsonY1 + 40, Thompson.val_y[1]);
	copy(tempThompsonY2, tempThompsonY2 + 40, Thompson.val_y[2]);
	Thompson.RPS = 86;
	Thompson.name = "Thompson";
}
void initSnipers() {
	int tempArr[40];
	for (int i = 0; i<40; i++)
		tempArr[i] = 15;

	Winchester.id = 12;
	copy(tempArr, tempArr + 40, Winchester.val_y[0]);
	copy(tempArr, tempArr + 40, Winchester.val_y[1]);
	copy(tempArr, tempArr + 40, Winchester.val_y[2]);
	Winchester.RPS = 500; // No idea o_O
	Winchester.name = "Winchester";

	VSS.id = 13;
	copy(tempArr, tempArr + 40, VSS.val_y[0]);
	copy(tempArr, tempArr + 40, VSS.val_y[1]);
	copy(tempArr, tempArr + 40, VSS.val_y[2]);
	VSS.RPS = 86;
	VSS.name = "VSS";

	Mini14.id = 14;
	copy(tempArr, tempArr + 40, Mini14.val_y[0]);
	copy(tempArr, tempArr + 40, Mini14.val_y[1]);
	copy(tempArr, tempArr + 40, Mini14.val_y[2]);
	Mini14.RPS = 100;
	Mini14.name = "Mini14";

	SKS.id = 19;
	copy(tempArr, tempArr + 40, SKS.val_y[0]);
	copy(tempArr, tempArr + 40, SKS.val_y[1]);
	copy(tempArr, tempArr + 40, SKS.val_y[2]);
	SKS.RPS = 90;
	SKS.name = "SKS";

	Kar98.id = 16;
	copy(tempArr, tempArr + 40, Kar98.val_y[0]);
	copy(tempArr, tempArr + 40, Kar98.val_y[1]);
	copy(tempArr, tempArr + 40, Kar98.val_y[2]);
	Kar98.RPS = 1900;
	Kar98.name = "Kar98";

	MK14.id = 17;
	copy(tempArr, tempArr + 40, MK14.val_y[0]);
	copy(tempArr, tempArr + 40, MK14.val_y[1]);
	copy(tempArr, tempArr + 40, MK14.val_y[2]);
	MK14.RPS = 90;
	MK14.name = "MK14";

	M24.id = 18;
	copy(tempArr, tempArr + 40, M24.val_y[0]);
	copy(tempArr, tempArr + 40, M24.val_y[1]);
	copy(tempArr, tempArr + 40, M24.val_y[2]);
	M24.RPS = 1800;
	M24.name = "M24";

	AWM.id = 19;
	copy(tempArr, tempArr + 40, AWM.val_y[0]);
	copy(tempArr, tempArr + 40, AWM.val_y[1]);
	copy(tempArr, tempArr + 40, AWM.val_y[2]);
	AWM.RPS = 1850;
	AWM.name = "AWM";
}
void initPistols() {
	int tempArr[40];
	for (int i = 0; i<40; i++)
		tempArr[i] = 15;

	Glock.id = 20;
	copy(tempArr, tempArr + 40, Glock.val_y[0]);
	copy(tempArr, tempArr + 40, Glock.val_y[1]);
	copy(tempArr, tempArr + 40, Glock.val_y[2]);
	Glock.RPS = 60;
	Glock.name = "Glock";

	P92.id = 21;
	copy(tempArr, tempArr + 40, P92.val_y[0]);
	copy(tempArr, tempArr + 40, P92.val_y[1]);
	copy(tempArr, tempArr + 40, P92.val_y[2]);
	P92.RPS = 135;
	P92.name = "P92";

	P1911.id = 22;
	copy(tempArr, tempArr + 40, P1911.val_y[0]);
	copy(tempArr, tempArr + 40, P1911.val_y[1]);
	copy(tempArr, tempArr + 40, P1911.val_y[2]);
	P1911.RPS = 110;
	P1911.name = "P1911";

	R45.id = 23;
	copy(tempArr, tempArr + 40, R45.val_y[0]);
	copy(tempArr, tempArr + 40, R45.val_y[1]);
	copy(tempArr, tempArr + 40, R45.val_y[2]);
	R45.RPS = 400;    //Unknown
	R45.name = "R45";

	Revolver.id = 24;
	copy(tempArr, tempArr + 40, Revolver.val_y[0]);
	copy(tempArr, tempArr + 40, Revolver.val_y[1]);
	copy(tempArr, tempArr + 40, Revolver.val_y[2]);
	Revolver.RPS = 400;
	Revolver.name = "Revolver";
}

string b2s(bool b) {
	if (b)
		return "True";
	return "False";
}
string getCurrentAttachments() {
	string ret = "|";
	int i = cur_eqp_gun - 1;
	if (gunAttachments[i][0])
		ret += " Vertical Grip |";
	if (gunAttachments[i][1])
		ret += " Angled Grip |";
	if (gunAttachments[i][2])
		ret += " Stock |";
	if (gunAttachments[i][3])
		ret += " Compensator |";
	return ret;
}
void init() {
	initARs();
	initSMGs();
	initSnipers();
	initPistols();
}
bool keyDown(int vcode) {
	return GetAsyncKeyState(vcode) & ~32767;
}
bool isRunning() {
	if (isMapOpen)
		return false;
	if (isMenuOpen)
		return false;
	if (isInventoryOpen)
		return false;
	return isOn;
}
void listKeys() {
	cout << "F1: Change AR" << endl <<
		"F2: Change SMG" << endl <<
		"F3: Change Sniper" << endl <<
		"F4: Change Pistol" << endl << endl <<
		"0: Remove Attachments" << endl <<
		"1: Change Grip" << endl <<
		"2: Add Stock" << endl <<
		"3: Add Compensator" << endl <<
		"4: Change Scope" << endl <<
		"6: Reset All Parameters" << endl <<
		"G: AutoFire";
}
void status() {
	int i = cur_eqp_gun - 1;
	system("CLS");
	cout << "Status: " << b2s(isRunning()) << endl <<
		"   Map: " << b2s(isMapOpen) << endl <<
		"   Menu: " << b2s(isMenuOpen) << endl <<
		"   Inventory: " << b2s(isInventoryOpen) << endl <<
		"Mouse1 Status: " << b2s(keyDown(1)) << endl <<
		"Weapon: " << Guns[i].name << endl <<
		"Gun Slot: " << cur_eqp_gun << endl <<
		"Scope: " << scopeType[i] << endl <<
		"Stance: " << stance << endl <<
		"Rapid Fire: " << b2s(rapidFire[i]) << endl <<
		"RPS: " << Guns[i].RPS << endl <<
		"Current Shot: " << currentShot << endl <<
		"Single Fire: " << Guns[i].isSingle << endl <<
		"Attachments: " << getCurrentAttachments() << endl <<
		"Base Y: " << Guns[i].val_y[stance][currentShot] << endl <<
		"Mod Y: " << attMod[i] << endl << endl;
	listKeys();
}
void moveMouse() {
	int i = cur_eqp_gun - 1;
	Sleep(Guns[i].RPS - 1);
	int valX = 0;
	int valY = (Guns[i].val_y[stance][currentShot] - attMod[i]) * scopeType[i];
	if (valY<0)
		valY = 0;
	mouse_event(MOUSEEVENTF_MOVE, Guns[i].val_x[stance][0], valY, 0, 0);
	currentShot++;
	if (currentShot >= 40)
		currentShot = 0;
}
void rapidFireFunc() {
	//turn mouse off
	if (isOn)
		keybd_event(1, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	rapidFireRunning = true;
	isOn = false;
	while (rapidFireRunning)
	{
		if (keyDown(1))
		{
			rapidFireRunning = false;
			Sleep(200);
			isOn = true;
			break;
		}
		keybd_event(75, 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0);
		keybd_event(75, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		moveMouse();
		status();
	}
}//Attachments

void removeAttachments() {
	int i = cur_eqp_gun - 1;
	for (int j = 0; j<4; j++)
		gunAttachments[i][j] = false;
	attMod[i] = 0;
	scopeType[i] = 1;
}
void resetToDefault() {
	Guns[0] = Winchester;//load a default AR to button 1;
	Guns[1] = AK;//load a default AR to button 1;
	Guns[2] = P1911;//load a default AR to button 1;
	rapidFire[0] = false;
	rapidFire[1] = false;
	rapidFire[2] = false;
	cur_gun_id[0] = 12;
	cur_gun_id[1] = 1;
	cur_gun_id[2] = 22;
	cur_eqp_gun = 1;
	removeAttachments();
	cur_eqp_gun = 2;
	removeAttachments();
}
