#include "GameScene.h"

#include "Util.h"
#include "monster_info.h"
#include "player_info.h"
#include "images.h"
#include "ammo.h"
#include "exp.h"

#include <sstream>

BOOL round_up_sound = FALSE;

GameScene::GameScene() : Scene { Game },
resume_button { Resume, L"��", { 20, 30 }, 60, 15 }, quit_button { Quit, L"��]", { 20, 70 }, 60, 15 },
game_over_message { L"DEAD", { 0, 25 }, 100, 20 } {
    setUp();
    resume_button.border_color = Gray;
    resume_button.border_width = 3;
    resume_button.bold = 2;

    quit_button.border_color = Gray;
    quit_button.border_width = 3;
    quit_button.bold = 2;

    game_over_message.text_color = Red;
    game_over_message.transparent_background = true;
    game_over_message.transparent_border = true;
    game_over_message.bold = 2;
}


void GameScene::setUp() {
    is_paused = false;
    game_over = false;
    health = 100;

    //��鸲 �ʱ�ȭ
    shake_count = 0;
    shake_acc = 0;
    shake_effect = 0;
    ss_x = 0;
    ss_y = 0;

    // �÷��̾� ��ġ �� ���� �ʱ�ȭ
    CM_x = 700; CM_y = 600;
    BG_scanner = 1500;  
    CM_jump = 0;
    CM_move_dir = -1;
    CM_jump_acc = 28; 
    CM_jump = 0; 
    space_pressed = 0;
    is_land = 1;
    kill_count = 0;

    // �� ���� �ʱ�ȭ
    is_zoom = FALSE;
    avail_awp = FALSE;
    shoot_delay = 0;
    after_delay = 0;
    var = 0;
    cat_ready = 0;
    awp_cat_delay = 0;

    // ���� �ʱ�ȭ
    game_round = 1;

    // ������ ���� �ʱ�ȭ
    mdx_r = 0;
    mdx_big = 0;
    mdx_air = 0;
    ddx = 0;
    cdx = 0;
    delete_delay = 0;
    cat_delete_delay = 0;

    // ��ź�� �ʱ�ȭ
    ammo = 0;
    reload = 0;
    r_pressed = 0;
    empty = 0;
    reload_x = 0;
    can_shoot = TRUE;
    reload_delay = 0;

    //���ӿ��� �� �ʱ�ȭ
    death_x = -500;
    death_acc = 54;

    //����ź �ʱ�ȭ
    is_throw = FALSE;
    is_boom = FALSE;
    set_grenade = FALSE;
    able_grenade = TRUE;
    gren_time = 0;
    gren_delay = 0;
    gren_motion_dir = -1;
    boom_delay = 0;

    //�� ���� �ִϸ��̼� �ʱ�ȭ
    new_bg_x = 0;
    new_bg_y = 850;
    CM_game_start_x = -800;
    new_logo_y = 850;
    new_logo_acc = 35;
    new_logo_delay = 0;
    new_logo_move = 1;

    //źŬ�� �ʱ�ȭ
    clip_created = FALSE;
    clip_motion_dir = -1;

    //�簢�� �ʱ�ȭ
    is_lazer = FALSE;
    is_rect = FALSE; 
    can_make_rect = TRUE;
    rect_size_x = 20; 
    rect_size_y = 20; 
    rect_acc = 0; 
    rect_delay = 0; 
    rect_delete_delay = 0;

    //�� �ʱ�ȭ
    edx = 0;
}


void GameScene::update(const POINT& point) {
    if(game_over) {
        RECT r = quit_button.absoluteArea(valid_area);
        if(PtInRect(&r, point)) {
            quit_button.highlighting = true;
        }
        else {
            quit_button.highlighting = false;
        }
        return;
    }
    if(is_paused) {
        RECT r = resume_button.absoluteArea(valid_area);
        if(PtInRect(&r, point)) {
            resume_button.highlighting = true;
        }
        else {
            resume_button.highlighting = false;
        }
        r = quit_button.absoluteArea(valid_area);
        if(PtInRect(&r, point)) {
            quit_button.highlighting = true;
        }
        else {
            quit_button.highlighting = false;
        }
        return;
    }
    if(!game_over) {
        //EXP ��� ų ���� ���� ����
        //���� * 5���� ų ���� �������� ���� ����� �ö󰣴�.
        if(kill_count >= game_round * 5) {
            kill_count = 0;
            game_round++;
            //���� ���� �� WM_TIMER���� ���� �� �ִϸ��̼� ���
            round_up = TRUE;
            round_up_sound = TRUE;
            round_size = 120;
            round_x = 550;
        }
        if(health <= 0) {
            game_over = true;
            ShowCursor(true);
            health = 100; //��� ���� �ߺ� ��� ����
        }
    }
}


void GameScene::togglePauseState() {
    if(game_over) {
        return;
    }
    if(is_paused) {
        resume();
    }
    else {
        pause();
    }
}

