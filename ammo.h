#pragma once
struct ellipse {
	int size;
	double x, y;
	int dir;
	int acc;
};

extern int edx; //ellipse-index
extern double incline;
extern double rect_x_end, rect_y_end;
extern double rect_x_start, rect_y_start;
extern int rect_size_x, rect_size_y;
extern int rect_dir;
extern BOOL is_lazer;
extern BOOL can_make_rect;
extern BOOL is_rect;
extern int rect_acc;
extern int rect_delay;
extern int rect_delete_delay;


extern BOOL is_draw;					  //TRUE�� �� �Ѿ� ������ �׸�
extern int ammo;							      //��ź ��
extern int draw_timer;							  //������ �׷����� �ð��� ���Ѵ�. ��ġ�� �������� �� �������� �׷�����.
extern double angle;							  //�Ѿ� ������ ����
extern double ammo_x1, ammo_y1, ammo_x2, ammo_y2; //�Ѿ� ������ �׷����� ��ǥ
extern double dist;//�÷��̾�� ��Ʈ ������ ������ �Ÿ�

extern BOOL draw_hit;					  //TRUE�� �� ��Ʈ ����Ʈ�� �׸�
extern int hit_timer;							  //��Ʈ ����Ʈ�� �׷����� �ð�	
extern int hit;									  //��Ʈ ������ ���� ������ �ε���
extern double hit_x, hit_y;   //������ ���ο��� �����Ǵ� ���� x,y ��ǥ

extern double var;            //���� ���� ����� ���� �ݵ����� ���� ��Ȯ���� ������, ��ġ�� ������ ���� �л굵�� Ŀ��

extern int ind_size; //ammo_indicator�� ��Ʈ ũ��
extern int ind_x;   //ammo_indicator�� ��Ʈ ��ġ
extern int ind_y;    //ammo_indicator�� ��Ʈ ��ġ
extern int ind_ani;        //�Ѿ��� �Ҹ� �� ������ �ִϸ��̼� ���, 0: ��� ����, 1: ���

extern int shoot_delay; //���� �ӵ� ���� ���� //��ġ�� �������� ���簡 ������
extern int r_pressed;      //������ �ߺ� �Է� ������ ���� ����
extern int reload;      //0�̸� ������ ����, 1�̸� ������ ��
extern int reload_x;    //������ ǥ�ñ� x2 ��ǥ

extern int empty;   //�Ѿ� ��� �Ҹ� �� 1�� ����

extern BOOL can_shoot; //���� �ӵ��� ���� ���� ���콺 ��Ÿ�Ͽ� �� ������ ��� ���� ���� ����
extern int after_delay;       //�� ������ ���� �ӵ� ��ġ�� �ٸ��� ���콺�� �ƹ��� ���� ������ �߻簡 ���� �ʴ´�.

extern int reload_delay; //mg_42 ������ �ӵ� ���� ����

int cal_dist(double x1, double y1, double x2, double y2);
void draw_ammo(HDC mdc, double x1, double y1, double x2, double y2, int GUN_number);
void ammo_indicator(HDC mdc, int max_ammo, int ammo, int ind_size, int ind_x, int ind_y);
void reload_indicator(HDC mdc, int x, int y, int x2, int y2, int x3, int y3, int x4, int y4);
int cal_damage(int monster_hp, int GUN_number);
void push_ellipse(int del, int idx);


