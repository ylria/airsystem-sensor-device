#include "communication/bluetooth/BluetoothRefreshHandler.h"
#include "communication/bluetooth/Bluetooth.h"

void BluetoothRefreshHandler::deviceRefreshRequest(String &actionName) {
    Logger::info(
        (
            String("[BluetoothRefreshHandler]: Receive config update request, action (") 
            + actionName 
            + ")"
        ).c_str()
    );
    if(actionName.equals("wifi")) {
        Bluetooth::setLastOperationStatus("wifi|setting_up");
        Internet::stop();
        Internet::start();
        Config::save();
        Bluetooth::setLastOperationStatus("wifi|ok");
    }
    else if(actionName.equals("address")) {
        Bluetooth::setLastOperationStatus("address|ok");
    }
    else if(actionName.equals("location")) {
        Bluetooth::setLastOperationStatus("location|ok");
    }
    else if(actionName.equals("register")) {
        Bluetooth::setLastOperationStatus("register|setting_up");
        Config::save();
        Api.configUpdated();
        Bluetooth::setLastOperationStatus("register|ok");
    }

    Logger::info("[BluetoothRefreshHandler]: Config updated");
}
