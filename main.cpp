#include <array>
#include <iostream>
#include <libusb-1.0/libusb.h>

auto main() -> int {

    // create a context and initialize
    libusb_context *ctx = nullptr;
    libusb_init(&ctx);

    libusb_device **devs = nullptr;
    auto device_count = libusb_get_device_list(ctx, &devs);

    if (device_count < 0) {
        std::cerr << "Failed to get device list" << std::endl;
        return -1;
    }
    std::cout << "Found: " << device_count << " devices." << std::endl;

    libusb_device_handle *handle = nullptr;

    for (auto i = 0; i < device_count; ++i) {
        auto dev = devs[i];
        libusb_device_descriptor desc{};
        libusb_get_device_descriptor(dev, &desc);

        std::cout << "\nDevice: " << desc.idVendor
                  << "\n idProduct: " << desc.idProduct
                  << "\n Bus: " << int(libusb_get_bus_number(dev))
                  << "\n Port: " << int(libusb_get_port_number(dev))
                  << "\n Speed: " << int(libusb_get_device_speed(dev))
                  << std::endl;

        if (desc.iProduct == 0) {
            std::cerr << "No product name" << std::endl;
        } else {
            auto result = libusb_open(dev, &handle);
            if (result != 0) {
                std::cerr << "Failed to open device. Skipping" << std::endl;
                std::cerr << "libusb_open error: " << libusb_strerror(result)
                          << std::endl;
            } else {
                std::cout << "Opened device" << std::endl;

                char product_name[256];
                libusb_get_string_descriptor_ascii(
                    handle, desc.iProduct,
                    static_cast<unsigned char *>(
                        static_cast<void *>(product_name)),
                    sizeof(product_name));

                std::cout << "Product: " << std::string(product_name)
                          << std::endl;

                libusb_close(handle);
            }
        }
    }

    return 0;
}
