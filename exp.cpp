#include <windows.h>
#include "exp.h"

//����ġ. exp�� ���� �̸��� �Ϸ� ������ �浹�� ���� �̷��� ��
int experience;
//����ġ�� �����ϴ� ������ �����ϴ� ����. ����ġ ���� ȿ���� ����� �� ����Ѵ�.
int prev_up;
//����ġ�� ������ �� ����ġ ���� �̺�Ʈ�� �߻���Ų��.
BOOL exp_up = FALSE;
int exp_x = -150;
int exp_acc = 20;
int out = 1;
int exp_out_delay;

//����ġ ��ġ ǥ�� �Լ�
void show_exp(HDC mdc, int experience, int x, int y) {
	HFONT hfont, oldfont;
	TCHAR exp_tchar[1000] = { 0 };
	hfont = CreateFont(70, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("���� ���"));
	oldfont = (HFONT)SelectObject(mdc, hfont);
	SetBkMode(mdc, TRANSPARENT);
	SetTextColor(mdc, RGB(0, 0, 0));

	wsprintf(exp_tchar, L"%d", experience);
	for (int i = -3; i <= 3; i++)
		for (int j = -4; j <= 4; j++)
			TextOut(mdc, x + i, y + j, exp_tchar, lstrlen(exp_tchar));
	SetTextColor(mdc, RGB(255, 255, 255));
	TextOut(mdc, x, y, exp_tchar, lstrlen(exp_tchar));

	SelectObject(mdc, oldfont);
	DeleteObject(hfont);
}

//����ġ ȹ�� ��ġ ǥ�� �Լ�
void show_exp_add(HDC mdc, int prev_up, int x, int y) {
	HFONT hfont, oldfont;
	TCHAR exp_tchar[10] = { 0 };
	hfont = CreateFont(50, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("���� ���"));
	oldfont = (HFONT)SelectObject(mdc, hfont);
	SetBkMode(mdc, TRANSPARENT);
	SetTextColor(mdc, RGB(0, 0, 0));

	wsprintf(exp_tchar, L"EXP +%d", prev_up);
	for (int i = -3; i <= 3; i++)
		for (int j = -4; j <= 4; j++)
			TextOut(mdc, x + i, y + j, exp_tchar, lstrlen(exp_tchar));
	SetTextColor(mdc, RGB(255, 255, 255));
	TextOut(mdc, x, y, exp_tchar, lstrlen(exp_tchar));


	SelectObject(mdc, oldfont);
	DeleteObject(hfont);
}