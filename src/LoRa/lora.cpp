#include "lora.hpp"

LoRa::LoRa(unsigned int rx, unsigned int tx) : serialPort(rx, tx)
{
    carrierCode = Utils::GenerateRandomString(4);
}

void LoRa::Initialize()
{
    serialPort.begin(57600);
    serialPort.print("LAMBDA_BOOT_SIGNAL\n");
    while (true)
    {
        yield(); // darle tiempo al callstack de tcp a hacer sus tareas
        if (serialPort.available())
            if (serialPort.readString().indexOf("THETA_BOOT_RECIEVED\n") != -1)
            {
                serialPort.print("LAMBDA_CARRIER:" + carrierCode + '\n');
                break;
            }
    }

    while (true)
    {
        yield(); // darle tiempo al callstack de tcp a hacer sus tareas
        if (serialPort.available())
            if (serialPort.readString().indexOf("THETA_CARRIER_RECEIVED\n") != -1)
                break;
    }
}

boolean LoRa::TransmitMessage(Transmitions transmitionType, String data)
{
    if (data.length() > 256 - 9)
    { // 256 bytes es el máximo de LoRa, y 9 son los reservados para el protocolo
        Debug::LOG("Transmition message size limit reached!");
        Debug::LOG_VAR(data.c_str(), "Transmition data");
        return false;
    }
    if (!serialPort.availableForWrite())
        return false;
    uint32_t _messageIndex = messageIndex++;
    serialPort.print(this->carrierCode + transmitionType + Utils::IntToBase36(_messageIndex) + data + '\n');                // envia los datos a la estación de tierra
    serialPort.print(this->carrierCode + Transmitions::errorcheck + Utils::IntToBase36(_messageIndex) + sha1(data) + '\n'); // envia hash de los datos para comprobar paridad
    return true;
}

void LoRa::HandleSerial(String data)
{
    String Instruction;
    if (data.indexOf(':') != -1)
    {
        for (int i = 0; i < data.indexOf(':'); i++)
            Instruction += data[i];
        data.remove(0, data.indexOf(':'));
    }
    else
    {
        Instruction = data;
    }

    if (Instruction == "_RESEND")
    {
        Debug::LOG((String) "RESEND " + data + this->carrierCode);
    }
    else if (Instruction == "_NSQMAS")
    {
    }
}
