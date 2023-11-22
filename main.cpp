#include <iostream>
#include <libusb-1.0/libusb.h>

auto main() -> int {
    libusb_context *ctx = nullptr;
    libusb_init(&ctx);
    libusb_device **devs = nullptr;
    auto cnt = libusb_get_device_list(ctx, &devs);
    std::cout << "Found: " << cnt << " devices" << std::endl;

    for (auto i = 0; i < sizeof(devs); ++i) {
        auto dev = devs[i];
        libusb_device_descriptor desc{};
        libusb_get_device_descriptor(dev, &desc);
        libusb_config_descriptor *config = nullptr;
        libusb_get_config_descriptor(dev, 0, &config);
        std::cout << "Device: " << desc.idVendor << ":" << desc.bcdDevice
                  << ", " << desc.idProduct << ", " << desc.iSerialNumber
                  << ", " << desc.bDeviceClass << ", " << desc.iManufacturer
                  << ", " << desc.bcdUSB << ", " << desc.bMaxPacketSize0
                  << std::endl;
        std::cout << "Config: " << config->bLength << std::endl;
    }

    return 0;
}
