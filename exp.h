#pragma once
//����ġ. exp�� ���� �̸��� �Ϸ� ������ �浹�� ���� �̷��� ��
extern int experience;
//����ġ�� �����ϴ� ������ �����ϴ� ����. ����ġ ���� ȿ���� ����� �� ����Ѵ�.
extern int prev_up;
//����ġ�� ������ �� ����ġ ���� �̺�Ʈ�� �߻���Ų��.
extern BOOL exp_up;
extern int exp_x;
extern int exp_acc;
extern int out;
extern int exp_out_delay;

//���� ���� ��� ����
extern BOOL cant_buy_sound;
extern BOOL buy_sound;

void show_exp(HDC mdc, int experience, int x, int y);
void show_exp_add(HDC mdc, int prev_up, int x, int y);