void GameScene::pause() {
    if(!game_over) {
        is_paused = true;
    }
    ShowCursor(true);                //Ŀ�� ��� ������ ���̱�
}

void GameScene::resume() {
    if(!game_over) {
        is_paused = false;
    }
    ShowCursor(false);                //Ŀ�� ��� ������ ���̱�
}

bool GameScene::isPaused() const {
    return is_paused;
}

bool GameScene::isGameOver() const {
    return game_over;
}


void GameScene::draw(const HDC& hdc) const {
    drawScore(hdc);

    if(is_paused) {
        drawPauseScene(hdc);
    }
    else if(game_over) {
        drawGameOverScene(hdc);
    }
}

//�ΰ��� UI ���ϼ��� ���� ����
void GameScene::drawScore(const HDC& hdc) const {
    if (!game_over && !is_paused) {
        TCHAR lpout[100];
        HFONT hfont, oldfont;
        hfont = CreateFont(round_size, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("���� ���"));
        oldfont = (HFONT)SelectObject(hdc, hfont);
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(0, 0, 0));

        //���� ���
        wsprintf(lpout, L"ROUND %d", game_round);
        for (int i = -3; i <= 3; i++)
            for (int j = -4; j <= 4; j++)
                TextOut(hdc, ss_x + round_x + i, ss_y + landing_shake + 5 + j, lpout, lstrlen(lpout));
        if (round_up == FALSE)  SetTextColor(hdc, RGB(255, 255, 255));
        else if (round_up == TRUE) SetTextColor(hdc, RGB(0, 255, 0));
        TextOut(hdc, round_x + ss_x, 5 + ss_y + landing_shake, lpout, lstrlen(lpout));

        SelectObject(hdc, oldfont);
        DeleteObject(hfont);

        hfont = CreateFont(40, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("���� ���"));
        oldfont = (HFONT)SelectObject(hdc, hfont);
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(0, 0, 0));

        //������ �ʿ��� ų �� ���
        wsprintf(lpout, L"%d KILLS to GO", game_round * 5 - kill_count);
        for (int i = -3; i <= 3; i++)
            for (int j = -3; j <= 3; j++)
                TextOut(hdc, ss_x + 350 + i, ss_y + landing_shake + 10 + j, lpout, lstrlen(lpout));
        SetTextColor(hdc, RGB(255, 255, 255));
        TextOut(hdc, 350 + ss_x, 10 + ss_y + landing_shake, lpout, lstrlen(lpout));

        SelectObject(hdc, oldfont);
        DeleteObject(hfont);
    }
}

void GameScene::drawPauseScene(const HDC& hdc) const {
    resume_button.show(hdc, valid_area);
    quit_button.show(hdc, valid_area);
}

//���� ���� �� ���� ���带 ǥ�� �ϴ� ������ ����
void GameScene::drawGameOverScene(const HDC& hdc) const {
    game_over_message.show(hdc, valid_area);
    quit_button.show(hdc, valid_area);

    TextBox score_text { L"TOTAL ROUNDS", { 0, 45 }, 100, 7 };
    //���� ���� ���� ����ϴ� ��ġ �� ũ��
    score_text.transparent_background = true;
    score_text.transparent_border = true;
    score_text.bold = 4;
    score_text.text_color = White;

    TextBox score_number { L"", { 0, 45 }, 100, 25 };
    //���� ����
    score_number.transparent_background = true;
    score_number.transparent_border = true;
    score_number.bold = 4;
    score_number.text_color = White;

    // 'TOTAL ROUNDS' ���
    score_text.show(hdc, valid_area);
    
    //���� ���� ���
    std::basic_stringstream<TCHAR> ss;
    ss << game_round;
    score_number.text = ss.str();
    score_number.show(hdc, valid_area);
    ss.str(L"");
}


int GameScene::clickL(const POINT& point) {
    if(is_paused) {
        RECT r = resume_button.absoluteArea(valid_area);
        if(PtInRect(&r, point)) {
            return resume_button.getID();
        }
        r = quit_button.absoluteArea(valid_area);
        if(PtInRect(&r, point)) {
            logo_acc = 30; //�ΰ� �ִϸ��̼� �� �ʱ�ȭ
            logo_y = -415;
            armory_to_main = TRUE;
            return quit_button.getID();
        }
        return None;
    }
    if(game_over) {
        RECT r = quit_button.absoluteArea(valid_area);
        if(PtInRect(&r, point)) {
            logo_acc = 30; //�ΰ� �ִϸ��̼� �� �ʱ�ȭ
            logo_y = -415;
            armory_to_main = TRUE;
            return quit_button.getID();
        }
        return None;
    }

    return None;
}

int GameScene::clickR(const POINT& point) {
    if(is_paused) {
        return None;
    }
    if(game_over) {
        return None;
    }

    return None;
}