#include "usercontrol.h"
#include "autonomous.h"
#include <iostream>
using namespace std;
using namespace vex;

/*怎么写按键
# 一次性触发：如A/B/UP/DOWN，按下后触发一次事件，再次按下才会触发第二次事件
  写法：if(press_A){ press_A=false; //事件代码 }
# 持续触发：如L1/L2/R1/R2，按下后持续触发事件，松开后停止触发
  写法：if(press_L1){ //事件代码 }
*/

//@brief IMU初始化
void botInit() { 
    std::cout << "=========Init=========" << std::endl;
    Inertial.startCalibration();
    Controller.Screen.setCursor(5, 1);
    Controller.Screen.print("IMU Calibrating...");
    std::cout << "IMU Calibrating..." << std::endl;
    while (Inertial.isCalibrating()) {
        this_thread::sleep_for(10);
    }
    this_thread::sleep_for(200);
    double last_rot = Inertial.rotation();
    this_thread::sleep_for(800);
    if (abs(Inertial.rotation() - last_rot) > 0.1f) {
        Controller.rumble("-.-.-");
        Controller.Screen.setCursor(5, 1);
        Controller.Screen.print("IMU Error! Recal Suggested      ");
        std::cout << "Error! IMU Heading: " << Inertial.rotation() << std::endl;
    } else {
        Controller.rumble(".");
        Controller.Screen.setCursor(5, 1);
        Controller.Screen.print("IMU Ready!                      ");
        std::cout << "Ready! IMU Heading: " << Inertial.rotation() << std::endl;
    }
    this_thread::sleep_for(500);
}

//@brief 调试用函数
void debug(){
    if (press_A){
        press_A = false;
        cout << "params move test" << endl;
        Controller.Screen.print("Moving to 100 cm");
        moveTo(100, 5000, 80, 5, 200, 0.5, 0.0, 0.1, 50, 20);
    }
    if (press_B) {
        press_B = false;
        cout << "params turn test" << endl;
        Controller.Screen.print("Turning to 90 degrees");
        turnTo(90);
    }
    if (press_DOWN) {
        press_DOWN = false;
        cout << "autonomous mode" << endl;
        autonomous();
    }
}

//@brief 球路控制
//@note 从复杂到简单写这些内容，防止键位冲突
void ballPathControl() {
    // 1. 所有双键
    if (press_R1 && press_R2) {
        moveShooter(30);
    } else if (press_R1 && press_L1) {
        moveIntake(80);
        moveShooter(100);
    } else if (press_R1 && press_L2) { 
        moveIntake(80);
        moveShooter(60);
    } else if (press_R2 && press_L1) {
        moveIntake(80);
        moveShooter(-80);
    } else if (press_R2 && press_L2) { 
        moveIntake(-50);
        moveShooter(-80);
    }
    // 2. 所有单键
    else if (press_R1) {
        moveIntake(40);
    } else if (press_R2) {
        moveIntake(-50);
        moveShooter(-80);
    } else if (press_L1) {
        moveIntake(80);
    } else if (press_L2) {
        moveIntake(-50);
    } else {
        moveIntake(0);
        moveShooter(0);
    }
}

//@brief 自动程序选择器
void autonChooser() {
    if (press_UP) {
        press_UP = false; // 修改按键实现切换不同的自动程序
        int nextVal = (static_cast<int>(auton_type) + 1) % 2;
        auton_type = static_cast<Autotype>(nextVal);
        Controller.Screen.setCursor(5, 1);
        Controller.Screen.print("Auton %s       ", auton_type_name[nextVal].c_str());
    }
}

void allDeviceControl() {
    // 在这里添加对所有设备的控制代码
    // 例如，控制电机、传感器等
    debug();
    ballPathControl();
}

void userControl() {
    // 用户控制代码
    cout<<"Entering user control" << endl;
    while (true) {
        if (auto_func_reg == COMPETITION) {
            cout << "User Control" << endl;
            robot_operation_mode = RobotOperationMode::USER_CONTROL;
        }
        allDeviceControl();
        autonChooser();
        this_thread::sleep_for(10); // 避免占用过多CPU资源
    }
}