/**
 * @file systembus.c
 * BSD 3-Clause License
 *
 * Copyright (c) 2023, Lukas Jackson
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include "systembus.h"

void initSystemBus(SystemBus *bus)
{
    bus->numDevices = 0;
}

void addDevice(SystemBus *bus, int id, int address)
{
    if (bus->numDevices < MAX_DEVICES)
    {
        Device newDevice;
        newDevice.id = id;
        newDevice.address = address;
        newDevice.data = 0;

        bus->devices[bus->numDevices++] = newDevice;
        printf("Added device with ID %d at address %d\n", id, address);
    }
    else
    {
        printf("Cannot add device. Maximum number of devices reached.\n");
    }
}

Device *findDevice(SystemBus *bus, int id)
{
    for (int i = 0; i < bus->numDevices; i++)
    {
        if (bus->devices[i].id == id)
        {
            return &(bus->devices[i]);
        }
    }
    return NULL;
}

void writeData(SystemBus *bus, int id, int address, int data)
{
    Device *device = findDevice(bus, id);
    if (device != NULL && device->address == address)
    {
        device->data = data;
        printf("Device with ID %d wrote data %d to address %d\n", id, data, address);
    }
    else
    {
        printf("Device with ID %d not found at address %d\n", id, address);
    }
}

int readData(SystemBus *bus, int id, int address)
{
    Device *device = findDevice(bus, id);
    if (device != NULL && device->address == address)
    {
        printf("Device with ID %d read data %d from address %d\n", id, device->data, address);
        return device->data;
    }
    else
    {
        printf("Device with ID %d not found at address %d\n", id, address);
        return -1;
    }
}

int removeData(SystemBus *bus, int id, int address)
{
    Device *device = findDevice(bus, id);
    if (device != NULL && device->data != 0)
    {
        device->data = 0;
        printf("Device data with ID: %d removed data at %d address.\n", id, address);
        return device->data;
    }
    else
    {
        printf("Device with ID: %d not found at address %d\n", id, address);
        return device->data;
    }
    return -1;
}

int main(void)
{
    SystemBus bus;
    initSystemBus(&bus);

    addDevice(&bus, 1, 0x10);
    addDevice(&bus, 2, 0x20);

    writeData(&bus, 1, 0x10, 42);
    writeData(&bus, 2, 0x20, 123);

    int data1 = readData(&bus, 1, 0x10);
    int data2 = readData(&bus, 2, 0x20);

    data1 = removeData(&bus, 1, 0x10);

    printf("Data read from device 1: %d\n", data1);
    printf("Data read from device 2: %d\n", data2);

    return 0;
}
