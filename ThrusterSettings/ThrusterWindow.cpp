#include "ThrusterWindow.h"
#include "ui_ThrusterWindow.h"

ThrusterWindow::ThrusterWindow(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ThrusterWindow) {
    ui->setupUi(this);

    std::ifstream file("thrusterJson.json");
    if (!file) {
        qDebug() << "thrusterJson не открыт";
        createDefaultThrusterJson("thrusterJson.json");
        std::ifstream file("thrusterJson.json");
    }
    if (file) {
        qDebug() << "thrusterJson открыт";
        file >> thrusterJson;
        file.close();
    }

    thrusters_amount = thrusterJson["thrusters"].size();
    thrusters = new Thruster[thrusters_amount];
//    thrusters_table = new ThrusterName_number[thrusters_amount];
    for (int i = 0; i < thrusters_amount; ++i) {
        ui->horizontalLayout_Thrusters->addWidget(&thrusters[i], i);
        thrusters[i].setThruster(i);
//        thrusters_table[i].name = QString::fromStdString(thrusterJson["thrusters"][i]["name"]);
    }
}

ThrusterWindow::~ThrusterWindow() {
    delete [] thrusters;
    delete ui;
}

void ThrusterWindow::createDefaultThrusterJson(std::string name) {
    std::ofstream o(name);
    json j = {{"thrusters", {
            {
                    {"name", "HLB"},
                    {"backward_saturation", 75},
                    {"forward_saturation", 75},
                    {"id", 6},
                    {"kBackward", 1},
                    {"kForward", 1},
                    {"reverse", true}
            }, {
                    {"name", "HLF"},
                    { "backward_saturation", 75 },
                    { "forward_saturation", 75 },
                    { "id", 8 },
                    { "kBackward", 1 },
                    { "kForward", 1 },
                    { "reverse", false }
            }, {
                    {"name", "HRB"},
                    {"backward_saturation", 75},
                    {"forward_saturation", 75},
                    {"id", 1},
                    {"kBackward", 1},
                    {"kForward", 1},
                    {"reverse", true}
            }, {
                    {"name", "HRF"},
                    {"backward_saturation", 75},
                    {"forward_saturation", 75},
                    {"id", 2},
                    {"kBackward", 1},
                    {"kForward", 1},
                    {"reverse", true}
            }, {
                    {"name", "VB"},
                    {"backward_saturation", 75},
                    {"forward_saturation", 75},
                    {"id", 3},
                    {"kBackward", 1},
                    {"kForward", 1},
                    {"reverse", true}
            }, {
                    {"name", "VF"},
                    {"backward_saturation", 75},
                    {"forward_saturation", 75},
                    {"id", 5},
                    {"kBackward", 1},
                    {"kForward", 1},
                    {"reverse", true}
            }, {
                    {"name", "VL"},
                    {"backward_saturation", 75},
                    {"forward_saturation", 75},
                    {"id", 4},
                    {"kBackward", 1},
                    {"kForward", 1},
                    {"reverse", true}
            }, {
                    {"name", "VB"},
                    {"backward_saturation", 75},
                    {"forward_saturation", 75},
                    {"id", 7},
                    {"kBackward", 1},
                    {"kForward", 1},
                    {"reverse", true}
            },
    }}};
    o << std::setw(4) << j << std::endl;
    o.close();
}