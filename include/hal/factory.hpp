#pragma once

#include "hal/hal.hpp"
#include <memory>

namespace hal {

/// Factory for creating HAL implementations.
/// Use createFt4222Spi/createFt4222I2c when linking against hal_ft4222.
std::unique_ptr<ISpiInterface> createFt4222Spi(const SpiConfig& config);
std::unique_ptr<II2cInterface> createFt4222I2c(const I2cConfig& config);

}  // namespace hal
