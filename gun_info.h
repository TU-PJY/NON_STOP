#pragma once

namespace Gun {
    int damage(int gun_id);         // ���ݷ�
    int shoot_speed(int gun_id);    // �߻� �ӵ�
    int max_ammo(int gun_id);       // �ִ� źâ
    int reload_delay(int gun_id);   // ������ ������
    int reload_speed(int gun_id);   // ������ �ӵ�
    int recoil(int gun_id);         // ź����
    int shake(int gun_id);          // ȭ�� ��鸲 ����
    int shake_time(int gun_id);     // ȭ�� ��鸲 �ð�
    int price(int gun_id);          // ����
    int speed_info(int gun_id);     //����� ����
}

