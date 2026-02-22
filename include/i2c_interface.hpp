#pragma once

#include <cstdint>
#include <memory>
#include <span>
#include <vector>

namespace hal {

struct I2cConfig {
  uint32_t clock_hz = 100'000;  // 100 kHz default
  uint8_t address = 0x62;        // 7-bit slave address
  uint32_t timeout_ms = 500;
};

/// Abstract I2C interface for hardware abstraction.
/// Implementations: FT4222, Linux i2cdev, mock for testing.
class II2cInterface {
 public:
  virtual ~II2cInterface() = default;

  virtual void open() = 0;
  virtual void close() = 0;
  virtual bool isOpen() const = 0;

  virtual void write(std::span<const uint8_t> data) = 0;
  virtual void read(std::span<uint8_t> data) = 0;

  /// Combined write-then-read (repeated start).
  virtual void writeRead(std::span<const uint8_t> write_data,
                         std::span<uint8_t> read_data) = 0;

  /// Wait for bus idle (polling).
  virtual bool waitIdle(float timeout_s = 0.5f) = 0;
};

}  // namespace hal
