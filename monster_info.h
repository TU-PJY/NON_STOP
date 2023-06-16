#pragma once
struct monster_info_regular { //������ ���� ����, �̵� ����, ��ġ�� �����ϴ� ����ü
	double x, y;
	int move_dir;
	int img_dir;
	int hp;
	int targeted;
	int height;
	int motion_acc;
};

struct monster_info_big { //���� ����
	double x, y;
	int move_dir;
	int img_dir;
	int hp;
	int targeted;
	int height;
	int motion_acc;
};

struct monster_info_air { //���� ����
	double x, y;
	int move_dir;
	int img_dir;
	int hp;
	int height;
	int motion_acc;
};

//���Ͱ� ���� �� ��ü �̹��� ���. ���� ���� ������ �̹������� �������.
struct dead_location {
	int monster_type; //1: �Ϲ� ����, 2: ���� ����, 3: ���� ����
	double x, y;
	int acc;
	int dir;
	int motion_dir;
};

//���� �ö� �� ���� �� �ִϸ��̼��� ����ϱ� ���� ����
extern int round_size;
extern int round_x;
extern int kill_count;
extern BOOL round_up; //�� ������ TRUE�� �Ǹ� �ִϸ��̼��� ����Ѵ�.

extern int game_round;			// ���� �ֱ⸦ ������

//���� ��ü �ε���
extern int ddx; //dead-index
extern int delete_delay;

extern int mdx_r;                 //�Ϲ� ���� �� (monster - index_regular)
extern int spawn_timer_r;   //���尡 �ö� ���� ���� �ֱⰡ ��������. -> ��ġ�� ��������. �⺻ ��ġ�� 500���� ����
extern const int spawn_timer_r_max;	// ���� �ֱ� ���� ��ġ

extern int mdx_big;				  //���� ���� ��
extern int spawn_timer_big;
extern const int spawn_timer_big_max;

extern int mdx_air;				  //���� ���� ��
extern int spawn_timer_air;
extern const int spawn_timer_air_max;

//awp ������ ����: �ּ� 1���� �̻��� ���Ͱ� �Ѿ˿� �¾ƾ��ϰ�, ���� is_hit�� TRUE�� �Ǿ� ���� ȿ�� �ߵ�
extern BOOL is_hit;

int calc_spawn_timer(int spawn_timer_max);

void spawn_monster_regular(int mdx, int BG_scanner, RECT rt);
void spawn_monster_big(int mdx_big, int BG_scanner, RECT rt);
void spawn_monster_air(int mdx_air, int BG_scanner, RECT rt);

void update_monster_dir_r(double monster_x, double CM_x, int mdx);
void update_monster_dir_big(double monster_x, double CM_x, int mdx_big);
void update_monster_dir_air(double monster_x, double CM_x, int mdx_air);

void monster_hp_ind(HDC mdc, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);

void monster_array_push_r(int hit, int idx);
void monster_array_push_big(int hit, int idx);
void monster_array_push_air(int i, int mdx_air);
void push_dead(int idx);