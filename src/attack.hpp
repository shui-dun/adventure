#ifndef ATTACK_HPP
#define ATTACK_HPP

class Aggressive {
public:
    int attackVal;
};

class Vulnerable {
public:
    // 返回被攻击后是否生还
    virtual bool beAttacked(Aggressive &attacker) = 0;

    int healthPoint;
};

class AttackUtils {
public:
    static bool attack(Vulnerable &attacked, Aggressive &attacker) {
        attacked.healthPoint -= attacker.attackVal;
        // 最好受损后再变个颜色
        if (attacked.healthPoint <= 0) {
            return false;
        } else {
            return true;
        }
    }
};

#endif