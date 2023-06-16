#include <windows.h>
#include "player_info.h"

int space_pressed;       //���� Ű �ߺ��� �����ϱ� ���� ����
int CM_move_dir = -1; // 0: �����̵�, 1: ���� �̵� -1: ����
int CM_jump_acc = 28; //���� �� ���ӵ�
int CM_jump;          //0: ���� �� ��, 1: ���� �� 2: ���� ��
int cool_time;

//BOOL�� �ϸ� ������ ���� int�� ��ü
int cat_ready = 0;
int awp_cat_delay = 0;

double CM_x, CM_y;    //�÷��̾� ĳ������ ��ġ

bool is_zoom = false;
bool avail_awp = false;

int health = 100; //�÷��̾� �⺻ ü�� 100
int recovery_delay = 0; //�÷��̾� ü�� ȸ�� ������

//�÷��̾� ü�� ��ġ ǥ��
void player_health(HDC mdc, RECT rt, double ss_x, double ss_y, double landing_shake, int health) {
	TCHAR out[10];
	HFONT hfont, oldfont;
	hfont = CreateFont(60, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("���� ���"));
	oldfont = (HFONT)SelectObject(mdc, hfont);
	SetBkMode(mdc, TRANSPARENT);
	SetTextColor(mdc, RGB(0, 0, 0));
	wsprintf(out, L"%d", health);
	for (int i = -3; i <= 3; i++)
		for (int j = -4; j <= 4; j++)
			TextOut(mdc, rt.left + 320 + ss_x + i, rt.bottom - 60 + ss_y + landing_shake + j, out, lstrlen(out));

	SetTextColor(mdc, RGB(255, 255, 255));

	TextOut(mdc, rt.left + 320 + ss_x, rt.bottom - 60 + ss_y + landing_shake, out, lstrlen(out));
	SelectObject(mdc, oldfont);
	DeleteObject(hfont);
}

//����ź ��� �ð� ���
void show_gren_time(HDC mdc, double ss_x, double ss_y, double landing_shake, int gren_time) {
	TCHAR out[100] = { 0 };
	HFONT hfont, oldfont;
	hfont = CreateFont(60, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("���� ���"));
	oldfont = (HFONT)SelectObject(mdc, hfont);
	SetBkMode(mdc, TRANSPARENT);
	
	if (gren_time > 1) {
		wsprintf(out, L"%d", gren_time);
		SetTextColor(mdc, RGB(0, 0, 0));
		for (int i = -3; i <= 3; i++)
			for (int j = -4; j <= 4; j++)
				TextOut(mdc, 500 + ss_x + i, 690 + ss_y + landing_shake + j, out, lstrlen(out));
		SetTextColor(mdc, RGB(255, 255, 255));
		TextOut(mdc, 500 + ss_x, 690 + ss_y + landing_shake, out, lstrlen(out));
	}

	if (gren_time == 0) {
		SetTextColor(mdc, RGB(0, 0, 0));
		for (int i = -3; i <= 3; i++)
			for (int j = -4; j <= 4; j++)
				TextOut(mdc, 500 + ss_x + i, 690 + ss_y + landing_shake + j, L"L SHIFT", lstrlen(L"L SHIFT"));
		SetTextColor(mdc, RGB(255, 255, 255));
		TextOut(mdc, 500 + ss_x, 690 + ss_y + landing_shake, L"L SHIFT", lstrlen(L"L SHIFT"));
	}

	SelectObject(mdc, oldfont);
	DeleteObject(hfont);
}