#include "autonomous.h"
#include "my-timer.h"
#include "robot_config.h"
#include "vex.h"
#include <iostream>

using namespace std;
using namespace vex;

//@brief 第一套自动程序
void autonomous_1() {
moveTo(100, 5000, 80, 5, 200, 0.5, 0.0, 0.1, 50, 20);
moveTo(-100, 5000, 80, 5, 200, 0.5, 0.0, 0.1, 50, 20);
brakeChassic();
}

//@brief 第二套自动程序
void autonomous_2() {
moveTo(150, 5000, 80, 5, 200, 0.6, 0.0, 0.1, 50, 20);
turnTo(90, 3000, 60, 3, 100, 0.7, 0.0, 0.1, 30, 15);
brakeChassic();
}

//@brief 总控
void autonomous() {
    cout << "Entering autonomous" << endl;
    robot_operation_mode = RobotOperationMode::AUTO;
    MyTimer auton_timer;

    switch (auton_type) {
        case Autotype::AUTONOMOUS_1:
            cout << "Starting AUTONOMOUS_1" << endl;
            autonomous_1();
            break;
        case Autotype::AUTONOMOUS_2:
            cout << "Starting AUTONOMOUS_2" << endl;
            autonomous_2();
            break;
    }

    Controller.Screen.setCursor(3, 13);
    Controller.Screen.print("Auton done time: %.2f s", auton_timer.getTimeDouble());
    cout << "Autonomous completed in " << auton_timer.getTimeDouble() << " seconds."
         << endl;

    // 路线结束后不要退出自动函数
    while (true) {
        this_thread::sleep_for(10);
    }
}