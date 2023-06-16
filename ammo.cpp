#include <windows.h>
#include <tchar.h>
#include <math.h>
#include <iostream>
#include <random>
#include "ammo.h"
#include "gun_info.h"

enum gun_name_ammo {
	null, scar_h, m16, mp_44, mg_42, awp
};

BOOL is_draw = FALSE;					  //TRUE�� �� �Ѿ� ������ �׸�
int ammo;							      //��ź ��
int draw_timer;							  //������ �׷����� �ð��� ���Ѵ�. ��ġ�� �������� �� �������� �׷�����.
double angle;							  //�Ѿ� ������ ����
double ammo_x1, ammo_y1, ammo_x2, ammo_y2; //�Ѿ� ������ �׷����� ��ǥ
double dist;//�÷��̾�� ��Ʈ ������ ������ �Ÿ�

BOOL draw_hit = FALSE;					  //TRUE�� �� ��Ʈ ����Ʈ�� �׸�
int hit_timer;							  //��Ʈ ����Ʈ�� �׷����� �ð�	
int hit;									  //��Ʈ ������ ���� ������ �ε���
double hit_x, hit_y;   //������ ���ο��� �����Ǵ� ���� x,y ��ǥ

double var;            //���� ���� ����� ���� �ݵ����� ���� ��Ȯ���� ������, ��ġ�� ������ ���� �л굵�� Ŀ��

int ind_size = 100; //ammo_indicator�� ��Ʈ ũ��
int ind_x = 1360;   //ammo_indicator�� ��Ʈ ��ġ
int ind_y = 650;    //ammo_indicator�� ��Ʈ ��ġ
int ind_ani;        //�Ѿ��� �Ҹ� �� ������ �ִϸ��̼� ���, 0: ��� ����, 1: ���

int shoot_delay; //���� �ӵ� ���� ���� //��ġ�� �������� ���簡 ������
int r_pressed;      //������ �ߺ� �Է� ������ ���� ����
int reload;      //0�̸� ������ ����, 1�̸� ������ ��
int reload_x;    //������ ǥ�ñ� x2 ��ǥ

int empty;   //�Ѿ� ��� �Ҹ� �� 1�� ����

BOOL can_shoot = TRUE; //���� �ӵ��� ���� ���� ���콺 ��Ÿ�Ͽ� �� ������ ��� ���� ���� ����
int after_delay;       //�� ������ ���� �ӵ� ��ġ�� �ٸ��� ���콺�� �ƹ��� ���� ������ �߻簡 ���� �ʴ´�.

int reload_delay; //mg_42 ������ �ӵ� ���� ����

ellipse e[100];
int edx = 0;

double incline;
double rect_x_end, rect_y_end;
double rect_x_start, rect_y_start;
int rect_size_x = 20, rect_size_y = 20;
int rect_dir;
BOOL is_lazer = FALSE;
BOOL can_make_rect = TRUE;
BOOL is_rect = FALSE;
int rect_acc;
int rect_delay;
int rect_delete_delay;


//�Ѿ� ���� �׸���
void draw_ammo(HDC mdc, double x1, double y1, double x2, double y2, int GUN_number) { 
	if (GUN_number != awp) {
		HPEN hpen, oldpen;
		hpen = CreatePen(PS_SOLID, 7, RGB(255, 212, 0));
		oldpen = (HPEN)SelectObject(mdc, hpen);

		MoveToEx(mdc, x1, y1, NULL);
		LineTo(mdc, x2, y2);

		SelectObject(mdc, oldpen);
		DeleteObject(hpen);
	}

	if (GUN_number == awp) {
		HPEN hpen, oldpen;
		hpen = CreatePen(PS_SOLID, 15, RGB(255, 212, 0));
		oldpen = (HPEN)SelectObject(mdc, hpen);

		MoveToEx(mdc, x1, y1, NULL);
		LineTo(mdc, x2, y2);

		SelectObject(mdc, oldpen);
		DeleteObject(hpen);
	}
}

//��ź�� ǥ��
void ammo_indicator(HDC mdc, int max_ammo, int ammo, int ind_size, int ind_x, int ind_y) {
	int ammo_empty = 0;
	TCHAR lpout[50];
	HFONT hfont, oldfont;
	hfont = CreateFont(ind_size, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("���� ���"));
	oldfont = (HFONT)SelectObject(mdc, hfont);
	SetBkMode(mdc, TRANSPARENT);
	SetTextColor(mdc, RGB(255, 212, 0));

	if ((max_ammo - ammo) / 100 > 0 && max_ammo - ammo > 0) {        //�Ѿ��� �� �ڸ��� ������ ��
		wsprintf(lpout, L"%d", max_ammo - ammo);
		TextOut(mdc, ind_x - 30, ind_y, lpout, lstrlen(lpout));
	}
	else if ((max_ammo - ammo) / 10 > 0 && max_ammo - ammo > 0) {       //�Ѿ��� �� �ڸ��� ������ ��
		wsprintf(lpout, L"%d", max_ammo - ammo);
		TextOut(mdc, ind_x, ind_y, lpout, lstrlen(lpout));
	}
	else if ((max_ammo - ammo) / 10 == 0 && max_ammo - ammo > 0) { //�Ѿ��� �� �ڸ��� ������ ��
		wsprintf(lpout, L" %d", max_ammo - ammo);
		TextOut(mdc, ind_x, ind_y, lpout, lstrlen(lpout));
	}

	if (max_ammo - ammo == 0)                                //�Ѿ� ��� �Ҹ� �� ������ ǥ�� 
		ammo_empty = 1;
	
	SelectObject(mdc, oldfont);
	DeleteObject(hfont);

	hfont = CreateFont(ind_size, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("���� ���"));
	oldfont = (HFONT)SelectObject(mdc, hfont);
	SetBkMode(mdc, TRANSPARENT);
	SetTextColor(mdc, RGB(255, 0, 0));

	if (ammo_empty == 1) //�Ѿ� ��� �Ҹ� �� ������ ǥ�� 
		TextOut(mdc, ind_x, ind_y, L" R", lstrlen(L" R"));

	SelectObject(mdc, oldfont);
	DeleteObject(hfont);
}

//������ ������ ǥ��
void reload_indicator(HDC mdc, int x, int y, int x2, int y2, int x3, int y3, int x4, int y4) {
	HBRUSH hbrush, oldbrush;
	HPEN hpen, oldpen;

	hbrush = CreateSolidBrush(RGB(0, 0, 0));
	oldbrush = (HBRUSH)SelectObject(mdc, hbrush);

	Rectangle(mdc, x3, y3, x4, y4);

	SelectObject(mdc, oldbrush);
	DeleteObject(hbrush);

	hbrush = CreateSolidBrush(RGB(255, 255, 255));
	oldbrush = (HBRUSH)SelectObject(mdc, hbrush);

	Rectangle(mdc, x, y, x2, y2);

	SelectObject(mdc, oldbrush);
	DeleteObject(hbrush);

	hbrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	oldbrush = (HBRUSH)SelectObject(mdc, hbrush);
	hpen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	oldpen = (HPEN)SelectObject(mdc, hpen);

	Rectangle(mdc, x3, y3, x4, y4);

	SelectObject(mdc, oldbrush);
	DeleteObject(hbrush);
	SelectObject(mdc, oldpen);
	DeleteObject(hpen);
}

//�÷��̾�� ��Ʈ ����Ʈ�� �Ÿ� ���
int cal_dist(double x1, double y1, double x2, double y2) {
	double distance = sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));

	return distance;
}

//�Ѹ��� �ٸ� ����� ���
int cal_damage(int monster_hp, int GUN_number) {
	return monster_hp - Gun::damage(GUN_number);
}

void push_ellipse(int del, int idx) {
	for (int i = del; i < idx; i++) {
		e[i].x = e[i + 1].x;
		e[i].y = e[i + 1].y;
		e[i].acc = e[i + 1].acc;
		e[i].size = e[i + 1].size;
		e[i].dir = e[i + 1].dir;
	}
	idx--;
	e[idx].x = -400;
	e[idx].y = 1500;
	e[idx].size = 0;
	e[idx].acc = 0;
	e[idx].dir = -1;
}
